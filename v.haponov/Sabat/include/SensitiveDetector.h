#pragma once

#include <QMutex>
#include <memory>

#include <G4VSensitiveDetector.hh>
#include "Utils.h"

class FileManager;
class G4Step;
class G4TouchableHistory;

using vectorPtr = std::shared_ptr<std::vector<int>>;
using streamPtr = std::unique_ptr<std::ofstream>;

class SensitiveDetector : public G4VSensitiveDetector {
private:
    const double HIST_MAX;
    const double HIST_MIN;
    int m_counter = utils::_participalAmmount;
    vectorPtr histogram = vectorPtr(new std::vector<int>(utils::NOBINS));
    vectorPtr histogram_angle = vectorPtr(new std::vector<int>(utils::NOBINS));

public:
    SensitiveDetector(G4String name);
    ~SensitiveDetector();

    G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
};
