#pragma once

#include "AbstractElement.h"
#include "G4NistManager.hh"
#include "Utils.h"

namespace geometry {

class BaseElement : public AbstractElement {
 public:
  BaseElement(const G4String &name, const G4String &material,
              const G4Colour &colour, G4LogicalVolume *parent,
              const bool customMaterial, G4Material *materialElement);

  BaseElement(const BaseElement &value);
  virtual ~BaseElement();

  const BaseElement &operator=(const BaseElement &value);

  G4LogicalVolume *createVolume(G4CSGSolid *solidVolume) override;
  G4LogicalVolume *construct(const G4bool checkOverlaps) override;

  G4LogicalVolume *parent() const;
  G4String name() const;
  G4ThreeVector position() const;
  void setPosition(const G4ThreeVector &position);
  G4RotationMatrix *rotation() const;
  void setRotation(G4RotationMatrix *rotation);
  void setMaterial(G4Material *material);

 protected:
  void drawVolume(const G4bool checkOverlaps) override;

 private:
  bool m_customMaterial;
  G4LogicalVolume *m_parent;
  G4LogicalVolume *m_current;
  G4Material *m_material;
  G4ThreeVector m_position;
  G4RotationMatrix *m_rotation;
  G4Colour m_colour;
  G4String m_name;
};
}  // namespace geometry
