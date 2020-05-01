#include "GeometryFabric.h"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"

namespace geometry {

GeomPtr GeometryFabric::createGeometryElement(const GeomProp &properties,
                                              G4LogicalVolume *parent) {
  auto solid = createSolid(properties);
  solid->SetName(properties.Name);
  LogInfo::FLog<GeometryFabric>(__func__, properties.Name);
  auto geomElement = GeomPtr(new BaseElement(
      properties.Name, properties.Material, properties.Colour, parent,
      properties.isCustomMaterial, properties.MaterialElement));
  geomElement->setPosition(properties.Position);
  geomElement->setRotation(properties.Rotation);
  geomElement->createVolume(solid);
  LogInfo::FLog<GeometryFabric>(__func__, "Done");
  return geomElement;
}

G4CSGSolid *GeometryFabric::createSolid(const GeomProp &properties) {
  const auto type = properties.type;
  switch (type) {
    case SolidType::Tube: {
      auto solid =
          new G4Tubs("", properties.innerR, properties.outerR, properties.SizeZ,
                     properties.PhiMin, properties.PhiMax);
      LogInfo::FLog<GeometryFabric>(__func__, "Tube");

      return solid;
    }
    case SolidType::Box: {
      auto solid =
          new G4Box("", properties.SizeX, properties.SizeY, properties.SizeZ);
      LogInfo::FLog<GeometryFabric>(__func__, "Box");
      return solid;
    }

    case SolidType::Sphere: {
      auto solid = new G4Sphere("", properties.innerR, properties.outerR,
                                properties.PhiMin, properties.PhiMax,
                                properties.ThetaMin, properties.ThetaMax);
      LogInfo::FLog<GeometryFabric>(__func__, "Sphere");
      return solid;
    }
  }
}
}  // namespace geometry
