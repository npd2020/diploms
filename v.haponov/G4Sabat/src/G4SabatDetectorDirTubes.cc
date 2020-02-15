#include "G4SabatDetectorDirTubes.hh"
G4DetectorDirTubs::G4DetectorDirTubs(const int &tubeType, const G4String &name, const G4String &material,
                                     const G4Colour &colour, const G4double &innerR, const G4double &outerR,
                                     const G4double &height, G4LogicalVolume *parent)
    : G4SabatDirTube(material, colour, name, innerR, outerR, height, parent)
{
    qDebug() << "[Construction]: G4DetectorDirTubs::G4DetectorDirTubs {full} status:<start>";
    Sabat::tubeTypes type = static_cast<Sabat::tubeTypes>(tubeType);
    qDebug() << "[Construction]: G4DetectorDirTubs::G4DetectorDirTubs {full} status:<inWork> type =" << type;
    //    rot->rotateY(Sabat::tubeRotZ);
    if (type == Sabat::tubeTypes::Pb_first_internal_tube)
    {
        setInnerR(Sabat::PbInternalDirTube::internR);
        setOuterR(Sabat::PbInternalDirTube::outerR);
        setHeight(Sabat::dirTubesHeight);
        setColour(Sabat::PbInternalDirTube::colour);
        setMaterialName(Sabat::PbInternalDirTube::material);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else if (type == Sabat::tubeTypes::B_internal_tube)
    {
        setInnerR(Sabat::BInternalDirTube::internR);
        setOuterR(Sabat::BInternalDirTube::outerR);
        setHeight(Sabat::dirTubesHeight);
        setColour(Sabat::BInternalDirTube::colour);
        setMaterialName(Sabat::BInternalDirTube::material);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else if (type == Sabat::tubeTypes::Pb_outer_tube)
    {
        setInnerR(Sabat::PbOuterDirTube::internR);
        setOuterR(Sabat::PbOuterDirTube::outerR);
        setHeight(Sabat::dirTubesHeight);
        setColour(Sabat::PbOuterDirTube::colour);
        setMaterialName(Sabat::PbOuterDirTube::material);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else
        qDebug() << tubeType << "is not a tube";
    qDebug() << "[Construction]: G4DetectorDirTubs::G4DetectorDirTubs {full} status:<finished>";
}

G4DetectorDirTubs::~G4DetectorDirTubs()
{
}

G4DetectorSphere::G4DetectorSphere(const int &tubeType, const G4String &name, const G4String &material,
                                   const G4Colour &colour, const G4double &innerR, const G4double &outerR,
                                   const G4double &tetaMin, const G4double &tetaMax, G4LogicalVolume *parent)
    : G4SabatDirSphere(material, colour, name, innerR, outerR, tetaMin, tetaMax, parent)
{
    //    rot->rotateY(Sabat::tubeRotZ);
    qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<start>";
    Sabat::tubeTypes type = static_cast<Sabat::tubeTypes>(tubeType);

    qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> type = " << type;
    if (type == Sabat::tubeTypes::Pb_first_internal_sphr)
    {
        setInnerR(Sabat::PbInternalSphr::internR);
        setOuterR(Sabat::PbInternalSphr::outerR);
        setColour(Sabat::PbInternalSphr::colour);
        setMaterialName(Sabat::PbInternalSphr::material);
        setPhiMax(Sabat::phiMaxSphrTube);
        setTetaMin(Sabat::sphrTetaMin);
        setTetaMax(Sabat::sphrTetaMax);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else if (type == Sabat::tubeTypes::B_internal_sphr)
    {
        setInnerR(Sabat::BInternalSphr::internR);
        setOuterR(Sabat::BInternalSphr::outerR);
        setColour(Sabat::BInternalSphr::colour);
        setMaterialName(Sabat::BInternalSphr::material);
        setPhiMax(Sabat::phiMaxSphrTube);
        setTetaMin(Sabat::sphrTetaMin);
        setTetaMax(Sabat::sphrTetaMax);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else if (type == Sabat::tubeTypes::Pb_outer_sphr)
    {
        setInnerR(Sabat::PbOuterSphr::internR);
        setOuterR(Sabat::PbOuterSphr::outerR);
        setColour(Sabat::PbOuterSphr::colour);
        setMaterialName(Sabat::PbOuterSphr::material);
        setPhiMax(Sabat::phiMaxSphrTube);
        setTetaMin(Sabat::sphrTetaMin);
        setTetaMax(Sabat::sphrTetaMax);
        qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<inWork> set parametr "
                    "succssed ";
    }
    else
        qDebug() << tubeType << "is not a sphere";

    qDebug() << "[Construction]: G4DetectorSphere::G4DetectorSphere {full} status:<done>";
}

G4DetectorSphere::~G4DetectorSphere()
{
}

G4SabatDirectionElement::G4SabatDirectionElement(const int &typeP, const G4String &name,
                                                 const G4bool &checkOverlaps, const G4ThreeVector &position,
                                                 G4LogicalVolume *parent)
{
    qDebug() << "[Construction]: G4SabatDirectionElement::G4SabatDirectionElement {full} status:<start>";
    Sabat::tubeTypes type = static_cast<Sabat::tubeTypes>(typeP);
    qDebug()
        << "[Construction]: G4SabatDirectionElement::G4SabatDirectionElement {full} status:<inWork> type = "
        << type;
    if (type == Sabat::tubeTypes::Pb_internal)
    {
        G4DetectorSphere *sphr =
            new G4DetectorSphere(Sabat::tubeTypes::Pb_first_internal_sphr, name + "Sphr");
        sphr->setParent(parent);
        sphr->setPosition(position);
        sphr->construct(checkOverlaps);
        G4DetectorDirTubs *tube =
            new G4DetectorDirTubs(Sabat::tubeTypes::Pb_first_internal_tube, name + "Tube");
        tube->setParent(sphr->getCurrent());
        G4double tx = 0. * cm, ty = 0. * cm, tz = -tube->getHeight();
        G4ThreeVector tubePosition = G4ThreeVector(tx, ty, tz);
        tube->setPosition(tubePosition);
        tube->construct(checkOverlaps);
    }
    else if (type == Sabat::tubeTypes::B_internal)
    {
        G4DetectorSphere *sphr = new G4DetectorSphere(Sabat::tubeTypes::B_internal_sphr, name + "Sphr");
        sphr->setParent(parent);
        sphr->setPosition(position);
        sphr->construct(checkOverlaps);
        G4DetectorDirTubs *tube = new G4DetectorDirTubs(Sabat::tubeTypes::B_internal_tube, name + "Tube");
        tube->setParent(sphr->getCurrent());
        G4double tx = 0. * cm, ty = 0. * cm, tz = -tube->getHeight();
        G4ThreeVector tubePosition = G4ThreeVector(tx, ty, tz);
        tube->setPosition(tubePosition);
        tube->construct(checkOverlaps);
    }
    else if (type == Sabat::tubeTypes::Pb_outer)
    {
        G4DetectorSphere *sphr = new G4DetectorSphere(Sabat::tubeTypes::Pb_outer_sphr, name + "Sphr");
        sphr->setParent(parent);
        sphr->setPosition(position);
        sphr->construct(checkOverlaps);
        G4DetectorDirTubs *tube = new G4DetectorDirTubs(Sabat::tubeTypes::Pb_outer_tube, name + "Tube");
        tube->setParent(sphr->getCurrent());
        G4double tx = 0. * cm, ty = 0. * cm, tz = -tube->getHeight();
        G4ThreeVector tubePosition = G4ThreeVector(tx, ty, tz);
        tube->setPosition(tubePosition);
        tube->construct(checkOverlaps);
    }
    else
        qDebug() << type << "is not a direction";
    qDebug() << "[Construction]: G4SabatDirectionElement::G4SabatDirectionElement {full} status:<done>";
}

G4SabatDirectionElement::~G4SabatDirectionElement()
{
}
