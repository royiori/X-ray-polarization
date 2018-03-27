#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyAnalysisManager.hh"
#include "SimEvent.hh"
#include "Verbose.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

MySteppingAction::MySteppingAction()
: G4UserSteppingAction()
{
  if(verbose) G4cout << "====>MySteppingAction::MySteppingAction(MyDetectorConstruction *, MyEventAction *)" << G4endl;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  if(verbose) G4cout << "====>MySteppingAction::UserSteppingAction(const G4Step* step)" << G4endl;

#if 1
//1
    // positions in the global coordinate system:
    G4StepPoint* PreStep  = step->GetPreStepPoint();
    G4StepPoint* PostStep = step->GetPostStepPoint();


    G4ThreeVector posPreStep  = PreStep->GetPosition();
    G4ThreeVector posPostStep = PostStep->GetPosition();

    G4TouchableHandle touchPreStep = PreStep->GetTouchableHandle();
    G4TouchableHandle touchPostStep = PostStep->GetTouchableHandle();

    //To get the current volume:
    G4VPhysicalVolume* volumePre = touchPreStep->GetVolume();
    G4VPhysicalVolume* volumePost =touchPostStep->GetVolume();

    //To get its name:
    G4String namePre = volumePre->GetName();
    G4String namePost= (volumePost==NULL)?"Null":volumePost->GetName();
    //G4cout<< namePost << G4endl;

    // G4Track* aTrack = step->GetTrack();
  
    SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();

#endif
  G4double edep = step->GetTotalEnergyDeposit();
  if(namePre == "Gas")    { fEvt->AddEdepGas(edep); }   // Edep of Gas
  if(namePost == "Wafer") { fEvt->AddEdepSi (edep); }   // Edep of Si
}