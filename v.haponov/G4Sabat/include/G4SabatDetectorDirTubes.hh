#ifndef G4SABATDETECTORDIRTUBES_H
#define G4SABATDETECTORDIRTUBES_H
#include "G4SabatDirTube.hh"
#include "G4SabatColours.hh"
namespace Sabat {

enum tubeTypes
{
    Pb_first_internal_tube, // 0
    B_internal_tube,        // 1
    Pb_outer_tube,          // 2
    Pb_first_internal_sphr, // 3
    B_internal_sphr,        // 4
    Pb_outer_sphr,          // 5
    Pb_outer,               // 6
    Pb_internal,            // 7
    B_internal              // 8
};

const G4double sphrTetaMin = 0. * rad;
const G4double sphrTetaMax = M_PI / 2 * rad;
const G4double dirTubesHeight = 30. * cm;
const G4double phiMaxSphrTube = 2 * M_PI * rad;
const G4double phiMinSphrTube = 0. * deg;
const G4double tubeRotZ = M_PI / 4 * rad;

namespace PbInternalSphr {
    const G4double internR = 38 * cm;
    const G4double outerR = 44. * cm;
    const G4String material = "G4_Pb";
    const G4Colour colour = blue;
};

namespace PbInternalDirTube {
    const G4double internR = PbInternalSphr::internR * cos(sphrTetaMin);
    const G4double outerR = PbInternalSphr::outerR * cos(sphrTetaMin);
    const G4String material = "G4_Pb";
    const G4Colour colour = blue;
};

namespace BInternalSphr {
    const G4double internR = 44. * cm;
    const G4double outerR = 50. * cm;
    const G4String material = "G4_B";
    const G4Colour colour = brown;
};
namespace BInternalDirTube {
    const G4double internR = BInternalSphr::internR * cos(sphrTetaMin);
    const G4double outerR = BInternalSphr::outerR * cos(sphrTetaMin);
    const G4String material = "G4_B";
    const G4Colour colour = brown;
};
namespace PbOuterSphr {
    const G4double internR = 50. * cm;
    const G4double outerR = 56. * cm;
    const G4String material = "G4_Pb";
    const G4Colour colour = blue;
};
namespace PbOuterDirTube {
    const G4double internR = PbOuterSphr::internR * cos(sphrTetaMin);
    const G4double outerR = PbOuterSphr::outerR * cos(sphrTetaMin);
    const G4String material = "G4_Pb";
    const G4Colour colour = blue;
};
}

class G4DetectorDirTubs : public G4SabatDirTube
{
public:
    G4DetectorDirTubs(const int &tubeType, const G4String &name, const G4String &material = "",
                      const G4Colour &colour = white, const G4double &innerR = 0.,
                      const G4double &outerR = 0., const G4double &height = 0.,
                      G4LogicalVolume *parent = nullptr);
    ~G4DetectorDirTubs();
};
class G4DetectorSphere : public G4SabatDirSphere
{
public:
    G4DetectorSphere(const int &tubeType, const G4String &name, const G4String &material = "",
                     const G4Colour &colour = white, const G4double &innerR = 0., const G4double &outerR = 0.,
                     const G4double &tetaMin = 0., const G4double &tetaMax = 0.,
                     G4LogicalVolume *parent = nullptr);
    ~G4DetectorSphere();
};
class G4SabatDirectionElement
{
public:
    G4SabatDirectionElement(const int &typeP, const G4String &name, const G4bool &checkOverlaps,
                            const G4ThreeVector &position, G4LogicalVolume *parent);
    ~G4SabatDirectionElement();
};

#endif // G4SABATDETECTORDIRTUBES_H
