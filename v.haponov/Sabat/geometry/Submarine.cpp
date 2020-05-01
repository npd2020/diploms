#include "Submarine.h"

namespace sabat {

GeomProp Submarine::getSubmarineProp() {
    GeomProp prop;
    prop.SizeX = sizeX;
    prop.SizeY = sizeY;
    prop.SizeZ = sizeZ;
    prop.Colour = colour;
    prop.Material = material;
    prop.Name = name;
    prop.type = type;
    G4ThreeVector position = { 0, 0, sizeZ / 2 };
    prop.Position = position;
    return prop;
}
}
