#include "Detector.h"

namespace geometry {

namespace sabat {

ProtectionTube::ProtectionTube(const G4double innerR, const G4double outerR,
                               const G4double sizeZ, const G4String &name,
                               const G4String &material,
                               const G4ThreeVector &pos, const G4Colour &colour)
    : GeomProp() {
  PhiMin = tubePhiMin;
  PhiMax = tubePhiMax;
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  SizeZ = sizeZ;
  this->innerR = innerR;
  this->outerR = outerR;
  type = utils::geometry::GeometrySolid::Tube;
}

GeomProp ProtectionTube::getGeometryProperty() const {
  return utils::geometry::getGeomProperty<ProtectionTube>(this);
}

ProtectionSphere::ProtectionSphere(const G4double innerR, const G4double outerR,
                                   const G4String &name,
                                   const G4String &material,
                                   const G4ThreeVector &pos,
                                   const G4Colour &colour)
    : GeomProp() {
  PhiMin = tubePhiMin;
  PhiMax = tubePhiMax;
  ThetaMax = sphereThetaMax;
  ThetaMin = sphereThetaMin;
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  this->innerR = innerR;
  this->outerR = outerR;
  type = utils::geometry::GeometrySolid::Sphere;
}

GeomProp ProtectionSphere::getGeometryProperty() const {
  return utils::geometry::getGeomProperty<ProtectionSphere>(this);
}

CreateProtection::CreateProtection(const GeomFabricPtr &fabric,
                                   G4LogicalVolume *parent,
                                   const G4ThreeVector &pos) {
  m_parent = parent;
  m_position = pos;
  m_fabric = fabric;
}

QVector<G4LogicalVolume *> CreateProtection::create() const {
  QVector<G4LogicalVolume *> result;
  G4double lastOuter = geometry::sabat::dectorSize + 1. * cm;
  for (auto it = m_names.constBegin(); it != m_names.constEnd(); ++it) {
    const auto index = it - m_names.begin();
    auto tube = createTube(index, lastOuter);
    auto sphere = createSphere(index, lastOuter);
    result << tube << sphere;
  }
  return result;
}

G4LogicalVolume *CreateProtection::createTube(const int index,
                                              G4double &lastOuter) const {
  const auto innerR = lastOuter;
  const auto outerR = lastOuter + (index + 1) * tubeDeepth;
  G4ThreeVector tubsPos =
      G4ThreeVector(m_position.x(), m_position.y(), m_position.z() - tubeSizeZ);
  ProtectionTube tube(innerR, outerR, tubeSizeZ, m_names.at(index) + "Tube",
                      m_materials.at(index), tubsPos, m_colours.at(index));
  const auto tubeProp = tube.getGeometryProperty();
  auto tubeGeom = m_fabric->createGeometryElement(tubeProp, m_parent);
  return tubeGeom->construct(checkOverlaps);
}

G4LogicalVolume *CreateProtection::createSphere(const int index,
                                                G4double &lastOuter) const {
  const auto innerR = lastOuter;
  const auto outerR = lastOuter + (index + 1) * tubeDeepth;
  ProtectionSphere sphere(innerR, outerR, m_names.at(index) + "Sphere",
                          m_materials.at(index), m_position,
                          m_colours.at(index));
  const auto SphereProp = sphere.getGeometryProperty();
  auto sphereGeom = m_fabric->createGeometryElement(SphereProp, m_parent);
  lastOuter = outerR;
  return sphereGeom->construct(checkOverlaps);
}

void CreateProtection::setCheckOverlaps(bool value) { checkOverlaps = value; }

}  // namespace sabat
}  // namespace geometry
