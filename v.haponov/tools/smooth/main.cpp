#include <QCoreApplication>
#include <QDebug>
#include <QFile>

#include <math.h>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <map>

constexpr double fanoFGe = 0.13;
constexpr double energyOnPair = 3.62;

double energWindow(const double &E_eV) {
  return 2.36 * energyOnPair * std::sqrt(fanoFGe * E_eV / energyOnPair);
}

double k_energWindow(const double &E_keV) {
  return 2.36 * energyOnPair *
         std::sqrt(fanoFGe * E_keV * pow(10, 3) / energyOnPair);
}

double M_energWindow(const double &E_MeV) {
  return 2.36 * energyOnPair *
         std::sqrt(fanoFGe * E_MeV * pow(10, 6) / energyOnPair);
}

std::map<double, double> readData(QFile &file) {
  std::map<double, double> dataMap;
  const auto dataMas = file.readAll().split('\n');
  file.close();
  for (const auto &el : dataMas) {
    if (el.isEmpty()) {
      continue;
    }
    auto dataPair = el.split(' ');
    dataPair.removeAll("");
    if (dataPair.size() != 2) {
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
  return dataMap;
}

void write(const std::map<double, double> &map) {
  const auto normalize = 25 * 4 * 3.1415 * pow(10, 6);
  auto resFile = std::ofstream("result_file.txt");
  for (auto it = map.cbegin(); it != map.cend(); ++it) {
    resFile << std::setw(15) << it->first << " " << std::setw(15)
            << it->second / normalize << " " << std::setw(15) << '\n';
  }
  resFile.close();
}

std::map<double, double> smooth(const std::map<double, double> &data) {
  std::map<double, double> res;
  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    const auto ev_energ_bin = M_energWindow(it->first);
    const auto last_bin_value = it->first + ev_energ_bin / pow(10, 6);
    auto bin_value = it->first;
    auto amount_value = it->second;
    int counter = 1;
    while (bin_value < last_bin_value) {
      ++it;
      ++counter;
      bin_value += it->first;
      amount_value += it->second;
    }
    if (bin_value >= last_bin_value) {
      const auto smtEnerg = bin_value / counter;
      const auto smthAmount = amount_value / counter;
      res[smtEnerg] = smthAmount;
    } else {
      qDebug() << "smth happen wrong";
    }
  }
  return res;
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  //  const auto _first_file = QString(argv[1]);
  const auto _first_file = "fon2.txt";

  if (!QFile(_first_file).exists()) {
    qDebug() << "file: " << _first_file << "not exist";
    return a.exec();
  }
  QFile file(_first_file);
  file.open(QIODevice::ReadOnly);
  std::map<double, double> dataMap = readData(file);
  file.close();

  write(smooth(dataMap));

  return a.exec();
}
