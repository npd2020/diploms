#include "PrimaryGeneratorAction.hh"
// Подключаем необходимы заголовочные файлы
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// Класс, в котором описывается положение, тип, энергия, направление вылета
// и распределение начальных частиц
PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(nullptr)
{
  // G4GeneralParticleSource
  //fGeneralParticleSource = new G4GeneralParticleSource();

  
  // ParticleGun
  // По умолчанию поставим 1 частицу
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Получаем встроеную в Geant4 таблицу частиц
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  // Ищем частицу
  G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
  // Устанавливаем полученную частицу в качестве испускаемого типа начальных частиц в источнике
  fParticleGun->SetParticleDefinition(particle);
  // Установка начальной энергии испускаемых частиц
  fParticleGun->SetParticleEnergy(14.1*MeV);
  // Встановлюєм позицію істочника
  fParticleGun->SetParticlePosition(G4ThreeVector(0*cm,-40*cm,0*cm));
  // Устанавливаем направление движение частицы по (x,y,z)
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.,0.));
}

// Деструктор
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  // удаляем созданный в конструкторе экземпляр класса источника G4ParticleGun
  delete fParticleGun;
  //delete fGeneralParticleSource;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // Генерируем первичное событие
  fParticleGun->GeneratePrimaryVertex(anEvent);
  //fGeneralParticleSource->GeneratePrimaryVertex(anEvent);
}
