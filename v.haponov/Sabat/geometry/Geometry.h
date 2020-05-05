#pragma once

#include "Utils.h"

namespace geometry {

constexpr G4double elementarySize = 1. * cm;

using GeomProp = utils::geometry::GeometryProp;
class PrimaryElementBox : public GeomProp {
 public:
  PrimaryElementBox(const G4String& name, const G4String& material,
                    const G4ThreeVector& pos, const G4Colour& colour);

  GeomProp getGeometryProperty() const;

 private:
};
namespace sabat {

constexpr G4double tubePhiMin = 0;
constexpr G4double tubePhiMax = 360.0 * deg;
constexpr G4double sphereThetaMin = 0;
constexpr G4double sphereThetaMax = 90. * deg;

constexpr G4double enviromentSize = 4. * cm;

class Enviroment : public GeomProp {
 public:
  Enviroment(const G4ThreeVector& pos,
             const G4String& name = utils::sabat::EnviromentName,
             const G4String& material = "G4_WATER",
             const G4Colour& colour = utils::colours::blue);

  GeomProp getGeometryProperty() const;

 private:
};

constexpr G4double bottomSize = 2. * m;

class Bottom : public GeomProp {
 public:
  Bottom(const G4ThreeVector& pos,
         const G4String& name = utils::sabat::bottomName,
         const G4String& material = "G4_Si",
         const G4Colour& colour = utils::colours::yellow);

  GeomProp getProperties() const;

 private:
};

constexpr G4double detectorSizeR = 3.3 * cm;
constexpr G4double detectorSizeZ = 2.853 * cm;

class DetectorSD : public GeomProp {
 public:
  DetectorSD(const G4ThreeVector& pos,
             const G4String& name = utils::sabat::DetectorSDName,
             const G4String& material = "G4_Ge",
             const G4Colour& colour = utils::colours::red);

  GeomProp getProperties() const;

 private:
};

constexpr G4double targetSize = 20. * cm;

class Target : public GeomProp {
 public:
  Target(const G4ThreeVector& pos, const G4String& material,
         const G4String& name = utils::sabat::targetName,
         const G4Colour& colour = utils::colours::brown);

  void setMaterial(G4Material* value);
  GeomProp getProperties() const;

 private:
};
}  // namespace sabat
}  // namespace geometry
