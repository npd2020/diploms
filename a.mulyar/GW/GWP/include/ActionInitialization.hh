#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();//Конструктор
    virtual ~ActionInitialization();//Деструктор
    virtual void Build() const;//Создание источника первичных частиц

};
#endif
