#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"//Подключаем обязательный класс
//в котором описываются источник начальных частиц

/// Обязательный класс, который должен быть объявлен в проекте Geant4
/// Имя класса может быть другим, и он должен наследоваться от
/// класса G4VUserActionInitialization

/// Конструктор
ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}
//Деструктор, ничего не объявляли, поэтому оставим пустым
ActionInitialization::~ActionInitialization()
{}
//Создание источника первичных частиц
void ActionInitialization::Build() const
{
SetUserAction(new PrimaryGeneratorAction);//Задается источник первичных частиц
//через обязательный класс PrimaryGeneratorAction
}
