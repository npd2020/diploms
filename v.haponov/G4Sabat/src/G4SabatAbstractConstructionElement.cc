#include "G4SabatAbstractConstructionElement.hh"

G4LogicalVolume *G4SabatAbstractElement::getParent() const
{
    return parent;
}

G4String G4SabatAbstractElement::getName() const
{
    return name;
}

void G4SabatAbstractElement::setColour(const G4Colour &value)
{
    colour = value;
}

void G4SabatAbstractElement::setMaterialName(const G4String &value)
{
    materialName = value;
}

void G4SabatAbstractElement::setParent(G4LogicalVolume *value)
{
    parent = value;
}

G4LogicalVolume *G4SabatAbstractElement::getCurrent() const
{
    return current;
}

G4SabatAbstractElement::G4SabatAbstractElement(const G4String &material, const G4Colour &colour,
                                               const G4String &name, G4LogicalVolume *parent)
{
    materialName = material;
    this->name = name;
    this->colour = colour;
    this->parent = parent;
    qDebug() << "[Constructor]:G4SabatAbstractElement::G4SabatAbstractElement {full}";
}

G4SabatAbstractElement::G4SabatAbstractElement(const G4SabatAbstractElement &value)
    : G4SabatAbstractElement(value.materialName, value.colour, value.name, value.parent)
{
    position = value.position;
    current = value.current;
    qDebug() << "[Constructor]:G4SabatAbstractElement::G4SabatAbstractElement {copy}";
}

G4SabatAbstractElement::~G4SabatAbstractElement()
{
}

G4LogicalVolume *G4SabatAbstractElement::createVolume(G4CSGSolid *solidVolume)
{
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *material = nist->FindOrBuildMaterial(materialName);
    G4LogicalVolume *logicalVolume = new G4LogicalVolume(solidVolume, material, name);
    logicalVolume->SetVisAttributes(new G4VisAttributes(colour));
    current = logicalVolume;
    return logicalVolume;
    qDebug() << "[G4SabatAbstractElement]: createVolume {function}";
}

void G4SabatAbstractElement::drawVolume(G4LogicalVolume *volume, const G4bool &checkOverlaps)
{
    new G4PVPlacement(rot,            // no rotation
                      position,       // at position
                      volume,         // its logical volume
                      name,           // its name
                      parent,         // its mother  volume
                      false,          // no boolean operation
                      0,              // copy number
                      checkOverlaps); // overlaps checking
    qDebug() << "[Show] Logical volume: [" << name << "] from parent: [" << parent->GetName() << "]";
}

G4ThreeVector G4SabatAbstractElement::getPosition() const
{
    return position;
}

void G4SabatAbstractElement::setPosition(const G4ThreeVector &value)
{
    position = value;
}

G4RotationMatrix *G4SabatAbstractElement::getRot() const
{
    return rot;
}
