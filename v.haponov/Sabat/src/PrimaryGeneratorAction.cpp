/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.h"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

#include "Utils.h"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(0), fEnvelopeBox(0) {
  G4int n_particle = utils::_participalAmmount;
  fParticleGun = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle =
      particleTable->FindParticle(particleName = "neutron");
  fParticleGun->SetParticleDefinition(particle);

  G4ThreeVector sourceDir = utils::Utils::countSourceDirection();
  fParticleGun->SetParticleMomentumDirection(sourceDir);
  fParticleGun->SetParticleEnergy(14.5 * MeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
  G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox) {
    G4LogicalVolume* envLV = G4LogicalVolumeStore::GetInstance()->GetVolume(
        utils::sabat::EnviromentName);
    if (envLV) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if (fEnvelopeBox) {
    envSizeXY = fEnvelopeBox->GetXHalfLength() * 2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength() * 2.;
  } else {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()", "MyCode0002",
                JustWarning, msg);
  }

  //  G4double size = 0.5;
  //  G4double x0 = -15. * cm;
  //  G4double y0 = 0;
  //  G4double z0 = 10. * cm;

  G4ThreeVector sourcePos = utils::Utils::countSourcePosition();
  fParticleGun->SetParticlePosition(sourcePos);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

const G4ParticleGun* PrimaryGeneratorAction::GetParticleGun() const {
  return fParticleGun;
}
