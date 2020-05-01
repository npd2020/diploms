#pragma once

#include "Utils.h"

namespace sabat {
constexpr G4double sizeX = 300. * cm;
constexpr G4double sizeY = 200. * cm;
constexpr G4double sizeZ = 1. * m;
static const G4Colour colour = utils::colours::blue;
static const G4String material = "G4_Al";
static const G4String name = "Submarine";
static const utils::geometry::GeometrySolid type = utils::geometry::GeometrySolid::Box;

using GeomProp = utils::geometry::GeometryProp;
class Submarine {
public:
    static GeomProp getSubmarineProp();
};
}
