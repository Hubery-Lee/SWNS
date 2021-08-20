/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 15:29:09
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-08-07 13:02:20
 */
#include "SWNSPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh" //! for gps macros

//! for gun macros ---------------------
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "g4root.hh"

SWNSPrimaryGeneratorAction::SWNSPrimaryGeneratorAction(/* args */)
{
    fParticleGPS = new G4GeneralParticleSource;//! for gps macros

    //! for gun macros ---------------------
    // G4int n_particle = 1;
    // fParticleGun = new G4ParticleGun(n_particle);

    // // default particle

    // G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    // G4ParticleDefinition *particle = particleTable->FindParticle("e-");

    // fParticleGun->SetParticleDefinition(particle);
    // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    // fParticleGun->SetParticleEnergy(0.546* MeV);
}

SWNSPrimaryGeneratorAction::~SWNSPrimaryGeneratorAction()
{
    // delete fParticleGun;
    delete fParticleGPS; //! for gps
}

void SWNSPrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{

    // fParticleGun->SetParticlePosition(G4ThreeVector(0. * cm, 0. * cm, 0. * cm)); //! for gun macros
    // fParticleGun->GeneratePrimaryVertex(anEvent);

    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillH1(0, fParticleGPS->GetParticleEnergy()); //!for gps

    fParticleGPS->GeneratePrimaryVertex(anEvent);//! for gps macros
}
