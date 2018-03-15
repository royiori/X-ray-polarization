#include "MyDetectorMessenger.hh"
#include "MyDetectorConstruction.hh"
#include "Verbose.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"


MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  if(verbose) G4cout << "MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)" << G4endl;
}

MyDetectorMessenger::~MyDetectorMessenger()
{
  // delete fMyDirectory;
  // delete fDetDirectory;

  // add more if needed
}

void MyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
#if 0
  if(command ==)
  {}
  if(command ==) 
  {}
#endif  
}

#if 0
MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  if(verbose) G4cout << "MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)" << G4endl;

  fMyDirectory = new G4UIdirectory("/MySimulation/");
  fMyDirectory->SetGuidance("UI commands specific to Framework.");

  fDetDirectory = new G4UIdirectory("/MySimulation/det/");
  fDetDirectory->SetGuidance("Detector construction control");  

  fDistanceX = new G4UIcmdWithADoubleAndUnit("/MySimulation/det/setDistanceX",this);
  fDistanceX->SetGuidance("Set the distance between detectors along x axis.");  
  fDistanceX->SetUnitCategory("Length");  
  fDistanceX->SetParameterName("dX",false);

  fDistanceZ = new G4UIcmdWithADoubleAndUnit("/MySimulation/det/setDistanceZ",this);
  fDistanceZ->SetGuidance("Set the distance between detectors along z axis.");   
  fDistanceZ->SetUnitCategory("Length");  
  fDistanceZ->SetParameterName("dZ",false);  

/*  fDistanceX->SetDefaultValue(G4Double); false->True
    Default value and unit for dX and dZ. 
    Omitable? */
}

MyDetectorMessenger::~MyDetectorMessenger()
{
  delete fMyDirectory;
  delete fDetDirectory;

  delete fDistanceX;
  delete fDistanceZ;
}

void MyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if(command == fDistanceX)
  { fDetectorConstruction->SetDistanceX(fDistanceX->GetNewDoubleValue(newValue)); }  
  if(command == fDistanceZ) 
  { fDetectorConstruction->SetDistanceZ(fDistanceZ->GetNewDoubleValue(newValue)); }  
}
#endif