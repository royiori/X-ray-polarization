#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "TROOT.h"
#include "TSystem.h"
#include "TF2.h"

#define PI 3.1415927

class MyGunMessenger;
class G4GeneralParticleSource;

class MyPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
	public:
		MyPrimaryGeneratorAction();    
    virtual ~MyPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

    void SetAlpha(G4double a) { alpha = a*PI/180; }     
    void SetBeta (G4double b) { beta  = b*PI/180; }
    void SetPolar(G4double p) { polar = p*PI/180; } 
    //polar (cosp, sinp, 0) p=0 -> (1,0,0)
  private:
    MyGunMessenger* fGunMessenger;   // messenger
    G4ParticleGun*  fParticleGun;    // G4 particle gun
    G4GeneralParticleSource* fParticleSourceGun; // G4 particle source gun    

    G4int                  fPGorGPS;
    
    G4double alpha, beta, polar;     //degree
};

#endif