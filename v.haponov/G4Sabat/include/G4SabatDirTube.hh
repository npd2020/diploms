#ifndef G4SABATSUBMARINE_H
#define G4SABATSUBMARINE_H
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4SabatColours.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include <G4VPhysicalVolume.hh>
#include <G4Colour.hh>
#include <QDebug>
#include "G4Tubs.hh"
#include "G4SabatAbstractConstructionElement.hh"
#include "G4PhysicsFreeVector.hh"
#include "G4SabatSubmarineDetector.hh"
class G4SabatDirTube : public G4SabatAbstractElement
{
private:
    G4double innerR;
    G4double outerR;
    G4double height;
    G4double phiMax = 360. * deg;

public:
    G4SabatDirTube(const G4double &innerR, const G4double &outerR, const G4double &height,
                   G4SabatAbstractElement *parent);
    G4SabatDirTube(const G4String &material, const G4Colour &colour, const G4String &name,
                   const G4double &innerR, const G4double &outerR, const G4double &height,
                   G4LogicalVolume *parent = nullptr);
    ~G4SabatDirTube();

public:
    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) override;

    G4double getHeight() const;

protected:
    void setInnerR(const G4double &value);
    void setOuterR(const G4double &value);
    void setHeight(const G4double &value);
};
class G4SabatDirSphere : public G4SabatAbstractElement
{
private:
    G4double innerR;
    G4double outerR;
    G4double phiMax = 360. * deg;
    G4double tetaMax;
    G4double tetaMin;

public:
    G4SabatDirSphere(const G4double &innerR, const G4double &outerR, const G4double &tetaMin,
                     const G4double &tetaMax, G4SabatAbstractElement *parent);
    G4SabatDirSphere(const G4String &material, const G4Colour &colour, const G4String &name,
                     const G4double &innerR, const G4double &outerR, const G4double &tetaMin,
                     const G4double &tetaMax, G4LogicalVolume *parent = nullptr);
    ~G4SabatDirSphere();

    virtual G4LogicalVolume *construct(const G4bool &checkOverlaps) override;

    G4double getOuterR() const;

    G4double getInnerR() const;

protected:
    void setInnerR(const G4double &value);
    void setOuterR(const G4double &value);
    void setPhiMax(const G4double &value);
    void setTetaMax(const G4double &value);
    void setTetaMin(const G4double &value);
};
#endif // G4SABATSUBMARINE_H
