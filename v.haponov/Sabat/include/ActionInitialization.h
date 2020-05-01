/// \file ActionInitialization.hh
/// \brief Definition of the ActionInitialization class

#pragma once

#include "G4VUserActionInitialization.hh"

/// Action initialization class.

class ActionInitialization : public G4VUserActionInitialization {
 public:
  ActionInitialization();
  virtual ~ActionInitialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;
  virtual G4VSteppingVerbose* InitializeSteppingVerbose() const;
};
