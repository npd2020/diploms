#include "DetectorConstruction.hh"
#include "DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4UnionSolid.hh"  //("Box+Cylinder", box, cyl)
#include "G4IntersectionSolid.hh" //("Box*Cylinder", box, cyl)
#include "G4SubtractionSolid.hh" //("Box-Cylinder", box, cyl)
#include "G4MultiUnion.hh" //
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

// Конструктор класса объявления материалов и геометрии всей моделируемой системы
DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

// Деструктор
DetectorConstruction::~DetectorConstruction()
{ }

// Функция определения материалов и геометрии всей системы,
// должна возвращать физический объем - ссылку на экземпляр класса G4VPhysicalVolume
// Геометрию проектировать будем следующую: пучок протонов попадает на мишень
// вольфрамовый лист толщиной около 1 мм, а за мишень поставим детектор
// таких же размеров, он будет регистрировать что в него попало.
G4VPhysicalVolume* DetectorConstruction::Construct()
{  
    // Для простоты используем предопределенные в Geant4 материалы
    // Так объявляется менеджер, из которого можно извлечь
    // ранее предопределенные материалы
  G4NistManager* nist = G4NistManager::Instance();
   
  // Опция для включения/выключения проверки перекрытия объемов
  G4bool checkOverlaps = true;

  // Envelope parameters
  G4double env_sizeX = 60*cm, env_sizeY = 60*cm, env_sizeZ = 60*cm;

  // World(Основна робоча зона)
  G4double world_sizeX = env_sizeX;
  G4double world_sizeY = env_sizeY;
  G4double world_sizeZ  = env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_WATER");
  
  G4Box* WorldS =    
    new G4Box("World",                             //its name
       1.2*world_sizeX, 1.2*world_sizeY, 1.2*world_sizeZ);     //its size
      
  G4LogicalVolume* WorldL =                         
    new G4LogicalVolume(WorldS,              //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* WorldPV = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      WorldL,                //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
  ///////////////////////////////////////////////////////////////////////////////////////////////
  ///                      Земля або досліджуванна речовина(мішень)
  G4Element*  C = nist->FindOrBuildElement("C" , false);
  G4Element*  H  = nist->FindOrBuildElement("H" , false);
  G4Element*  Cl  = nist->FindOrBuildElement("Cl" , false);
  G4Element*  S  = nist->FindOrBuildElement("S" , false);

  G4Material* C4H8Cl2S = new G4Material("NaI", 1.27*g/cm3, 4);
  C4H8Cl2S->AddElement(C, 4);
  C4H8Cl2S->AddElement(H, 8);
  C4H8Cl2S->AddElement(Cl, 2);
  C4H8Cl2S->AddElement(S, 1);
  //G4Material* C4H8Cl2S = nist->FindOrBuildMaterial("G4_Ag");
  G4ThreeVector pos1 = G4ThreeVector(0, -0.5*env_sizeY, 0*cm);

  G4Box* GroundS =    
    new G4Box("Ground",                       //its name
        env_sizeX, 0.05*env_sizeY, env_sizeZ); //its size
      
  G4LogicalVolume* GroundL =                         
    new G4LogicalVolume(GroundS,              //its solid
                        C4H8Cl2S,             //its material
                        "Ground");            //its name
                    
  G4VPhysicalVolume* GroundPV =
    new G4PVPlacement(0,                      //no rotation
                    pos1,                     //at 
                    GroundL,                  //its logical volume
                    "Ground",                 //its name
                    WorldL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * GroundAtt = new G4VisAttributes(G4Colour(1.,1.,0.)); // yellow
  GroundAtt->SetForceWireframe(true);
  GroundL->SetVisAttributes(GroundAtt);
  ///////////////////////////////////////////////////////////////////////////////////////////
  ////  Свинцевий захист
  //G4double wrapperX = 10*cm, wrapperY = 20*cm, wrapperZ = 20*cm;
  G4Material* wrapper_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, 0*cm);

  G4double TpRMin = 10*cm, TpRMax = 12*cm, TpDz = 12*cm, TpSPhi = 0*deg, TpDPhi = 360.*deg;
  G4Tubs* WrapperTubusS = new G4Tubs("WrapperTubus", TpRMin, TpRMax, TpDz, TpSPhi, TpDPhi);

  G4double SpRmin = TpRMin, SpRmax = TpRMax, SpSPhi = 0*deg, SpDPhi = 360.*deg, SpSTheta = 0*deg, SpDTheta = 90.*deg;
  G4Sphere* WrapperSphereS = new G4Sphere("WrapperSphere", SpRmin, SpRmax, SpSPhi, SpDPhi, SpSTheta, SpDTheta);

  G4RotationMatrix* rotm  = new G4RotationMatrix();
  G4ThreeVector position1 = G4ThreeVector(0.*cm,0.*cm,0*cm);
  G4ThreeVector position2 = G4ThreeVector(0.*cm,0.*cm,TpDz);
  G4Transform3D tr1 = G4Transform3D(*rotm,position1);
  G4Transform3D tr2 = G4Transform3D(*rotm,position2);

  G4MultiUnion* WrapperU = new G4MultiUnion("Wrapper");
  WrapperU->AddNode(*WrapperTubusS,tr1);
  WrapperU->AddNode(*WrapperSphereS,tr2);
  WrapperU->Voxelize();

  G4LogicalVolume* WrapperL =                         
    new G4LogicalVolume(WrapperU,               //its solid
                        wrapper_mat,           //its material
                        "Wrapper");            //its name
  
  G4RotationMatrix* rot  = new G4RotationMatrix();
  rot->rotateX(M_PI/2.*rad);

  G4VPhysicalVolume* WrapperPV =
    new G4PVPlacement(rot,                      //no rotation
                    pos2,                     //at 
                    WrapperL,                  //its logical volume
                    "Wrapper",                 //its name
                    WorldL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * WrapAtt = new G4VisAttributes(G4Colour(1.,0.,0.)); // red
  WrapAtt->SetForceWireframe(true);
  WrapperL->SetVisAttributes(WrapAtt);
  ////////////////////////////////////////////////////////////////////////////////////////
  ///наброски(trash)
 /* G4Material* C4H8Cl2 = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos9 = G4ThreeVector(0, 0*env_sizeY, 0*cm);

  
  G4Tubs* ss = new G4Tubs("WrapperTubus", TpRMin, TpRMax, TpDz, TpSPhi, TpDPhi);

  G4LogicalVolume* ssl =                         
    new G4LogicalVolume(ss,              //its solid
                        C4H8Cl2,             //its material
                        "ss");            //its name
  
  G4RotationMatrix* rot  = new G4RotationMatrix();
  rot->rotateX(M_PI/2.*rad);

  G4VPhysicalVolume* sspv =
    new G4PVPlacement(rot,                      //no rotation
                    pos9,                     //at 
                    ssl,                  //its logical volume
                    "ss",                 //its name
                    WorldL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * ssj = new G4VisAttributes(G4Colour(1.,1.,0.)); // yellow
  ssj->SetForceWireframe(true);
  ssl->SetVisAttributes(ssj);*/
  //////////////////////////////////////////////////////////////////////////////////////                 
  // Детектор
  G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Ge"); 
  //G4ThreeVector pos3 = G4ThreeVector(0*cm, 0*env_sizeY, (TpRMin/2)+(TpDz/4));
  G4ThreeVector pos3 = G4ThreeVector(0*cm, 5*cm, 0*cm); 

  G4Box* DetectorS =    
    new G4Box("Detector",                              //its name
       0.5*TpRMin, 0.5*TpRMin, 0.5*TpRMin); //its size
  
  G4LogicalVolume* DetectorL =                         
    new G4LogicalVolume(DetectorS,                //its solid
                        detector_mat,             //its material
                        "Detector");              //its name
                    
  G4VPhysicalVolume* DetectorPV =
    new G4PVPlacement(0,                       //no rotation
                    pos3,                      //at 
                    DetectorL,                 //its logical volume
                    "Detector",                //its name
                    WorldL,                   //its mother  volume     (чому не прцює з логічний обєктом WrapperL)
                    false,                     //no boolean operation
                    0,                         //copy number
                    checkOverlaps);            //overlaps checking
  G4VisAttributes * DetAtt = new G4VisAttributes(G4Colour(0.,1.,0.)); // green
  DetAtt->SetForceWireframe(true);
  DetectorL->SetVisAttributes(DetAtt);

  //////////////////////////////////////////////////////////////////////////////////
  //Всегда возвращает физический объем
  return WorldPV;
}

void DetectorConstruction::ConstructSDandField()
{
  // Объявление чувствительной области детектора, в которой можно получить подробную
  // информацию о состоянии и движении частицы
  // Назовем чувствительную область DetectorSD
  G4String trackerChamberSDname = "DetectorSD";
  // Создаем экземпляр чувствительной области
  DetectorSD* aTrackerSD = new DetectorSD(trackerChamberSDname);
  // Передаем указатель менеджеру
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Добавляем чувствительный объем ко всем логическим областям с
  // именем Detector
  SetSensitiveDetector("Detector", aTrackerSD, true);
}
