// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes, nor the agencies providing financial support for this*
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// *                                                                  *
// * Разработано специально для dev.asifmoda.com                      *
// * Можно использовать для обучения, частных и коммерческих проектов.*
// * Прывітанне з Беларусі!                                           *
// * Автор, идея и реализация:                                        *
// * Виктор Гавриловец, bycel@tut.by,                                 *
// ********************************************************************
//
/// \file G4SabatDetectorConstruction01.cpp
/// \brief Implementation of the G4SabatDetectorConstruction01 class

#include "G4SabatDetectorConstruction01.hh"
#include "G4SabatDetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SabatSourceProtection.hh"

// Конструктор класса объявления материалов и геометрии всей моделируемой системы
G4SabatDetectorConstruction01::G4SabatDetectorConstruction01()
    : G4VUserDetectorConstruction()
{
}

// Деструктор
G4SabatDetectorConstruction01::~G4SabatDetectorConstruction01()
{
}

// Функция определения материалов и геометрии всей системы,
// должна возвращать физический объем - ссылку на экземпляр класса G4VPhysicalVolume
// Геометрию проектировать будем следующую: пучок протонов попадает на мишень
// вольфрамовый лист толщиной около 1 мм, а за мишень поставим детектор
// таких же размеров, он будет регистрировать что в него попало.
G4VPhysicalVolume* G4SabatDetectorConstruction01::Construct()
{
    // Для простоты используем предопределенные в Geant4 материалы
    // Так объявляется менеджер, из которого можно извлечь
    // ранее предопределенные материалы
    G4NistManager* nist = G4NistManager::Instance();

    // Параметры детектора
    G4double det_sizeXYZ = 25 * cm;
    // Материал детектора, здесь выбираем вольфрам
    G4Material* det_mat = nist->FindOrBuildMaterial("G4_Ge");
    // Опция для включения/выключения проверки перекрытия объемов
    G4bool checkOverlaps = true;

    // World
    // Объем мира, самый большой объем, включающий остальные, аналог экспериментального
    // зала
    G4double world_sizeXYZ = 5 * m; //Размер по x и y здесь будут одинаковы - ширина и высота
    // Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

    // Создание объема для мира (экспериментального зала), определяется сама форма объема,
    // берем параллелепипед, это просто геометрическая фигура
    G4Box* solidWorld =
        new G4Box("World", // its name, название объема
                  0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ); // its size, его размеры
    // указываются половины размеров высоты, ширины и глубины

    // Логический объем, здесь подключается материал, из которого сделан объем
    G4LogicalVolume* logicWorld =
        new G4LogicalVolume(solidWorld, // its solid, геометрический объем, объявлен выше
                            world_mat, // its material, материал объема
                            "World");  // its name, название логического объема
    //совпадает с названием объема, но
    //для Geant4 это разные объекты
    //геометрический объем и логический объем

    //Физический объем, а теперь наш логический объем помещаем в "реальный" мир
    G4VPhysicalVolume* physWorld =
        new G4PVPlacement(0,               // no rotation, нет вращения
                          G4ThreeVector(), // at (0,0,0), расположение в центре (0,0,0)
                          logicWorld, // its logical volume, логический объем этого физического
                          "World", // its name, название физического объема
                          0, // its mother  volume, материнский объем, этот самый первый, поэтому 0
                          false, // no boolean operation, без логических (булевых) операций
                          0, // copy number, номер копии
                          checkOverlaps); // overlaps checking, флаг проверки перекрытия объемов

    // Детектор, для него также используем параллелепипед
    G4SabatBottom* bottom = new G4SabatBottom(G4ThreeVector(0, 0, -world_sizeXYZ / 2 + 1. * m), world_sizeXYZ,
                                              2. * m, logicWorld);
    bottom->construct(checkOverlaps);
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume("Bottom");

    G4Box* bottomBox = dynamic_cast<G4Box*>(envLV->GetSolid());
    G4double bottomHeight = bottomBox->GetZHalfLength() * 2;
    G4Box* solidDet = new G4Box("Detector",                                               // its name, имя
                                0.5 * det_sizeXYZ, 0.5 * det_sizeXYZ, 0.5 * det_sizeXYZ); // its size, размер
    //Логический объем
    G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet, // its solid, объем
                                                    det_mat, // its material, указываем материал детектора
                                                    "Detector"); // its name, его имя
    G4ThreeVector detectorPosition = G4ThreeVector(
        -cos(Sabat::tubeRotZ) * Sabat::dirTubesHeight - Sabat::PbOuterDirTube::outerR, 0.,
        -world_sizeXYZ / 2 + bottomHeight + Sabat::dirTubesHeight
            + sin(Sabat::tubeRotZ) * (Sabat::dirTubesHeight + Sabat::PbOuterSphr::outerR) + 4. * cm);

    //Физический объем детектора
    G4RotationMatrix* detectorRot = new G4RotationMatrix;
    detectorRot->rotateY(Sabat::tubeRotZ);
    new G4PVPlacement(detectorRot, // no rotation, так же без вращения
                      detectorPosition, // at (0,0,5 см) положение центра детектора, он смещен на 5 см от
                                        // центра объема World
                      logicDet,   // its logical volume, подключаем логический объем
                      "Detector", // its name, имя физического объема
                      logicWorld, // its mother  volume, родительский логический объем, помещаем в world!
                      false, // no boolean operation, без булевых операций
                      0,     // copy number, номер копии
                      checkOverlaps); // overlaps checking, флаг проверки перекрытия объемов
    G4ThreeVector protectionPos = G4ThreeVector(0, 0, 0);
    qDebug() << "set protection position" << protectionPos.x() << protectionPos.y() << protectionPos.z();
    QList<G4SabatDirectionElement*> protectionElementList = QList<G4SabatDirectionElement*>();
    for (int i = 6; i < 9; i++)
    {
        QString pName = "PElement" + QString::number(i);
        protectionElementList.append(
            new G4SabatDirectionElement(i, pName.toStdString(), checkOverlaps, protectionPos, logicDet));
    }

    G4ThreeVector sourcePosition = G4ThreeVector(0, 0, 0);
    G4SabatSource* sourceP = new G4SabatSource("", blue, sourcePosition);
    //    sourceP->construct(checkOverlaps);
    //    G4Box* solid = new G4Box("DetectorGe",                                       // its name,
    //    имя
    //                             0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * 5. * cm); // its size,
    //                             размеры

    //    //Логический объем
    //    G4LogicalVolume* logic = new G4LogicalVolume(solid, // its solid, объем
    //                                                 det_mat, // its material, указываем материал
    //                                                 детектора "DetectorGe"); // its name, его имя

    //    //Физический объем детектора
    //    new G4PVPlacement(
    //        0, // no rotation, так же без вращения
    //        G4ThreeVector(
    //            0, 0,
    //            2.5 * cm), // at (0,0,5 см) положение центра детектора, он смещен на 5 см от центра
    //            объема World
    //        logic,         // its logical volume, подключаем логический объем
    //        "Detector",    // its name, имя физического объема
    //        logicWorld, // its mother  volume, родительский логический объем, помещаем в world!
    //        false,          // no boolean operation, без булевых операций
    //        0,              // copy number, номер копии
    //        checkOverlaps); // overlaps checking, флаг проверки перекрытия объемов
    //    // Для мишени, на которую будет падать пучек, возьмем геометрические размеры как
    //    // у детектора, параллелепипед - лист вольфрама.
    //    //Логический объем
    //    G4Box* solidtarg = new G4Box("Detector",                                           // its
    //    name, имя
    //                                 0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ); // its
    //                                 size, размеры
    //    G4Material* targ_mat = nist->FindOrBuildMaterial("G4_Ca");
    //    G4LogicalVolume* logicTar = new G4LogicalVolume(solidtarg, // its solid, объем
    //                                                    targ_mat, // its material, указываем
    //                                                    материал мишени "Target"); // its name, его
    //                                                    имя

    //Физический объем мишени
    //    new G4PVPlacement(0, G4ThreeVector(0, 0, -5 * cm), logicTar, "Target", logicWorld, false, 0,
    //                      checkOverlaps);
    //  new G4PVPlacement(0,                       //no rotation, так же без вращения
    //                    G4ThreeVector(0,0,-5*cm),//at (0,0,-5 см) положение центра мишени в другую
    //                    сторону от детектора, смещена на 5 см от центра объема World logicTar, //its
    //                    logical volume, подключаем логический объем "Target",                //its
    //                    name, имя физического объема logicWorld,              //its mother  volume,
    //                    родительский логический объем! false,                   //no boolean
    //                    operation, без булевых операций 0,                       //copy number,
    //                    номер копии checkOverlaps);
    //Всегда возвращает физический объем
    return physWorld;
}

void G4SabatDetectorConstruction01::ConstructSDandField()
{
    // Объявление чувствительной области детектора, в которой можно получить подробную
    // информацию о состоянии и движении частицы
    // Назовем чувствительную область DetectorSD
    G4String trackerChamberSDname = "DetectorSD";
    // Создаем экземпляр чувствительной области
    G4SabatDetectorSD* aTrackerSD = new G4SabatDetectorSD(trackerChamberSDname);
    // Передаем указатель менеджеру
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
    // Добавляем чувствительный объем ко всем логическим областям с
    // именем Detector
    SetSensitiveDetector("Detector", aTrackerSD, true);
}
