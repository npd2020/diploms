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
  G4double env_sizeX = 3*m, env_sizeY = 3*m, env_sizeZ = 3*m;

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

  G4Material* C4H8Cl2S = new G4Material("C4H8Cl2S", 1.27*g/cm3, 4);
  C4H8Cl2S->AddElement(C, 4);
  C4H8Cl2S->AddElement(H, 8);
  C4H8Cl2S->AddElement(Cl, 2);
  C4H8Cl2S->AddElement(S, 1);
  //G4Material* C4H8Cl2S = nist->FindOrBuildMaterial("G4_Ag");
  G4ThreeVector pos1 = G4ThreeVector(0, -0.5*env_sizeY, 0*cm);

  G4Box* GroundS =    
    new G4Box("Ground",                       //its name
        1*m, 1*m, 1*m); //its size
      
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
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////
  // Алюмінієва преграда
  G4double n = 2*cm;
  G4double TpRMin = 40*cm, TpRMax = 42*cm, TpDz = 30*cm, TpSPhi = 0*deg, TpDPhi = 360.*deg;
  G4Material* rep_matSS = nist->FindOrBuildMaterial("G4_Al"); 
  G4ThreeVector pos4 = G4ThreeVector(0*cm, 70*cm, 0*cm); 

  G4Box* RepSb = new G4Box("Repperb", TpRMax + 3*cm + 2*n, TpDz+TpRMax/2 + 3*cm + 2*n, TpRMax + 3*cm + 2*n);
  G4Box* RepSm = new G4Box("Reppers", TpRMax + 2*cm + 2*n, TpDz+TpRMax/2 + 2*cm + 2*n, TpRMax + 2*cm + 2*n);
  
  G4SubtractionSolid* sub = new G4SubtractionSolid("RepSb-RepSm", RepSb, RepSm);
  
  G4LogicalVolume* RepSSL =                         
    new G4LogicalVolume(sub,                //its solid
                        rep_matSS,             //its material
                        "RepperSS");              //its name
                    
  G4VPhysicalVolume* RepSSPV =
    new G4PVPlacement(0,                       //no rotation
                    pos4,                      //at 
                    RepSSL,                 //its logical volume
                    "RepperSS",                //its name
                    WorldL,                   //its mother  volume     (чому не прцює з логічний обєктом WrapperL)
                    false,                     //no boolean operation
                    0,                         //copy number
                    checkOverlaps);            //overlaps checking
  G4VisAttributes * RepAttSS = new G4VisAttributes(G4Colour(1.,1.,1.)); // white
  RepAttSS->SetForceWireframe(true);
  RepSSL->SetVisAttributes(RepAttSS);
  ///////////////////////////////////////////////////////////////////////////////////////////
  // Повітряний блок
  G4Material* rep_mat = nist->FindOrBuildMaterial("G4_AIR"); 

  G4LogicalVolume* RepL =                         
    new G4LogicalVolume(RepSm,                //its solid
                        rep_mat,             //its material
                        "Repper");              //its name
                    
  G4VPhysicalVolume* RepPV =
    new G4PVPlacement(0,                       //no rotation
                    pos4,                      //at 
                    RepL,                 //its logical volume
                    "Repper",                //its name
                    WorldL,                   //its mother  volume     (чому не прцює з логічний обєктом WrapperL)
                    false,                     //no boolean operation
                    0,                         //copy number
                    checkOverlaps);            //overlaps checking
  G4VisAttributes * RepAtt = new G4VisAttributes(G4Colour(0.2,0.9,0.1)); // white
  RepAtt->SetForceWireframe(true);
  RepL->SetVisAttributes(RepAtt);
  //////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////// 
  ////  Свинцевий захист
  G4Material* wrapper_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4ThreeVector pos2 = G4ThreeVector(0*cm, 0*cm, 0*cm);

  //G4double TpRMin = 40*cm, TpRMax = 43*cm, TpDz = 26*cm, TpSPhi = 0*deg, TpDPhi = 360.*deg;
  G4Tubs* WrapperTubusS = new G4Tubs("WrapperTubus", TpRMin, TpRMax, TpDz, TpSPhi, TpDPhi);

  G4double SpRmin = TpRMin, SpRmax = TpRMax, SpSPhi = 0*deg, SpDPhi = 360.*deg, SpSTheta = 0*deg, SpDTheta = 90.*deg;
  G4Sphere* WrapperSphereS = new G4Sphere("WrapperSphere", SpRmin, SpRmax, SpSPhi, SpDPhi, SpSTheta, SpDTheta);

  G4RotationMatrix* rotm  = new G4RotationMatrix();
  G4ThreeVector position1 = G4ThreeVector(0.*cm,0.*cm,-TpDz + 5*cm);
  G4ThreeVector position2 = G4ThreeVector(0.*cm,0.*cm,5*cm);
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
                    RepL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * WrapAtt = new G4VisAttributes(G4Colour(1.,0.,0.)); // red
  WrapAtt->SetForceWireframe(false);
  WrapperL->SetVisAttributes(WrapAtt);
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////// 
  ////  Кадмієв захист
  G4Material* wrapper_mat2 = nist->FindOrBuildMaterial("G4_Cd");

  G4Tubs* WrapperTubusS2 = new G4Tubs("WrapperTubus2", TpRMax, TpRMax + n, TpDz, TpSPhi, TpDPhi);

  G4double SpRmin2 = TpRMax, SpRmax2 = TpRMax + n;
  G4Sphere* WrapperSphereS2 = new G4Sphere("WrapperSphere2", SpRmin2, SpRmax2, SpSPhi, SpDPhi, SpSTheta, SpDTheta);

  G4RotationMatrix* rotm2  = new G4RotationMatrix();
  G4ThreeVector position12 = G4ThreeVector(0.*cm,0.*cm,-TpDz + 5*cm);
  G4ThreeVector position22 = G4ThreeVector(0.*cm,0.*cm,5*cm);
  G4Transform3D tr12 = G4Transform3D(*rotm2,position12);
  G4Transform3D tr22 = G4Transform3D(*rotm2,position22);

  G4MultiUnion* WrapperU2 = new G4MultiUnion("Wrapper2");
  WrapperU2->AddNode(*WrapperTubusS2,tr12);
  WrapperU2->AddNode(*WrapperSphereS2,tr22);
  WrapperU2->Voxelize();

  G4LogicalVolume* WrapperL2 =                         
    new G4LogicalVolume(WrapperU2,               //its solid
                        wrapper_mat2,           //its material
                        "Wrapper2");            //its name
  
  G4RotationMatrix* rot2  = new G4RotationMatrix();
  rot2->rotateX(M_PI/2.*rad);

  G4VPhysicalVolume* WrapperPV2 =
    new G4PVPlacement(rot2,                      //no rotation
                    pos2,                     //at 
                    WrapperL2,                  //its logical volume
                    "Wrapper2",                 //its name
                    RepL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * WrapAtt2 = new G4VisAttributes(G4Colour(1.,0.5,0.)); 
  WrapAtt2->SetForceWireframe(false);
  WrapperL2->SetVisAttributes(WrapAtt2);
  ////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////// 
  ////  Парафин захист
  //G4Element*  C = nist->FindOrBuildElement("C" , false);
  //G4Element*  H  = nist->FindOrBuildElement("H" , false);

  G4Material* C31H64 = new G4Material("C31H64", 0.895*g/cm3, 2);
  C31H64->AddElement(C, 31);
  C31H64->AddElement(H, 64);

  G4Tubs* WrapperTubusS3 = new G4Tubs("WrapperTubus3", TpRMax + n, TpRMax + 2*n, TpDz, TpSPhi, TpDPhi);

  G4double SpRmin3 = TpRMax + n, SpRmax3 = TpRMax + 2*n;
  G4Sphere* WrapperSphereS3 = new G4Sphere("WrapperSphere3", SpRmin3, SpRmax3, SpSPhi, SpDPhi, SpSTheta, SpDTheta);

  G4RotationMatrix* rotm3  = new G4RotationMatrix();
  G4ThreeVector position13 = G4ThreeVector(0.*cm,0.*cm,-TpDz + 5*cm);
  G4ThreeVector position23 = G4ThreeVector(0.*cm,0.*cm,5*cm);
  G4Transform3D tr13 = G4Transform3D(*rotm2,position13);
  G4Transform3D tr23 = G4Transform3D(*rotm2,position23);

  G4MultiUnion* WrapperU3 = new G4MultiUnion("Wrapper3");
  WrapperU3->AddNode(*WrapperTubusS3,tr13);
  WrapperU3->AddNode(*WrapperSphereS3,tr23);
  WrapperU3->Voxelize();

  G4LogicalVolume* WrapperL3 =                         
    new G4LogicalVolume(WrapperU3,               //its solid
                        C31H64,           //its material
                        "Wrapper3");            //its name
  
  G4RotationMatrix* rot3  = new G4RotationMatrix();
  rot3->rotateX(M_PI/2.*rad);

  G4VPhysicalVolume* WrapperPV3 =
    new G4PVPlacement(rot3,                      //no rotation
                    pos2,                     //at 
                    WrapperL3,                  //its logical volume
                    "Wrapper3",                 //its name
                    RepL,                   //its mother  volume
                    false,                    //no boolean operation
                    0,                        //copy number
                    checkOverlaps);           //overlaps checking
  
  G4VisAttributes * WrapAtt3 = new G4VisAttributes(G4Colour(0.4,0.,0.6)); 
  WrapAtt3->SetForceWireframe(false);
  WrapperL3->SetVisAttributes(WrapAtt3);
  ////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////                 
  // Детектор
  G4Material* detector_mat = nist->FindOrBuildMaterial("G4_Ge"); 
  //G4ThreeVector pos3 = G4ThreeVector(0*cm, 0*env_sizeY, (TpRMin/2)+(TpDz/4));
  G4ThreeVector pos3 = G4ThreeVector(0*cm, 0*cm, 0*cm); 

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
                    RepL,                   //its mother  volume     (чому не прцює з логічний обєктом WrapperL)
                    false,                     //no boolean operation
                    0,                         //copy number
                    checkOverlaps);            //overlaps checking
  G4VisAttributes * DetAtt = new G4VisAttributes(G4Colour(0.,1.,0.)); // green
  DetAtt->SetForceWireframe(false);
  DetectorL->SetVisAttributes(DetAtt);
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
