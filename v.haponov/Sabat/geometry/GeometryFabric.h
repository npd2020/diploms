#pragma once

#include "BaseElement.h"

namespace geometry {

using GeomProp = utils::geometry::GeometryProp;
using GeomPtr = std::shared_ptr<BaseElement>;
using SolidType = utils::geometry::GeometrySolid;

class GeometryFabric {
public:
    GeomPtr createGeometryElement(const GeomProp& properties, G4LogicalVolume* parent);

private:
    G4CSGSolid* createSolid(const GeomProp& properties);
    G4CSGSolid* createBox(G4CSGSolid* solid, const GeomProp& properties);
    G4CSGSolid* createTube(G4CSGSolid* solid, const GeomProp& properties);
    G4CSGSolid* createSphere(G4CSGSolid* solid, const GeomProp& properties);
};
}
