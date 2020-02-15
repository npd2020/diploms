// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes, nor the agencies providing financial support for this*
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// *                                                                  *
// * Разработано специально для dev.asifmoda.com                      *
// * Можно использовать для обучения, частных и коммерческих проектов.*
// * Прывітанне з Беларусі!                                           *
// * Автор, идея и реализация:                                        *
// * Виктор Гавриловец, bycel@tut.by,                                 *
// ********************************************************************
// $Id: G4SabatActionInitialization01.hh$
//
/// \file G4SabatActionInitialization01.hh
/// \brief Definition of the G4SabatActionInitialization01 class

#ifndef G4SabatActionInitialization01_h
#define G4SabatActionInitialization01_h 1

#include "G4VUserActionInitialization.hh"

/**
 * @brief The G4SabatActionInitialization01 class
 */
class G4SabatActionInitialization01 : public G4VUserActionInitialization
{
public:
    G4SabatActionInitialization01(); // Constructor
    virtual ~G4SabatActionInitialization01();

public:
    virtual void Build() const; // Create source of primary particles
};

#endif
