#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "DetectorSD.hh"
// Используем пространство имен std, что бы не писать много где std::
using namespace std;
// Конструктор чувствительной области, по умолчанию инициализируем нижнюю и верхнюю границы гистограммы 
DetectorSD::DetectorSD(G4String name): G4VSensitiveDetector(name), HIST_MAX(10*MeV), HIST_MIN(0 *MeV)
{
  // Обнуляем гистограммы
  for(int i = 0; i<NOBINS; i++){
    histogram[i] = 0;
  }
}
//Вызывается на каждом шаге моделрования частицы, когда она попадает в этот чувствительный объем
G4bool DetectorSD::ProcessHits(G4Step* step, G4TouchableHistory* history)
{
  // Получаем кинетическую энергии частицы с предыдущего шага, т.е. начальную
  // кинетическую энегрию перед текущим шагом
  double energy = step->GetPreStepPoint()->GetKineticEnergy();
  //double energy = step->GetTotalEnergyDeposit();
  // Вычисляем ширину бина (интерва) гистограммы
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  // Задаем единичный вектор в направлении оси OY
  G4ThreeVector *centerVector = new G4ThreeVector(0, 1, 0);
  // Получаем вектор направления частицы
  G4ThreeVector ang = step->GetPreStepPoint()->GetMomentumDirection();
  // Применяем фунцию класса G4ThreeVector - находим угол относительно вектора centerVector
  double angle=ang.angle(*centerVector);
  // Если имя частицы протон (gamma), тогда заполняем гистограммы    ////&& angle < 1.58
  if(step->GetTrack()->GetDefinition()->GetParticleName() == "gamma"){
    // Определяем индекс (номер) бина гистограммы энергии
    int index = int(floor((energy-HIST_MIN)/bin_width));
    // Добавляем +1 в соответствующий бин
    if(index >= 0 && index < NOBINS)
      histogram[index]++;
  }
  // Так как мы хотим только измерить параметры частиц после прохождения
  // мишени и не интересуемся дальнейшей их судьбой в детекторе, то их убиваем -
  // устанавливаем статус остановлено и уничтожено (fStopAndKill)
  //step->GetTrack()->SetTrackStatus(fStopAndKill);
  return true;
}
DetectorSD::~DetectorSD()
{
  // В деструкторе выводим гистограммы в файлы
  // Открываем файл (существующий файл полностью перезаписывается)
  std::ofstream file("fon.txt");
  file << "Energy" << " " << "N" << '\n';
  // Вычисляем ширину бина
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  // Выводим гистограмму
  for(int i = 0; i<NOBINS; i++)
  {
    // Вычисляем энергию
    double energy = i*bin_width + HIST_MIN;
    // Выводим в файл
    file << energy/MeV << " " << histogram[i] << std::endl;
  }
  // Закрываем фай
  file.close();
}
