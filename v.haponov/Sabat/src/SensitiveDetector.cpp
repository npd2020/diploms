#include "SensitiveDetector.h"

#include <QMutex>

#include <fstream>
#include <iostream>

#include <G4Step.hh>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include <QDebug>

SensitiveDetector::SensitiveDetector(G4String name)
    : G4VSensitiveDetector(name)
    , HIST_MAX(10 * MeV)
    , HIST_MIN(0 * MeV) {
    LogInfo::FLog<SensitiveDetector>(__func__, "create");
    std::fill(histogram->begin(), histogram->end(), 0);
    std::fill(histogram_angle->begin(), histogram_angle->end(), 0);
}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* history) {
    m_counter--;
    double energy = step->GetPreStepPoint()->GetKineticEnergy();
    double bin_width = (HIST_MAX - HIST_MIN) / utils::NOBINS;
    // Participal filter
    //  if (step->GetTrack()->GetDefinition()->GetParticleName() != "gamma") {
    //    return true;
    //  }
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
    if (m_counter == 0) {
        utils::Utils::saveData(histogram, HIST_MIN, HIST_MAX);
        m_counter = utils::_participalAmmount;
    }
    return true;
}

SensitiveDetector::~SensitiveDetector() {
    utils::Utils::saveData(histogram, HIST_MIN, HIST_MAX);
    utils::Utils::squashData();
    LogInfo::FLog<SensitiveDetector>(__func__, "delete");
}
