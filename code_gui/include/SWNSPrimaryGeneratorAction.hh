/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 15:26:50
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-07-22 16:53:38
 */

#ifndef SWNSPrimaryGeneratorAction_h
#define SWNSPrimaryGeneratorAction_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource; //! for gps macros 
class G4ParticleGun;//! for gun macros----

class G4Event;

class SWNSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
private:
    /* data */
    G4GeneralParticleSource *fParticleGPS;//! for gps macros
    // G4ParticleGun* fParticleGun;//! for gun macros
public:
    SWNSPrimaryGeneratorAction(/* args */);
    ~SWNSPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event *anEvent);
    const G4GeneralParticleSource *GetParticleGPS() const { return fParticleGPS; }//! for gps macros
};

#endif