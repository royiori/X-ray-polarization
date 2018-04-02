#include "MyPrimaryGeneratorAction.hh"
#include "MyGunMessenger.hh"
#include "MyDetectorConstruction.hh"

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

#define PI 3.1415927
using std::sin;
using std::cos;

MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
  fGunMessenger(0), fParticleGun(0), fParticleSourceGun(0), alpha(0), beta(0), polar(0)
{
  if(verbose) G4cout << "====>MyPrimaryGeneratorAction::MyPrimaryGeneratorAction()" << G4endl;

  fPGorGPS = false; // false for GPS, true for Particle Gun
  // default GPS

  fGunMessenger = new MyGunMessenger(this);
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(2.*keV);
  // energy?
  // 2keV

  G4double fPosZ= -5*cm;

  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., fPosZ));  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


  //...... particle source gun
  fParticleSourceGun = new G4GeneralParticleSource();

  fParticleSourceGun->SetParticleDefinition(particle);

  G4SPSEneDistribution *eneDist = fParticleSourceGun->GetCurrentSource()->GetEneDist() ;
  eneDist->SetEnergyDisType("Mono");
  eneDist->SetMonoEnergy(30.*MeV);
  
  G4SPSPosDistribution *posDist = fParticleSourceGun->GetCurrentSource()->GetPosDist() ;
  posDist->SetPosDisType("Plane");
  posDist->SetPosDisShape("Circle");
  posDist->SetRadius(20.0*cm);
  posDist->SetCentreCoords(G4ThreeVector(0.,0.,fPosZ));

  G4SPSAngDistribution *angDist = fParticleSourceGun->GetCurrentSource()->GetAngDist() ;
  angDist->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.)) ;

}


MyPrimaryGeneratorAction::~MyPrimaryGeneratorAction()
{
  delete fParticleGun;
}

void MyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  if(verbose) G4cout << "====>MyPrimaryGeneratorAction::GeneratePrimaries()" << G4endl;
  
  //.. importance sampling for the detector injection direction.
  const MyDetectorConstruction* constfDetector
    = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  MyDetectorConstruction* fDetector
    = const_cast<MyDetectorConstruction*>(constfDetector);

  //.. set position
  G4double _x = fDetector->GetXSide();
  G4double _y = fDetector->GetYSide();
  G4double z0 = -fDetector->GetZTop();///
  G4double h0 = fDetector->GetHeight();

  G4double x0 = _x * 2*(G4UniformRand()-0.5);
  G4double y0 = _y * 2*(G4UniformRand()-0.5);

  fParticleGun->SetParticlePosition(G4ThreeVector(x0, y0, z0));

  //.. set direction
  G4int passFlag = 0;

  G4double theta, phi;

  while(!passFlag) {
    theta = G4UniformRand() * PI / 2;
    phi   = G4UniformRand() * PI * 2;

    G4double x1 = x0 + h0 * sin(theta)*cos(phi);
    G4double y1 = y0 + h0 * sin(theta)*sin(phi);

    if( fabs(x1) < _x && fabs(y1) < _y) passFlag = 1;
  }

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(sin(theta)*cos(phi), sin(theta)*sin(phi), cos(theta)));

  //.. set particle type, which is set by the messenger
  //G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  //fParticleGun->SetParticleDefinition(particle);


  //.. set particle energy
  G4double energy = 2*keV;
  if(hEvt!=NULL) energy = hEvt->GetRandom();

  fParticleGun->SetParticleEnergy(energy);

  // G4double z0 = -5.*cm;
  // fParticleGun->SetParticlePosition(G4ThreeVector(0,0,z0));
////////////////////////////////////////////////////////////////////////////////////////////////
  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
  // fParticleGun->SetParticlePolarization(G4ThreeVector(1,0,0));
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
//  //Spherical coordinate system
//  // alpha--theta beta--phi
//  // 2 degree vibration (amplitude), now just Uniform distribution, use Gaussian maybe
//  G4double alpha_ = alpha * (2*G4UniformRand()-1); 
//  G4double beta_ = beta, polar_ = polar;
//
//  // (cos(polar), sin(polar), 0)
//  G4ThreeVector direction   (sin(alpha_)*cos(beta_), sin(alpha_)*sin(beta_),  cos(alpha_));
//  // G4ThreeVector polarization(cos(alpha_)*cos(beta_), cos(alpha_)*sin(beta_), -sin(alpha_)); 
//  G4ThreeVector polarization (cos(alpha_)*cos(beta_)*cos(polar)-sin(beta_)*sin(polar_),
//                              cos(alpha_)*sin(beta_)*cos(polar)+cos(beta_)*sin(polar_),
//                             -sin(alpha_)*cos(polar_));
//  fParticleGun->SetParticleMomentumDirection(direction);
//  fParticleGun->SetParticlePolarization(polarization);
////////////////////////////////////////////////////////////////////////////////////////////////

  if(fPGorGPS == true) fParticleGun->GeneratePrimaryVertex(anEvent);
  else            fParticleSourceGun->GeneratePrimaryVertex(anEvent);  
}

void MyPrimaryGeneratorAction::SetParticleType(G4String ptype)
{
    ParticleType = ptype;
    hFileName = ParticleType+G4String(".root");

    if(hFile!=NULL) hFile->Close();    

   if(gROOT->GetListOfFiles()->FindObject(hFileName))
      hFile = (TFile*)gROOT->GetListOfFiles()->FindObject(hFileName);
   else
      hFile = new TFile(hFileName, "read");

    if(!hFile->IsOpen()) hEvt = NULL;
    else {
      hEvt = (TH1D *)hFile->Get("hevt");
      G4cout << "====>" << hFileName << " is open." << G4endl;

      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      
      G4ParticleDefinition* particle = particleTable->FindParticle(ParticleType="e-");
     
      if(ptype == "cxb")    particle = particleTable->FindParticle(ParticleType="gamma");
      if(ptype == "e+")     particle = particleTable->FindParticle(ParticleType="e+");
      if(ptype == "proton") particle = particleTable->FindParticle(ParticleType="proton");

      fParticleGun->SetParticleDefinition(particle);
    }
}



#if 0
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
#endif