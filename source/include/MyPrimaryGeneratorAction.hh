#ifndef MyPrimaryGeneratorAction_h
#define MyPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

#include "TROOT.h"
#include "TSystem.h"
#include "TF2.h"
#include "TH1D.h"
#include "TFile.h"

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
    void SetPGorGPS(bool val) { fPGorGPS = val; }
    //polar (cosp, sinp, 0) p=0 -> (1,0,0)
    void SetParticleType(G4String);
  private:
    MyGunMessenger* fGunMessenger;   // messenger
    G4ParticleGun*  fParticleGun;    // G4 particle gun
    G4GeneralParticleSource* fParticleSourceGun; // G4 particle source gun    

    bool fPGorGPS; //default GPS
    
    G4double alpha, beta, polar;     //degree

    TH1D* hEvt;
    TFile* hFile;
    G4String hFileName;
    G4String ParticleType;
};

#endif