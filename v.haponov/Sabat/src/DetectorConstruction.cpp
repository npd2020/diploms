/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
#include "DetectorConstruction.h"

#include "Detector.h"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include "Geometry.h"
#include "GeometryFabric.h"
DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(), fScoringVolume(0) {
  G4String trackerChamberSDname = "DetectorSD";
  //  trackerDetector = std::shared_ptr<SensitiveDetector>(
  //      new SensitiveDetector(trackerChamberSDname));
  //  G4SDManager::GetSDMpointer()->AddNewDetector(trackerDetector.get());
  std::fill(m_histogram->begin(), m_histogram->end(), 0);
  trackerDetector = new SensitiveDetector(m_histogram, m_counter);
  G4SDManager::GetSDMpointer()->AddNewDetector(trackerDetector);
  LogInfo::FLog<DetectorConstruction>(__func__, "create",
                                      LogInfo::LogFlags::Warning);
}

DetectorConstruction::~DetectorConstruction() {
  LogInfo::FLog<DetectorConstruction>(__func__, "delete",
                                      LogInfo::LogFlags::Warning);
}
using GeomFabricPtr = std::shared_ptr<geometry::GeometryFabric>;
G4VPhysicalVolume* DetectorConstruction::Construct() {
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // geometryFabric
  GeomFabricPtr geomFabric = GeomFabricPtr(new geometry::GeometryFabric);

  // Envelope parameters
  //
  G4double env_sizeXYZ = 1. * m;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_WATER");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXYZ = 1.2 * env_sizeXYZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World",  // its name
                                0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ,
                                0.5 * world_sizeXYZ);  // its size

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                                    world_mat,   // its material
                                                    "World");    // its name

  G4VPhysicalVolume* physWorld =
      new G4PVPlacement(0,                // no rotation
                        G4ThreeVector(),  // at (0,0,0)
                        logicWorld,       // its logical volume
                        "World",          // its name
                        0,                // its mother  volume
                        false,            // no boolean operation
                        0,                // copy number
                        checkOverlaps);   // overlaps checking

  //
  // Envelope
  //
  G4Box* solidEnv = new G4Box(utils::sabat::EnviromentName,  // its name
                              0.5 * env_sizeXYZ, 0.5 * env_sizeXYZ,
                              0.5 * env_sizeXYZ);  // its size

  G4LogicalVolume* logicEnv =
      new G4LogicalVolume(solidEnv,                       // its solid
                          env_mat,                        // its material
                          utils::sabat::EnviromentName);  //  its name

  new G4PVPlacement(0,                             // no rotation
                    G4ThreeVector(),               // at (0,0,0)
                    logicEnv,                      // its logical volume
                    utils::sabat::EnviromentName,  // its name
                    logicWorld,                    // its mother  volume
                    false,                         // no boolean operation
                    0,                             // copy number
                    checkOverlaps);                // overlaps checking

  // Bottom
  //  G4ThreeVector bottomPoss =
  //      G4ThreeVector(0, 0, -env_sizeXYZ / 2 + geometry::sabat::bottomSize /
  //      2);
  //  geometry::sabat::Bottom bottom(bottomPoss);
  //  const auto bottomProp = bottom.getProperties();
  //  auto bottomGeom = geomFabric->createGeometryElement(bottomProp, logicEnv);
  //  auto logicBottom = bottomGeom->construct(checkOverlaps);

  // Target
  G4double targetDeeps = 0. * cm;
  //  G4Material* targetMaterial =
  //      utils::Utils::MustardGas(nist);  // custom material Mustard gas

  utils::material::Au_Mineral_petzite targetMaterialDef;

  G4Material* targetMaterial =
      utils::Utils::materialCreator(nist, targetMaterialDef);
  G4Material* bottomM1 = nist->FindOrBuildMaterial("G4_Si");
  G4Material* bottomM2 = nist->FindOrBuildMaterial("G4_Fe");
  G4Material* bottomM3 = nist->FindOrBuildMaterial("G4_C");
  G4Material* bottomM4 = nist->FindOrBuildMaterial("G4_Ca");

  G4Material* resTargM = new G4Material("Custom", 3.22 * g / m3, 5);

  resTargM->AddMaterial(targetMaterial, 0.4 * perCent);

  resTargM->AddMaterial(bottomM1, 60.4 * perCent);
  resTargM->AddMaterial(bottomM2, 4.6 * perCent);
  resTargM->AddMaterial(bottomM3, 9.6 * perCent);
  resTargM->AddMaterial(bottomM4, 25.0 * perCent);

  //  G4ThreeVector targetPos =
  //      G4ThreeVector(0, 0,
  //                    geometry::sabat::bottomSize / 2 -
  //                        geometry::sabat::targetSize / 2 - targetDeeps);

  G4ThreeVector targetPos =
      G4ThreeVector(0, 0, -geometry::sabat::targetSize / 2 - targetDeeps);

  //  geometry::sabat::Target target(
  //      targetPos, targetMaterial->GetName());  // Mother volume bottomVolume
  //  target.setMaterial(targetMaterial);

  geometry::sabat::Target target(
      targetPos, resTargM->GetName());  // Mother volume bottomVolume
  target.setMaterial(resTargM);

  const auto targetProp = target.getProperties();
  //  auto targetGeom = geomFabric->createGeometryElement(targetProp,
  //  logicBottom);
  auto targetGeom = geomFabric->createGeometryElement(targetProp, logicEnv);
  auto logicTarget = targetGeom->construct(checkOverlaps);

  // DetectorSD
  G4ThreeVector detectorPos = G4ThreeVector(0, 0, utils::sabat::sourceZpos);
  geometry::sabat::DetectorSD detector(detectorPos);
  const auto detectorProp = detector.getProperties();
  auto detectorGeom = geomFabric->createGeometryElement(detectorProp, logicEnv);
  auto logicDetector = detectorGeom->construct(checkOverlaps);

  /*
 geometry::sabat::CreateProtection detectorProtection(geomFabric,
                                                      logicDetector);
 auto detectProtectVolumes = detectorProtection.create();
   */

  //
  // always return the physical World
  //
  fScoringVolume = logicTarget;
  fSensetiveVoulume = logicDetector;
  return physWorld;
}

G4LogicalVolume* DetectorConstruction::GetScoringVolume() const {
  return fScoringVolume;
}

G4LogicalVolume* DetectorConstruction::GetSensetiveVolume() const {
  return fSensetiveVoulume;
}

void DetectorConstruction::ConstructSDandField() {
  SetSensitiveDetector(utils::sabat::DetectorSDName, trackerDetector, true);
}
