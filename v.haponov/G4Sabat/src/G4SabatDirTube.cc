#include "G4SabatDirTube.hh"

void G4SabatDirTube::setInnerR(const G4double &value)
{
    innerR = value;
}

void G4SabatDirTube::setOuterR(const G4double &value)
{
    outerR = value;
}

void G4SabatDirTube::setHeight(const G4double &value)
{
    height = value;
}

G4double G4SabatDirTube::getHeight() const
{
    return height;
}

G4SabatDirTube::G4SabatDirTube(const G4double &innerR, const G4double &outerR, const G4double &height,
                               G4SabatAbstractElement *parent)
    : G4SabatAbstractElement(*parent)
    , innerR(innerR)
    , outerR(outerR)
    , height(height)
{
    qDebug() << "[Constructor]: G4SabatDirTube::G4SabatDirTube ";
}

G4SabatDirTube::G4SabatDirTube(const G4String &material, const G4Colour &colour, const G4String &name,
                               const G4double &innerR, const G4double &outerR, const G4double &height,
                               G4LogicalVolume *parent)
    : G4SabatAbstractElement(material, colour, name, parent)
    , innerR(innerR)
    , outerR(outerR)
    , height(height)
{
    qDebug() << "[Constructor]: G4SabatDirTube::G4SabatDirTube {full}";
}

G4SabatDirTube::~G4SabatDirTube()
{
}

G4LogicalVolume *G4SabatDirTube::construct(const G4bool &checkOverlaps)
{
    G4Tubs *solid = new G4Tubs(getName(), innerR, outerR, height, 0. * deg, phiMax);
    G4LogicalVolume *current = createVolume(solid);
    drawVolume(current, checkOverlaps);
    qDebug() << "[G4SabatDirTube]: construct {function}";
    return current;
}

void G4SabatDirSphere::setInnerR(const G4double &value)
{
    innerR = value;
}

void G4SabatDirSphere::setOuterR(const G4double &value)
{
    outerR = value;
}

void G4SabatDirSphere::setPhiMax(const G4double &value)
{
    phiMax = value;
}

void G4SabatDirSphere::setTetaMax(const G4double &value)
{
    tetaMax = value;
}

void G4SabatDirSphere::setTetaMin(const G4double &value)
{
    tetaMin = value;
}

G4double G4SabatDirSphere::getOuterR() const
{
    return outerR;
}

G4double G4SabatDirSphere::getInnerR() const
{
    return innerR;
}

G4SabatDirSphere::G4SabatDirSphere(const G4double &innerR, const G4double &outerR, const G4double &tetaMin,
                                   const G4double &tetaMax, G4SabatAbstractElement *parent)
    : G4SabatAbstractElement(*parent)
    , innerR(innerR)
    , outerR(outerR)
    , tetaMax(tetaMax)
    , tetaMin(tetaMin)
{
    qDebug() << "[Constructor]: G4SabatDirSphere::G4SabatDirSphere";
}

G4SabatDirSphere::G4SabatDirSphere(const G4String &material, const G4Colour &colour, const G4String &name,
                                   const G4double &innerR, const G4double &outerR, const G4double &tetaMin,
                                   const G4double &tetaMax, G4LogicalVolume *parent)
    : G4SabatAbstractElement(material, colour, name, parent)
    , innerR(innerR)
    , outerR(outerR)
    , tetaMax(tetaMax)
    , tetaMin(tetaMin)
{
    qDebug() << "[Constructor]: G4SabatDirSphere::G4SabatDirSphere {full}";
}

G4SabatDirSphere::~G4SabatDirSphere()
{
}

G4LogicalVolume *G4SabatDirSphere::construct(const G4bool &checkOverlaps)
{
    G4Sphere *solid = new G4Sphere(getName(), innerR, outerR, 0. * deg, phiMax, tetaMin, tetaMax);
    G4LogicalVolume *current = createVolume(solid);
    drawVolume(current, checkOverlaps);
    qDebug() << "[G4SabatDirSphere]: construct {function}";
    return current;
}
