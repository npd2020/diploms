#include "G4SabatBottomGeometry.hh"

G4double G4SabatBottom::getSizeXY() const
{
    return sizeXY;
}

void G4SabatBottom::setSizeXY(const G4double &value)
{
    sizeXY = value;
}

G4double G4SabatBottom::getSizeZ() const
{
    return sizeZ;
}

void G4SabatBottom::setSizeZ(const G4double &value)
{
    sizeZ = value;
}

G4SabatBottom::G4SabatBottom(const G4ThreeVector &position, const G4double &sizeXY, const G4double &sizeZ,
                             G4LogicalVolume *parent, const G4String &material, const G4Colour &colour,
                             const G4String &name)
    : G4SabatAbstractElement(material, colour, name, parent)
    , sizeXY(sizeXY)
    , sizeZ(sizeZ)
{
    setPosition(position);
    setColour(SabatBottom::Example::colour);
    setMaterialName(SabatBottom::Example::exMterial);
}

G4SabatBottom::~G4SabatBottom()
{
}

G4LogicalVolume *G4SabatBottom::construct(const G4bool &checkOverlaps)
{
    G4Box *solidB = new G4Box(getName(), sizeXY / 2, sizeXY / 2, sizeZ / 2);
    setColour(yellow);
    setMaterialName("G4_Si");
    G4LogicalVolume *seaBottom = createVolume(solidB);
    drawVolume(seaBottom, checkOverlaps);

    setMaterialName(SabatBottom::Example::exMterial);
    G4Box *solid = new G4Box(getName() + "Exmpl", SabatBottom::Example::sizeXY / 2,
                             SabatBottom::Example::sizeXY / 2, SabatBottom::Example::sizeZ / 2);
    setColour(SabatBottom::Example::colour);
    G4ThreeVector pos = G4ThreeVector(0., 0., sizeZ / 2 - SabatBottom::Example::sizeZ / 2);
    setPosition(pos);
    setParent(seaBottom);
    G4LogicalVolume *current = createVolume(solid);
    drawVolume(current, checkOverlaps);

    qDebug() << "[G4SabatBottom]: construct {function}";
    return current;
}
