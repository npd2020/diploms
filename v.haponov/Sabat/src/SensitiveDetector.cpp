#include "SensitiveDetector.h"

#include <QMutex>

#include <fstream>
#include <iostream>
#include <thread>

#include <G4Step.hh>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include <QDebug>

SensitiveDetector::SensitiveDetector(vectorPtr histogramPtr,
                                     std::shared_ptr<utils::counter> counter,
                                     G4String name)
    : G4VSensitiveDetector(name), HIST_MAX(10 * MeV), HIST_MIN(0 * MeV) {
  this->histogram = histogramPtr;
  LogInfo::FLog<SensitiveDetector>(__func__, "create");
  std::fill(histogram_angle->begin(), histogram_angle->end(), 0);
  m_counter = counter;
}

G4bool SensitiveDetector::ProcessHits(G4Step* step,
                                      G4TouchableHistory* history) {
  m_counter->at()--;
  double energy = step->GetPreStepPoint()->GetKineticEnergy();
  double bin_width = (HIST_MAX - HIST_MIN) / utils::NOBINS;
  // Participal filter
  if (step->GetTrack()->GetDefinition()->GetParticleName() != "gamma") {
    return true;
  }
  int index = int(floor((energy - HIST_MIN) / bin_width));
  if (index >= 0 && index < utils::NOBINS) {
    histogram->at(index)++;
  };
  G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
  G4ThreeVector* centerVector = new G4ThreeVector(0, 0, 1);
  double angle = ang.angle(*centerVector);
  double bin_width_ang = (3.14) / utils::NOBINS;
  index = int(floor((angle) / bin_width_ang));
  if (index >= 0 && index < utils::NOBINS) {
    histogram_angle->at(index)++;
  }
  // Kill pariciple after target
  //  step->GetTrack()->SetTrackStatus(fStopAndKill);
  if (m_counter->at() <= 0) {
    std::thread saveThread(utils::Utils::saveData, histogram, HIST_MIN,
                           HIST_MAX);
    saveThread.join();
    m_counter->update(utils::_participalAmmount);
  }
  return true;
}

SensitiveDetector::~SensitiveDetector() {
  utils::Utils::saveData(histogram, HIST_MIN, HIST_MAX);
  LogInfo::FLog<SensitiveDetector>(__func__, "delete");
}
