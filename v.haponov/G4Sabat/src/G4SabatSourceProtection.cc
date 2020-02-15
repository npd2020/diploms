#include "G4SabatSourceProtection.hh"

G4SabatSource::G4SabatSource(const G4String &material, const G4Colour &colour, const G4ThreeVector &position,
                             const G4String &name, G4LogicalVolume *parent)
    : G4SabatAbstractElement(material, colour, name, parent)
{
    setPosition(position);
    setMaterialName(SabatSource::exMterial);
    setColour(SabatSource::colour);
}

G4SabatSource::~G4SabatSource()
{
}

G4LogicalVolume *G4SabatSource::construct(const G4bool &checkOverlaps)
{
    G4Box *solid = new G4Box(getName(), SabatSource::sourceXYZSize / 2, SabatSource::sourceXYZSize / 2,
                             SabatSource::sourceXYZSize / 2);
    G4LogicalVolume *current = createVolume(solid);
    drawVolume(current, checkOverlaps);

    for (int i = 6; i < 9; i++)
    {
        QString pName = "SElement" + QString::number(i);
        protectionElementList.append(new G4SabatDirectionElement(i, pName.toStdString(), checkOverlaps,
                                                                 G4ThreeVector(0, 0, 0), getCurrent()));
    }
    qDebug() << "[G4SabatSource]: construct {function}";
    return getCurrent();
}
