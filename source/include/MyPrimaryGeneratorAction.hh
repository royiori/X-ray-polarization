#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "TROOT.h"
#include "TSystem.h"
#include "TF2.h"

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		MyPrimaryGeneratorAction();    
    virtual ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);     
  
  private:
    G4ParticleGun*  fParticleGun; // G4 particle gun
};

#endif