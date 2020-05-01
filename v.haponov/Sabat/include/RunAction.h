#pragma once

#include <memory>

#include "G4Accumulable.hh"
#include "G4RadioactiveDecay.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

using decayPtr = std::unique_ptr<G4RadioactiveDecay>;
class RunAction : public G4UserRunAction {
 public:
  RunAction();
  virtual ~RunAction();

  // virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

  void AddEdep(G4double edep);

 private:
  G4Accumulable<G4double> fEdep;
  G4Accumulable<G4double> fEdep2;
};
