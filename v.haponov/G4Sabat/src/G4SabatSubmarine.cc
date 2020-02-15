#include "G4SabatSubmarine.hh"

G4SabatSubmarine::G4SabatSubmarine(G4LogicalVolume *parent, const G4double width, const G4double height,
                                   G4double length, const G4double dist, const G4String &material,
                                   const G4Colour &colour, const G4String &name)
    : G4SabatAbstractElement(material, colour, name, parent)
    , distBottom(dist)
{
    //    setXSize(length / 2);
    //    setYSize(height / 2);
    //    setZSize(width / 2);
    //    G4SabatDetector *submarineDetector = new G4SabatDetector(this);
    //    subElementList.append(submarineDetector);
    qDebug() << "[Constructor]{G4SabatSubmarine}"
             << "done";
}

G4SabatSubmarine::~G4SabatSubmarine()
{
    std::for_each(subElementList.begin(), subElementList.end(),
                  [](G4SabatAbstractElement *element) { delete element; });
    qDebug() << "[Destructor]{G4SabatSubmarine}"
             << "done";
}

G4LogicalVolume *G4SabatSubmarine::construct(const G4bool &checkOverlaps)
{
    //    G4NistManager *nist = G4NistManager::Instance();
    //    // Submarine main box
    //    G4Material *submarine_mat = nist->FindOrBuildMaterial(materialName);
    //    G4Box *solidSubmarine = new G4Box(name, xSize, ySize, zSize);
    //    G4LogicalVolume *logicSubmarine = new G4LogicalVolume(solidSubmarine, submarine_mat, name);
    //    logicSubmarine->SetVisAttributes(new G4VisAttributes(colour));
    //    qDebug() << "submarine create4";
    //    new G4PVPlacement(rot,            // no rotation
    //                      position,       // at position
    //                      logicSubmarine, // its logical volume
    //                      name,           // its name
    //                      parent,         // its mother  volume
    //                      false,          // no boolean operation
    //                      0,              // copy number
    //                      checkOverlaps); // overlaps checking
    //    qDebug() << "submarine create";
    // Trapezoid shape
    //    G4SabatDetector *submarineDetector = dynamic_cast<G4SabatDetector *>(subElementList.first());
    //    submarineDetector->setLogicParent(logicSubmarine);
    //    //    submarineDetector->setLogicParent(lo
    //    G4ThreeVector detectorPos = G4ThreeVector(submarineDetector->getXSize() * 2, -ySize, 0);
    //    submarineDetector->setPosition(detectorPos);
    //        return submarineDetector->construct(checkOverlaps);
}

void G4SabatSubmarine::setPositionFromBottom(const G4ThreeVector &bottomP, const G4double &bottomH)
{
    //    position = bottomP;
    //    G4double deviceH = 30. * cm;
    //    std::for_each(subElementList.begin(), subElementList.end(),
    //                  [deviceH](G4SabatAbstractElement *elemet) mutable -> G4double {
    //                      deviceH += elemet->getYSize();
    //                      return deviceH;
    //                  });

    //    position.setY(bottomP.y() + bottomH / 2 + ySize + deviceH + distBottom);
    //    qDebug() << "[G4SabatSubmarine::setPositionFromBottom] done" << deviceH;
}
