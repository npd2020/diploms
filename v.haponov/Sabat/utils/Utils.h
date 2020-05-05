#pragma once

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QTimer>

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <typeinfo>

#include "G4Colour.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

namespace {
constexpr auto _logFormat =
    "%1 %2 : [%3](%4)::%5\n";  // Flag Time Class Function data
constexpr auto _timeFormat = "hh:mm:ss.zzz";
constexpr auto _logDir = "sabat_log/";
constexpr auto _log_fileName_pattern = "s_log_%1.log";
constexpr auto _spect_file_pattern = "spectr%1.%2";
constexpr auto _res_spectr_file_pattern = "spectr_res%1.txt";
constexpr auto _spectr_file_dir = "sabat_spectr/";

static const char *log(const char *const &_lflag, const char *const &_lclass,
                       const char *const &_lfunc, const char *const &_ldata) {
  const auto _time = QDateTime::currentDateTime().time().toString(_timeFormat);
  const auto _log = QString(_logFormat)
                        .arg(_lflag)
                        .arg(_time)
                        .arg(_lclass)
                        .arg(_lfunc)
                        .arg(_ldata);
  const auto _res = _log.toUtf8().data();
  return _res;
}
}  // namespace

namespace LogInfo {

enum class LogFlags { Info, Warning, Critical, Error };
static const std::map<LogFlags, const char *> flagsMap = {
    {LogFlags::Info, "Info"},
    {LogFlags::Warning, "Warning"},
    {LogFlags::Critical, "Critical"},
    {LogFlags::Error, "ERROR"}};
static const char *str(const LogFlags &flag) { return flagsMap.at(flag); }

// static LogFlags flag(const char *const &_lflag) {
//    for (auto it = flagsMap.cbegin(); it != flagsMap.cend(); ++it) {
//        if (it->second == _lflag) {
//            return it->first;
//        }
//    }
//}

template <typename T>
static void Log(const char *const &_func, const char *const &_log,
                const LogFlags &_lflag = LogFlags::Info) {
  const auto _nclass = typeid(T).name();
  const auto log_str = log(str(_lflag), _nclass, _func, _log);
  qDebug() << log_str;
}

template <typename T>
static void FLog(const char *const &_func, const char *const &_log,
                 const LogFlags &_lflag = LogFlags::Info) {
  const auto _nclass = typeid(T).name();
  const auto log_str = log(str(_lflag), _nclass, _func, _log);
  const auto htime = QDateTime::currentDateTime().time().hour();
  const auto _fname =
      QString(_log_fileName_pattern).arg(QString::number(htime));
  const auto _fnameDir = QDir(_logDir).filePath(_fname);
  if (!QFile(_fnameDir).exists()) {
    QDir().mkpath(_logDir);
  }
  auto log_stream = std::ofstream(_fnameDir.toStdString(), std::ios::app);
  log_stream << log_str;
  log_stream.close();
}
}  // namespace LogInfo

namespace utils {

constexpr auto _participalAmmount = 100000;
constexpr int NOBINS = 1024 * 16;  // * 256 / 2;

namespace material {

struct MaterialProperty {
  G4String m_chemicalFormula;
  G4String m_name;
  QMap<G4String, G4int> m_elList;
  G4double m_density;
};

struct Au_mineral : public MaterialProperty {
  Au_mineral() {
    m_chemicalFormula = "Аg3AuS2";
    m_name = "AuMineral";
    m_elList["Ag"] = 3;
    m_elList["Au"] = 1;
    m_elList["S"] = 2;
    m_density = 9.22 * g / cm3;
  }
};

}  // namespace material
namespace sabat {
static const G4String submarineName = "SabatSubmarine";
static const G4String bottomName = "SabatBottom";
static const G4String targetName = "SabatTarget";
static const G4String DetectorName = "SabatDetector";
static const G4String DetectorSDName = "SabatDetectorSD";
static const G4String EnviromentName = "Envelope";

constexpr G4double sourceZpos = 20. * cm;
constexpr G4double sourceXPos = 30. * cm;
constexpr G4double sourceYPos = 0;

}  // namespace sabat
class Utils {
 public:
  using vectorPtr = std::shared_ptr<std::vector<int>>;
  static void saveData(const vectorPtr &pointer, const double &hist_min,
                       const double &hist_max);
  static void squashData();

  static G4Material *MustardGas(G4NistManager *matman);
  static G4Material *materialCreator(G4NistManager *nist,
                                     const material::MaterialProperty &mProp);

  static G4ThreeVector countSourcePosition();
  static G4ThreeVector countSourceDirection();
};
namespace colours {
static const G4Colour white(1.0, 1.0, 1.0);
static const G4Colour grey(0.5, 0.5, 0.5);
static const G4Colour lgrey(.85, .85, .85);
static const G4Colour red(1.0, 0.0, 0.0);
static const G4Colour blue(0.0, 0.0, 1.0);
static const G4Colour cyan(0.0, 1.0, 1.0);
static const G4Colour magenta(1.0, 0.0, 1.0);
static const G4Colour yellow(1.0, 1.0, 0.0);
static const G4Colour orange(.75, .55, 0.0);
static const G4Colour lblue(0.0, 0.0, .75);
static const G4Colour lgreen(0.0, .75, 0.0);
static const G4Colour green(0.0, 1.0, 0.0);
static const G4Colour brown(0.7, 0.4, 0.1);
}  // namespace colours

class G4CSGSolid;

namespace geometry {
enum class GeometrySolid { Box, Sphere, Tube };
struct GeometryProp {
  G4double SizeX = 0;
  G4double SizeY = 0;
  G4double SizeZ = 0;
  G4double Depth = 0;
  G4double innerR = 0;
  G4double outerR = 0;
  G4double PhiMin = 0;
  G4double PhiMax = 0;
  G4double ThetaMin = 0;
  G4double ThetaMax = 0;
  G4Colour Colour = colours::white;
  G4String Material = "";
  G4ThreeVector Position = {0, 0, 0};
  G4String Name = "";
  G4RotationMatrix *Rotation = new G4RotationMatrix;
  GeometrySolid type = GeometrySolid::Box;
  bool isCustomMaterial = false;
  G4Material *MaterialElement = nullptr;

  bool valid() const;
};

template <typename T>
static GeometryProp getGeomProperty(const T *value) {
  auto nonConstValue = const_cast<T *>(value);
  auto geomProp = reinterpret_cast<GeometryProp *>(nonConstValue);
  if (!geomProp->valid()) {
    const auto debugString =
        QString("invalid geomProp name = %1").arg(QString(geomProp->Name));
    LogInfo::FLog<GeometryProp>(__func__, debugString.toStdString().c_str(),
                                LogInfo::LogFlags::Error);
  }
  const auto debugString =
      QString("valid Geometry Property name = %1").arg(QString(geomProp->Name));
  LogInfo::FLog<GeometryProp>(__func__, debugString.toStdString().c_str());
  return *geomProp;
}
}  // namespace geometry

class counter {
 public:
  counter(const int amount);
  const counter &operator=(const counter &value);
  bool operator==(const int amount) const;
  int &operator--();
  int &at();
  int &update(const int value);

 private:
  int m_amount = 0;
};
}  // namespace utils
