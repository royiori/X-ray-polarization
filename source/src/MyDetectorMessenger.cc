#include "MyDetectorMessenger.hh"
#include "MyDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADouble.hh"
#include "Verbose.hh"

MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  if(verbose) G4cout << "====>MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)" << G4endl;
  fMyDirectory = new G4UIdirectory("/MySimulation/");
  fMyDirectory->SetGuidance("UI commands specific to this example.");

  fDetDirectory = new G4UIdirectory("/MySimulation/det/");
  fDetDirectory->SetGuidance("Detector construction control");

/*
  fStepMaxCmd = new G4UIcmdWithADouble("/MySimulation/det/stepMax",this);
  fStepMaxCmd->SetGuidance("Define a step max");
  fStepMaxCmd->SetParameterName("step",false);
  fStepMaxCmd->SetRange("step>=0.&&step<=1.");
  fStepMaxCmd->AvailableForStates(G4State_Idle);
*/

  /* SetSize

  Update
  fUpdateCmd = new G4UIcmdWithoutParameter("/MySimulation/det/update",this);
  fUpdateCmd->SetGuidance("Update calorimeter geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorMessenger::~MyDetectorMessenger()
{

  // delete fUpdateCmd;
  // delete fStepMaxCmd;

  delete fMyDirectory;
  delete fDetDirectory;
}

void MyDetectorMessenger::SetNewValue(G4UIcommand* /*command*/,G4String /*newValue*/)
{
  if(verbose) G4cout<<"void MyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)"<<G4endl;
  
  
  // if( command == fStepMaxCmd ) 
  //  { fDetectorConstruction ->SetMaxStep(fStepMaxCmd->GetNewDoubleValue(newValue)); }   

 
  // if( command == fUpdateCmd) { fDetectorConstruction->Update(); }
}