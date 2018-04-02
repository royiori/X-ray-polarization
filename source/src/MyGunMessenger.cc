#include "MyGunMessenger.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "Verbose.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"


MyGunMessenger::MyGunMessenger(MyPrimaryGeneratorAction* PGA)
 : G4UImessenger(),
   fPrimaryGeneratorAction(PGA)
{
  if(verbose) G4cout << "MyGunMessenger::MyGunMessenger(MyPrimaryGeneratorAction* PGA)" << G4endl;

  fMyDirectory = new G4UIdirectory("/MySimulation/");
  fMyDirectory->SetGuidance("UI commands specific to Framework.");
  
  fGunDirectory = new G4UIdirectory("/MySimulation/gun/");
  fGunDirectory->SetGuidance("Particle gun control");  

  fAlpha = new G4UIcmdWithADouble("/MySimulation/gun/setAlpha",this);
  fAlpha->SetGuidance("Set Alpha.");  
  fAlpha->SetParameterName("alpha",false);

  fBeta = new G4UIcmdWithADouble("/MySimulation/gun/setBeta",this);
  fBeta->SetGuidance("Set Beta.");  
  fBeta->SetParameterName("beta",false);  

  fPolar = new G4UIcmdWithADouble("/MySimulation/gun/setPolar",this);
  fPolar->SetGuidance("Set Polar.");  
  fPolar->SetParameterName("polar",false);

  fPGorGPS = new G4UIcmdWithABool("/MySimulation/gun/setPGorGPS",this);
  fPGorGPS->SetGuidance("false = GPS, true = PG.");
  fPGorGPS->SetParameterName("PG=true, GPS=false",false);

  fPType = new G4UIcmdWithAString("/MySimulation/gun/setParticleType",this);
  fPType->SetGuidance("Set particle type.");
}

MyGunMessenger::~MyGunMessenger()
{
  delete fMyDirectory;
  delete fGunDirectory;

  // add more if needed
  delete fAlpha;
  delete fBeta;
  delete fPolar;
  delete fPGorGPS;
  delete fPType;
}

void MyGunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == fAlpha)
  { fPrimaryGeneratorAction->SetAlpha(fAlpha->GetNewDoubleValue(newValue)); }
  if(command == fBeta)
  { fPrimaryGeneratorAction->SetBeta (fBeta ->GetNewDoubleValue(newValue)); }
  if(command == fPolar)
  { fPrimaryGeneratorAction->SetPolar(fPolar->GetNewDoubleValue(newValue)); }
  if(command == fPGorGPS)
  { fPrimaryGeneratorAction->SetPGorGPS(fPGorGPS->GetNewBoolValue(newValue));}
  if (command == fPType)
  { fPrimaryGeneratorAction->SetParticleType(newValue); }  
}