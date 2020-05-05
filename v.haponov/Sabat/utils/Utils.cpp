#include "Utils.h"

#include "G4Box.hh"
#include "G4LogicalVolumeStore.hh"
#include "Randomize.hh"

namespace utils {

const auto timeFormat = QString("_%1_%2_%3");
void Utils::saveData(const vectorPtr &pointer, const double &hist_min,
                     const double &hist_max) {
  const auto _time = QDateTime::currentDateTime().time().toString().split(':');
  const auto _strTime =
      QString(timeFormat).arg(_time.at(0)).arg(_time.at(1)).arg(_time.at(2));
  const auto _fname = QString(_spect_file_pattern).arg(_strTime).arg("txt");
  const auto _fnameDir = QDir(_spectr_file_dir).filePath(_fname);
  if (!QFile(_fnameDir).exists()) {
    QDir().mkpath(_spectr_file_dir);
  }
  auto file = std::ofstream(_fnameDir.toStdString());
  double bin_width = (hist_max - hist_min) / NOBINS;
  for (int i = 0; i < NOBINS; i++) {
    double energy = i * bin_width + hist_min;
    file << std::setw(15) << energy / MeV << " " << std::setw(15)
         << pointer->at(i) << '\n';
  }
  file.close();
  LogInfo::FLog<std::ofstream>(__func__, "successed data saving");
}

void Utils::squashData() {
  const auto currentDir = QDir(_spectr_file_dir).absolutePath();
  const auto allFiles = QDir(currentDir).entryList();
  std::map<double, double> dataMap;
  for (const auto &el : allFiles) {
    const auto fname = QDir(_spectr_file_dir).filePath(el);
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
      LogInfo::FLog<QFile>(__func__, fname.toStdString().c_str(),
                           LogInfo::LogFlags ::Error);
      continue;
    }
    const auto dataMas = file.readAll().split('\n');
    file.close();
    for (const auto &el : dataMas) {
      if (el.isEmpty()) {
        LogInfo::FLog<QList<QByteArray>>(__func__, fname.toStdString().c_str(),
                                         LogInfo::LogFlags ::Warning);
        continue;
      }
      auto dataPair = el.split(' ');
      dataPair.removeAll("");
      if (dataPair.size() != 2) {
        LogInfo::FLog<QList<QByteArray>>(__func__, fname.toStdString().c_str(),
                                         LogInfo::LogFlags ::Warning);
        continue;
      }
      const auto p_energ = dataPair.at(0).toDouble();
      const auto p_amount = dataPair.at(1).toDouble();
      if (dataMap.find(p_energ) == dataMap.end()) {
        dataMap[p_energ] = p_amount;
      } else {
        dataMap[p_energ] += p_amount;
      }
    }
  }
  const auto _time = QDateTime::currentDateTime().time().toString();
  const auto resFileName = QString(_res_spectr_file_pattern).arg(_time);
  auto resFile = std::ofstream(resFileName.toStdString());
  for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it) {
    resFile << std::setw(15) << it->first << " " << std::setw(15) << it->second
            << '\n';
  }
  resFile.close();
}

G4Material *Utils::MustardGas(G4NistManager *matman) {
  // Chemicla Formula C4H8Cl2S
  // C - 24 / 82 =
  // H - 8 / 82 =
  // Cl - 34 / 82
  // S - 16 / 82
  const G4double density = 1.27 * g / mole;
  const G4int nel = 4;

  //    G4Element *elC = new G4Element("Hydrogen", "H", 1., 1.01 * g / mole);
  G4Material *Material = new G4Material("S_C4H8Cl2S", density, nel);

  Material->SetChemicalFormula("C4H8Cl2S");
  Material->AddElement(matman->FindOrBuildElement("C"),
                       4 /*(24 / 82) * perCent*/);
  Material->AddElement(matman->FindOrBuildElement("H"),
                       8 /*(8 / 82) * perCent*/);
  Material->AddElement(matman->FindOrBuildElement("Cl"),
                       2 /*(34 / 82) * perCent*/);
  Material->AddElement(matman->FindOrBuildElement("S"),
                       1 /*(16 / 82) * perCent*/);
  return Material;
}

G4Material *Utils::materialCreator(G4NistManager *nist,
                                   const material::MaterialProperty &mProp) {
  const G4int nEl = mProp.m_elList.size();
  G4Material *material = new G4Material(mProp.m_name, mProp.m_density, nEl);
  material->SetChemicalFormula(mProp.m_chemicalFormula);
  const auto elList = mProp.m_elList;
  for (auto it = elList.constBegin(); it != elList.constEnd(); ++it) {
    auto key = it.key();
    auto prEl = nist->FindOrBuildElement(it.key());
    if (!prEl) {
      LogInfo::FLog<Utils>(__func__, "element do not find",
                           LogInfo::LogFlags ::Error);
      return nullptr;
    }
    material->AddElement(prEl, it.value());
  }
  return material;
}

G4ThreeVector Utils::countSourcePosition() {
  const G4double xDir = sabat::sourceXPos;
  const G4double yDir = sabat::sourceYPos;
  const G4double zDir = sabat::sourceZpos;
  return G4ThreeVector(xDir, yDir, zDir);
}

G4ThreeVector Utils::countSourceDirection() {
  const auto randCof = G4UniformRand() - 0.5;
  const G4double Delta_Y_Dir = 1. * cm * randCof;
  const G4double Delta_Z_Dir = 0. * randCof;
  const G4double Delta_X_Dir = 3. * randCof;

  const G4double xDir = -sabat::sourceXPos + Delta_X_Dir;
  const G4double yDir = -sabat::sourceYPos + Delta_Y_Dir;
  const G4double zDir = -sabat::sourceZpos + Delta_Z_Dir;

  return G4ThreeVector(xDir, yDir, zDir);
}
namespace geometry {

bool GeometryProp::valid() const {
  bool invalidSize;
  switch (type) {
    case GeometrySolid::Tube: {
      invalidSize = innerR == 0 || outerR == 0 || innerR == outerR ||
                    (PhiMax == 0 || PhiMin == PhiMax);
      if (invalidSize) {
        LogInfo::FLog<GeometryProp>(__func__, "invalid Tube",
                                    LogInfo::LogFlags::Error);
      }
      break;
    }
    case GeometrySolid::Sphere: {
      invalidSize = (innerR == 0) || (outerR == 0) || (innerR == outerR) ||
                    (PhiMax == 0 || PhiMin == PhiMax) ||
                    (ThetaMax == 0 || ThetaMin == ThetaMax);
      if (invalidSize) {
        LogInfo::FLog<GeometryProp>(__func__, "invalid Sphere",
                                    LogInfo::LogFlags::Error);
      }
      break;
    }
    default: {
      invalidSize = (SizeX == 0) || (SizeY == 0) || (SizeZ == 0);
      break;
    }
  }
  bool invalidMaterial =
      Material.isNull() || (isCustomMaterial && !MaterialElement);
  bool invalidName = Name.isNull();
  return !invalidSize && !invalidName && !invalidMaterial;
}
}  // namespace geometry

counter::counter(const int amount) { m_amount = amount; }

const counter &counter::operator=(const counter &value) {
  m_amount = value.m_amount;
  return *this;
}

bool counter::operator==(const int amount) const { return m_amount == amount; }

int &counter::operator--() {
  m_amount--;
  return m_amount;
}

int &counter::at() { return m_amount; }

int &counter::update(const int value) {
  m_amount = value;
  return m_amount;
}

// namespace geometry

}  // namespace utils
