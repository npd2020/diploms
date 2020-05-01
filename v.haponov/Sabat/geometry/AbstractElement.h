#pragma once

#include "memory"

#include "G4CSGSolid.hh"
#include "G4LogicalVolume.hh"

namespace geometry {

using G4LVolumePtr = std::shared_ptr<G4LogicalVolume>;
using G4SolidPtr = std::shared_ptr<G4CSGSolid>;

class AbstractElement {
public:
    virtual G4LogicalVolume *construct(const G4bool checkOverlaps) = 0;
    virtual G4LogicalVolume *createVolume(G4CSGSolid *solidVolume) = 0;

protected:
    virtual void drawVolume(const G4bool checkOverlaps) = 0;
};
}
