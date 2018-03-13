#include "MyPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "Verbose.hh"

#include "TF2.h"

double gaisserr(double *x, double *par);

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction()
{
  if(verbose) G4cout<<"====>MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()"<<G4endl;


 /* G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic

  G4ParticleDefinition* particleDefinition 
    = G4ParticleTable::GetParticleTable()->FindParticle("proton");

  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(3.0*GeV);
*/
    G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="mu-");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(3.*GeV);//////'Y 30MeV???

  G4double fPosZ=200;

  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., fPosZ));  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
}

MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(verbose) G4cout<<"====>MyPrimaryGeneratorAction::GeneratePrimaries()"<<G4endl;

  G4double PI = 3.14159265358979323846;
  double Emin , Emax;
  Emin=0.03;
  Emax=30.;

  TF2 *muFlux = new TF2("muFlux", gaisserr, Emin, Emax, 0.1, 1.0, 0);
  muFlux->SetNpx(1000); //Emu
  muFlux->SetNpy(40);  //cosTh


  G4double Emu, cTheta, theta, phi;

  //Emu = 3;
  //cTheta = 0.5;
  muFlux->GetRandom2(Emu, cTheta);
 
  phi = G4UniformRand()*2*PI;
  theta = acos(cTheta);

  Emu*=GeV;

#define X 90.*cm
#define Y 130.*cm


  G4double ang= G4UniformRand()*2*PI;
  G4double x0=0+X*(G4UniformRand()-0.5); 
  G4double y0=0+Y*(G4UniformRand()-0.5);
  G4double z0 = -60.*cm;
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  G4double x1 = std::sin(theta)*std::cos(phi);
  G4double y1 = std::sin(theta)*std::sin(phi);
  G4double z1 = std::cos(theta);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x1, y1, z1));

  fParticleGun->SetParticleEnergy(Emu);

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

double gaisserr(double *x, double *par){
    double gaisser,emu, costh0;
    double  costh,en1, t115, t850, A0, gamma, p1,p2,p3,p4,p5;

    A0    = 0.14;
    gamma = 2.7;
    //     parameter( A0 = 0.260, gamma = 2.780)
    p1 = 0.102573;
    p2 = -0.068287;
    p3 = 0.958633;
    p4 = 0.0407253;
    p5 = 0.817285;

    emu=x[0];
    costh0=x[1];
    costh = sqrt((costh0*costh0+p1*p1+p2*pow(costh0,p3)+p4*pow(costh0,p5))/(1+p1*p1+p2+p4));

    en1= emu*(1+3.63698/(emu*pow(costh,1.29685)));

    t115 = 1.0  /( 1.0 + 1.10*emu*costh/115.0 );
    t850 = 0.0540/( 1.0 + 1.10*emu*costh/850.0 );

    gaisser = A0*(pow(en1,-gamma))*( t115 + t850 );
    // --> cm^2 s sr GeV
    return gaisser;
}