#ifndef G4SABATSOURCEPROTECTION
#define G4SABATSOURCEPROTECTION
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include <G4VPhysicalVolume.hh>
#include <G4Colour.hh>
#include <QDebug>
#include "G4Tubs.hh"
#include "G4SabatAbstractConstructionElement.hh"
#include "G4SabatDetectorDirTubes.hh"

namespace SabatSource {
const G4double sourceXYZSize = 0.1 * cm;
static const G4String exMterial = "G4_AIR";
static const G4Colour colour = yellow;
}
class G4SabatSource : public G4SabatAbstractElement
{
    QList<G4SabatDirectionElement *> protectionElementList = QList<G4SabatDirectionElement *>();

public:
    G4SabatSource(const G4String &material, const G4Colour &colour, const G4ThreeVector &position,
                  const G4String &name = "NeutronSource", G4LogicalVolume *parent = nullptr);
    ~G4SabatSource();

public:
    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) override;
};

#endif // G4SABATSOURCEPROTECTION
