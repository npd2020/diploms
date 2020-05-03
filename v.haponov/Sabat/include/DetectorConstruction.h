/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
#pragma once

#include <memory>

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

#include "SensitiveDetector.h"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction {
 public:
  DetectorConstruction();
  virtual ~DetectorConstruction();

  virtual G4VPhysicalVolume* Construct() override;
  G4LogicalVolume* GetScoringVolume() const;
  G4LogicalVolume* GetSensetiveVolume() const;
  virtual void ConstructSDandField() override;

  void setTrackerDetector(const std::unique_ptr<SensitiveDetector>& value);

 protected:
  G4LogicalVolume* fScoringVolume;
  G4LogicalVolume* fSensetiveVoulume;
  SensitiveDetector* trackerDetector;
  std::shared_ptr<utils::counter> m_counter = std::shared_ptr<utils::counter>(
      new utils::counter(utils::_participalAmmount));
  vectorPtr m_histogram = vectorPtr(new std::vector<int>(utils::NOBINS));
};
