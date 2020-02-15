#ifndef G4SABATCONSTRUCTIONELEMENT_H
#define G4SABATCONSTRUCTIONELEMENT_H

#include <QDebug>

#include "G4CSGSolid.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"

class G4SabatAbstractElement
{

private:
    G4LogicalVolume *parent, *current;
    G4String materialName, name;
    G4Colour colour;
    G4ThreeVector position;

protected:
    G4RotationMatrix *rot = new G4RotationMatrix;

public:
    G4SabatAbstractElement(const G4String &material, const G4Colour &colour, const G4String &name,
                           G4LogicalVolume *parent = nullptr);
    G4SabatAbstractElement(const G4SabatAbstractElement &value);
    virtual ~G4SabatAbstractElement();

protected:
    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) = 0;
    G4LogicalVolume *createVolume(G4CSGSolid *solidVolume);
    void drawVolume(G4LogicalVolume *volume, const G4bool &checkOverlaps);

public:
    G4ThreeVector getPosition() const;
    void setPosition(const G4ThreeVector &value);
    G4RotationMatrix *getRot() const;

    G4SabatAbstractElement &operator=(const G4SabatAbstractElement &value);
    G4LogicalVolume *getParent() const;
    G4String getName() const;
    void setColour(const G4Colour &value);
    void setMaterialName(const G4String &value);
    void setParent(G4LogicalVolume *value);
    G4LogicalVolume *getCurrent() const;
};

#endif // G4SABATCONSTRUCTIONELEMENT_H
