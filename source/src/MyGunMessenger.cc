#include "MyGunMessenger.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "Verbose.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADouble.hh"


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
}

MyGunMessenger::~MyGunMessenger()
{
  delete fMyDirectory;
  delete fGunDirectory;

  // add more if needed
  delete fAlpha;
  delete fBeta;
  delete fPolar;
}

void MyGunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == fAlpha)
  { fPrimaryGeneratorAction->SetAlpha(fAlpha->GetNewDoubleValue(newValue)); }
  if(command == fBeta)
  { fPrimaryGeneratorAction->SetBeta (fBeta ->GetNewDoubleValue(newValue)); }
  if(command == fPolar)
  { fPrimaryGeneratorAction->SetPolar(fPolar->GetNewDoubleValue(newValue)); }
}