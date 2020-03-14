#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    //Конструктор, вызывается при создании экземпляра класса
    //Обычно используется для задания начальных значений и значений по умолчанию
    //при создании геометрии и материалов
    DetectorConstruction();
    //Деструктор, вызывается при удалении экземпляра класса
    //Обычно используется для освобождения памяти инициализированных массивов внутри класса
    virtual ~DetectorConstruction();
    //Объявление и создание детекторов и среды
    virtual G4VPhysicalVolume* Construct();
    //Установка чувствительного объема. Когда частица в нем, то в нем извлекается
    //вся информация о треке и параметрах частицы на каждом шаге моделирования
    virtual void ConstructSDandField();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  protected:
    G4LogicalVolume*  fScoringVolume;
};
#endif

