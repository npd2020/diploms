#include "Geometry.h"
namespace geometry {

PrimaryElementBox::PrimaryElementBox(const G4String& name,
                                     const G4String& material,
                                     const G4ThreeVector& pos,
                                     const G4Colour& colour)
    : GeomProp() {
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  SizeX = elementarySize;
  SizeY = elementarySize;
  SizeZ = elementarySize;
}

GeomProp geometry::PrimaryElementBox::getGeometryProperty() const {
  return utils::geometry::getGeomProperty<PrimaryElementBox>(this);
}

namespace sabat {

Enviroment::Enviroment(const G4ThreeVector& pos, const G4String& name,
                       const G4String& material, const G4Colour& colour)
    : GeomProp() {
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  SizeX = enviromentSize;
  SizeY = enviromentSize;
  SizeZ = enviromentSize;
}

GeomProp Enviroment::getGeometryProperty() const {
  return utils::geometry::getGeomProperty<Enviroment>(this);
}

Bottom::Bottom(const G4ThreeVector& pos, const G4String& name,
               const G4String& material, const G4Colour& colour)
    : GeomProp() {
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  SizeX = bottomSize;
  SizeY = bottomSize;
  SizeZ = bottomSize / 2;
}

GeomProp Bottom::getProperties() const {
  return utils::geometry::getGeomProperty<Bottom>(this);
}

DetectorSD::DetectorSD(const G4ThreeVector& pos, const G4String& name,
                       const G4String& material, const G4Colour& colour)
    : GeomProp() {
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;

  SizeZ = detectorSizeZ;
  innerR = 0;
  outerR = detectorSizeR;
  PhiMax = geometry::sabat::tubePhiMax;
  PhiMin = geometry::sabat::tubePhiMin;
  type = utils::geometry::GeometrySolid::Tube;
}

GeomProp DetectorSD::getProperties() const {
  return utils::geometry::getGeomProperty<DetectorSD>(this);
}

Target::Target(const G4ThreeVector& pos, const G4String& material,
               const G4String& name, const G4Colour& colour)
    : GeomProp() {
  Material = material;
  Name = name;
  Position = pos;
  Colour = colour;
  SizeX = targetSize;
  SizeY = targetSize / 2;
  SizeZ = targetSize / 2;
  isCustomMaterial = true;
}

void Target::setMaterial(G4Material* value) { MaterialElement = value; }

GeomProp Target::getProperties() const {
  return utils::geometry::getGeomProperty<Target>(this);
}

}  // namespace sabat
}  // namespace geometry
