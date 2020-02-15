#ifndef G4SABATBOTTOMGEOMETRY_H
#define G4SABATBOTTOMGEOMETRY_H
#include "G4SabatAbstractConstructionElement.hh"
#include "G4SabatDetectorDirTubes.hh"
namespace SabatBottom {
namespace Example {
    constexpr G4double sizeXY = 2 * m;
    constexpr G4double sizeZ = 50 * cm;
    const G4String exMterial = "G4_Co";
    const G4Colour colour = green;
}
}
class G4SabatBottom : public G4SabatAbstractElement
{
private:
    G4double sizeXY, sizeZ;

public:
    G4SabatBottom(const G4ThreeVector &position, const G4double &sizeXY = 0., const G4double &sizeZ = 0,
                  G4LogicalVolume *parent = nullptr, const G4String &material = "",
                  const G4Colour &colour = white, const G4String &name = "Bottom");
    ~G4SabatBottom();

public:
    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) override;
    G4double getSizeXY() const;
    void setSizeXY(const G4double &value);
    G4double getSizeZ() const;
    void setSizeZ(const G4double &value);
};

#endif // G4SABATBOTTOMGEOMETRY_H
