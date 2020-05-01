/// \file SteppingVerbose.hh
/// \brief Definition of the SteppingVerbose class
#pragma once

#include "G4SteppingVerbose.hh"

class SteppingVerbose : public G4SteppingVerbose {
 public:
  SteppingVerbose();
  ~SteppingVerbose();

  virtual void TrackingStarted();
  virtual void StepInfo();
};
