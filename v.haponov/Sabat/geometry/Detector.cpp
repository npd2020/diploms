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
                                   G4RotationMatrix *rotMatrix,
                                   const G4ThreeVector &pos) {
  m_parent = parent;
  m_position = pos;
  m_fabric = fabric;
  m_rotMatrix = rotMatrix;
}

QVector<G4LogicalVolume *> CreateProtection::create(
    const bool isSourceP) const {
  QVector<G4LogicalVolume *> result;
  // env tube
  G4ThreeVector tubsPos =
      G4ThreeVector(m_position.x(), m_position.y(), m_position.z() - tubeSizeZ);
  if (isSourceP) {
    tubsPos = m_position;
  }
  ProtectionTube tube(0, geometry::sabat::detectorSizeR + 1. * cm,
                      tubeSizeZ - 1 * cm, "EnvTube", "G4_AIR", tubsPos,
                      utils::colours::cyan);
  const auto tubeProp = tube.getGeometryProperty();
  auto tubeGeom = m_fabric->createGeometryElement(tubeProp, m_parent);
  tubeGeom->setRotation(m_rotMatrix);
  result << tubeGeom->construct(checkOverlaps);

  G4double lastOuter = geometry::sabat::detectorSizeR + 1. * cm;

  if (isSourceP) {
    auto tubeP = createTube(0, lastOuter, isSourceP);
    result << tubeP;
    return result;
  }

  ProtectionSphere sphere(0, geometry::sabat::detectorSizeR + 1. * cm,
                          "EnvSphere", "G4_AIR", m_position,
                          utils::colours::cyan);

  const auto SphereProp = sphere.getGeometryProperty();
  auto sphereGeom = m_fabric->createGeometryElement(SphereProp, m_parent);
  sphereGeom->setRotation(m_rotMatrix);
  result << sphereGeom->construct(checkOverlaps);

  for (auto it = m_names.constBegin(); it != m_names.constEnd(); ++it) {
    const auto index = it - m_names.begin();
    auto tubeP = createTube(index, lastOuter);
    auto sphereP = createSphere(index, lastOuter);
    result << tubeP << sphereP;
  }

  return result;
}

G4LogicalVolume *CreateProtection::createTube(const int index,
                                              G4double &lastOuter,
                                              const bool isSourceP) const {
  const auto innerR = lastOuter;
  const auto outerR = innerR + m_sizes.at(index);

  G4ThreeVector tubsPos =
      G4ThreeVector(m_position.x(), m_position.y(), m_position.z() - tubeSizeZ);
  if (isSourceP) {
    tubsPos = m_position;
  }
  ProtectionTube tube(innerR, outerR, tubeSizeZ, m_names.at(index) + "Tube",
                      m_materials.at(index), tubsPos, m_colours.at(index));
  const auto tubeProp = tube.getGeometryProperty();
  auto tubeGeom = m_fabric->createGeometryElement(tubeProp, m_parent);
  tubeGeom->setRotation(m_rotMatrix);
  return tubeGeom->construct(checkOverlaps);
}

G4LogicalVolume *CreateProtection::createSphere(const int index,
                                                G4double &lastOuter) const {
  const auto innerR = lastOuter;
  const auto outerR = innerR + m_sizes.at(index);

  ProtectionSphere sphere(innerR, outerR, m_names.at(index) + "Sphere",
                          m_materials.at(index), m_position,
                          m_colours.at(index));
  const auto SphereProp = sphere.getGeometryProperty();
  auto sphereGeom = m_fabric->createGeometryElement(SphereProp, m_parent);
  sphereGeom->setRotation(m_rotMatrix);
  lastOuter = outerR;
  return sphereGeom->construct(checkOverlaps);
}

void CreateProtection::setCheckOverlaps(bool value) { checkOverlaps = value; }

}  // namespace sabat
}  // namespace geometry
