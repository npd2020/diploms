#pragma once

/// \file PrimaryGeneratorAction.h
/// \brief Definition of the PrimaryGeneratorAction class

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
 public:
  PrimaryGeneratorAction();
  virtual ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
  const G4ParticleGun* GetParticleGun() const;

 private:
  G4ParticleGun* fParticleGun;  // pointer a to G4 gun class
  G4Box* fEnvelopeBox;
};
