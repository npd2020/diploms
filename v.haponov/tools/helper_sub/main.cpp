#include <math.h>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <map>

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

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  const auto _first_file = QString(argv[1]);
  const auto _second_file = QString(argv[2]);

  if (!QFile(_first_file).exists()) {
    qDebug() << "file: " << _first_file << "not exist";
    return a.exec();
  }

  if (!QFile(_second_file).exists()) {
    qDebug() << "file: " << _second_file << "not exist";
    return a.exec();
  }

  QFile first(_first_file);
  if (!first.open(QIODevice::ReadOnly)) {
    qDebug() << "Error during file " << _first_file << " open";
    return a.exec();
  }
  const auto firstMap = readData(first);
  first.close();

  QFile second(_second_file);
  if (!second.open(QIODevice::ReadOnly)) {
    qDebug() << "Error during file " << _second_file << " open";
    return a.exec();
  }
  const auto secondMap = readData(second);
  second.close();

  std::map<double, double> result;
  for (auto it = firstMap.cbegin(); it != firstMap.cend(); ++it) {
    result[it->first] = it->second - secondMap.at(it->first);
  }
  write(result);
  return a.exec();
}
