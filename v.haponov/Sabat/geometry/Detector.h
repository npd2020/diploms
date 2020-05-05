#pragma once

#include "BaseElement.h"
#include "Geometry.h"
#include "GeometryFabric.h"

#include <math.h>

namespace geometry {

namespace sabat {

const G4double rotationTube =
    -atan(utils::sabat::sourceXPos / utils::sabat::sourceZpos);

constexpr G4double tubeDeepth = 1 * cm;
constexpr G4double tubeSizeZ = 7. * cm;

class ProtectionTube : public GeomProp {
 public:
  ProtectionTube(const G4double innerR, const G4double outerR,
                 const G4double sizeZ, const G4String& name,
                 const G4String& material, const G4ThreeVector& pos,
                 const G4Colour& colour);

  GeomProp getGeometryProperty() const;
};

class ProtectionSphere : public GeomProp {
 public:
  ProtectionSphere(const G4double innerR, const G4double outerR,
                   const G4String& name, const G4String& material,
                   const G4ThreeVector& pos, const G4Colour& colour);

  GeomProp getGeometryProperty() const;
};

using GeomFabricPtr = std::shared_ptr<geometry::GeometryFabric>;
class CreateProtection {
 public:
  CreateProtection(const GeomFabricPtr& fabric, G4LogicalVolume* parent,
                   G4RotationMatrix* rotMatrix = new G4RotationMatrix,
                   const G4ThreeVector& pos = G4ThreeVector(0, 0, 0));

  QVector<G4LogicalVolume*> create(const bool isSourceP = false) const;
  G4LogicalVolume* createTube(const int index, G4double& lastOuter,
                              const bool isSourceP = false) const;
  G4LogicalVolume* createSphere(const int index, G4double& lastOuter) const;
  void setCheckOverlaps(bool value);

 private:
  G4LogicalVolume* m_parent;
  G4ThreeVector m_position;
  GeomFabricPtr m_fabric;
  G4RotationMatrix* m_rotMatrix;
  bool checkOverlaps = true;
  const QVector<G4String> m_materials = {"G4_Pb", "G4_B", "G4_Al"};
  const QVector<G4String> m_names = {"First", "Second", "Third"};
  const QVector<G4double> m_sizes = {1. * cm, 5. * cm, 2. * cm};
  const QVector<G4Colour> m_colours = {
      utils::colours::red, utils::colours::yellow, utils::colours::lgreen};
};

namespace detector {

class Detector : public geometry::BaseElement {};
}  // namespace detector
}  // namespace sabat
}  // namespace geometry
