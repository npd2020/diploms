#include <QCoreApplication>

#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMap>

#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <ostream>

const auto file_name_patter = "spectr%1_part%2-%3Mev.txt";
const auto res_folder_name = "res_spectrum/";
const auto root_folder = "../sabat_spectr";

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  const auto fileName = QDir(root_folder).filePath(QString(argv[1]));
  const auto maxEnerg = 10;
  const auto partsAmout = 10;

  if (!QFile(fileName).exists()) {
    qDebug() << "File " << fileName << " not exist";
    return a.exec();
  }
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Error during file " << fileName << " open";
  }

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
  const auto _time = QDateTime::currentDateTime().time().toString();
  const auto energOffset = maxEnerg / partsAmout;
  size_t i = 0, index = 0;
  const auto subfolder = fileName.split('.').first();
  const auto dir = res_folder_name + subfolder;
  if (!QDir(res_folder_name).exists()) {
    if (!QDir().mkpath(dir)) {
      qDebug() << "folder for result was created";
    }
  }
  const auto maxItem = dataMap.size() / partsAmout;
  for (auto it = dataMap.cbegin(); it != dataMap.cend(); ++it) {
    index++;
    const auto minE = QString::number(i * energOffset);
    const auto maxE = QString::number(i * energOffset + energOffset);
    const auto resFileName =
        QString(file_name_patter).arg(_time).arg(minE).arg(maxE);
    const auto filePath = QDir(dir).filePath(resFileName).toStdString();
    auto resFile = std::ofstream(filePath, std::ios::app);
    resFile << std::setw(15) << it->first << " " << std::setw(15) << it->second
            << '\n';
    resFile.close();
    if (index == maxItem) {
      i++;
      index = 0;
    }
  }
  return a.exec();
}
