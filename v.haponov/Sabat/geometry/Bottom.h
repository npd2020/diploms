#pragma once

#include "Geometry.h"
#include "GeometryFabric.h"

namespace sabat {

using GeomProp = utils::geometry::GeometryProp;
namespace target {

constexpr G4double sizeX = 1. * m;
constexpr G4double sizeY = 1. * m;
constexpr G4double sizeZ = 1. * m;

class Target {
 public:
  Target(const G4double &materialPart, G4LogicalVolume *parent);

  G4LogicalVolume *getVolume() const;
  GeomProp geometry() const;

 private:
  G4LogicalVolume *m_parent;
  G4LogicalVolume *m_logicalVolume;
  G4double m_upart;
};
}  // namespace target
}  // namespace sabat
