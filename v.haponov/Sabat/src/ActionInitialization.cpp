/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.h"
#include "EventAction.h"
#include "PrimaryGeneratorAction.h"
#include "RunAction.h"
#include "SensitiveDetector.h"
#include "SteppingAction.h"
#include "SteppingVerbose.h"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization() {}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}

void ActionInitialization::Build() const {
  SetUserAction(new PrimaryGeneratorAction);

  RunAction* runAction = new RunAction;
  SetUserAction(runAction);

  EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));
}

G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const {
  return new SteppingVerbose();
}
