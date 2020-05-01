/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class

#include "PhysicsList.h"
#include "G4DeexPrecoParameters.hh"
#include "G4IonConstructor.hh"
#include "G4LossTableManager.hh"
#include "G4NuclearLevelData.hh"
#include "G4NuclideTable.hh"
#include "G4ParticleTypes.hh"
#include "G4PhysicsListHelper.hh"
#include "G4RadioactiveDecay.hh"
#include "G4SystemOfUnits.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4UnitsTable.hh"

PhysicsList::PhysicsList() : G4VUserPhysicsList() {
  // add new units for radioActive decays
  //
  const G4double minute = 60 * second;
  const G4double hour = 60 * minute;
  const G4double day = 24 * hour;
  const G4double year = 365 * day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour", "h", "Time", hour);
  new G4UnitDefinition("day", "d", "Time", day);
  new G4UnitDefinition("year", "y", "Time", year);

  // mandatory for G4NuclideTable
  //
  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  // read new PhotonEvaporation data set
  //
  G4DeexPrecoParameters* deex =
      G4NuclearLevelData::GetInstance()->GetParameters();
  deex->SetCorrelatedGamma(false);
  deex->SetStoreAllLevels(true);
  deex->SetMaxLifeTime(G4NuclideTable::GetInstance()->GetThresholdOfHalfLife() /
                       std::log(2.));
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle() {
  // pseudo-particles
  G4Geantino::GeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();

  // baryons
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();

  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess() {
  AddTransportation();

  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();

  G4bool ARMflag = false;
  radioactiveDecay->SetARM(ARMflag);  // Atomic Rearangement

  // need to initialize atomic deexcitation
  //
  G4LossTableManager* man = G4LossTableManager::Instance();
  G4VAtomDeexcitation* deex = man->AtomDeexcitation();
  if (!deex) {
    /// G4EmParameters::Instance()->SetFluo(true);
    G4EmParameters::Instance()->SetAugerCascade(ARMflag);
    deex = new G4UAtomicDeexcitation();
    deex->InitialiseAtomicDeexcitation();
    man->SetAtomDeexcitation(deex);
  }

  // register radioactiveDecay
  //
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());

  // printout
  //
  G4cout << "\n  Set atomic relaxation mode " << ARMflag << G4endl;
}

void PhysicsList::SetCuts() { SetCutsWithDefault(); }
