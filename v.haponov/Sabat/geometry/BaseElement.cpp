#include "BaseElement.h"

#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

namespace geometry {

BaseElement::BaseElement(const G4String &name, const G4String &material,
                         const G4Colour &colour, G4LogicalVolume *parent,
                         const bool customMaterial, G4Material *materialElement)
    : AbstractElement(),
      m_customMaterial(customMaterial),
      m_parent(parent),
      m_colour(colour),
      m_name(name) {
  if (!customMaterial && !materialElement) {
    auto *nist = G4NistManager::Instance();
    m_material = nist->FindOrBuildMaterial(material);
    LogInfo::FLog<BaseElement>(__func__, "with usual material from dataBase");
  } else {
    m_material = materialElement;
    LogInfo::FLog<BaseElement>(__func__, "with custom Material");
  }
}

BaseElement::BaseElement(const BaseElement &value)
    : BaseElement(value.m_name, value.m_material->GetName(), value.m_colour,
                  value.m_parent, value.m_customMaterial, value.m_material) {
  m_position = value.m_position;
  m_current = value.m_current;
  m_rotation = value.m_rotation;
  LogInfo::FLog<BaseElement>(__func__, "copy");
}

BaseElement::~BaseElement() {}

const BaseElement &BaseElement::operator=(const BaseElement &value) {
  m_name = value.m_name;
  m_material = value.m_material;
  m_colour = value.m_colour;
  m_parent = value.m_parent;
  m_position = value.m_position;
  m_current = value.m_current;
  m_rotation = value.m_rotation;

  LogInfo::FLog<BaseElement>(__func__, "operator");
  return *this;
}

G4LogicalVolume *BaseElement::construct(const G4bool checkOverlaps) {
  drawVolume(checkOverlaps);
  LogInfo::FLog<BaseElement>(__func__, "done");
  return m_current;
}

G4LogicalVolume *BaseElement::createVolume(G4CSGSolid *solidVolume) {
  auto logicalVolume = new G4LogicalVolume(solidVolume, m_material, m_name);
  logicalVolume->SetVisAttributes(new G4VisAttributes(m_colour));
  m_current = logicalVolume;
  LogInfo::FLog<BaseElement>(__func__, "done");
  return logicalVolume;
}

void BaseElement::drawVolume(const G4bool checkOverlaps) {
  new G4PVPlacement(m_rotation,      // no rotation
                    m_position,      // at position
                    m_current,       // its logical volume
                    m_name,          // its name
                    m_parent,        // its mother  volume
                    false,           // no boolean operation
                    0,               // copy number
                    checkOverlaps);  // overlaps checking
  LogInfo::FLog<BaseElement>(__func__, "done");
}

void BaseElement::setMaterial(G4Material *material) {
  m_material = material;
  LogInfo::FLog<BaseElement>(__func__, "done");
}

G4LogicalVolume *BaseElement::parent() const { return m_parent; }

G4String BaseElement::name() const { return m_name; }

G4ThreeVector BaseElement::position() const { return m_position; }

void BaseElement::setPosition(const G4ThreeVector &position) {
  m_position = position;
}

G4RotationMatrix *BaseElement::rotation() const { return m_rotation; }

void BaseElement::setRotation(G4RotationMatrix *rotation) {
  m_rotation = rotation;
}
}  // namespace geometry
