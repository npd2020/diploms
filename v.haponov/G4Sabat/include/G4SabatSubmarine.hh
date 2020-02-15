#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4SabatColours.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include <G4VPhysicalVolume.hh>
#include <G4Colour.hh>
#include <QDebug>
#include "G4Tubs.hh"
#include "G4SabatAbstractConstructionElement.hh"
#include "G4PhysicsFreeVector.hh"
#include "G4SabatSubmarineDetector.hh"

class G4SabatSubmarine : public G4SabatAbstractElement
{

private:
    QList<G4SabatAbstractElement *> subElementList = QList<G4SabatAbstractElement *>();
    G4double distBottom;

public:
    G4SabatSubmarine(G4LogicalVolume *parent, const G4double width = 300 * cm,
                     const G4double height = 200 * cm, G4double length = 300 * cm,
                     const G4double dist = 15 * cm, const G4String &material = "G4_Al",
                     const G4Colour &colour = blue, const G4String &name = "Submarine");
    ~G4SabatSubmarine();

    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) override;

    void setPositionFromBottom(const G4ThreeVector &bottomP, const G4double &bottomH);
};

#endif // SUBMARINE_H
