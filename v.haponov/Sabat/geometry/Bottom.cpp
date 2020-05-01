#include "Bottom.h"
namespace sabat {
namespace target {

Target::Target(const G4double &materialPart, G4LogicalVolume *parent) {
  m_parent = parent;
  m_upart = materialPart;
}

G4LogicalVolume *Target::getVolume() const {}

GeomProp Target::geometry() const {
  const auto targetVolume = sizeX * sizeY * sizeZ;
  const auto primaryElementAmount =
      targetVolume * m_upart / geometry::elementarySize;
  return GeomProp();
}
}  // namespace target
}  // namespace sabat
