#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyAnalysisManager.hh"
#include "Verbose.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

MySteppingAction::MySteppingAction()
: G4UserSteppingAction()
{
  if(verbose) G4cout<<"====>MySteppingAction::MySteppingAction(MyDetectorConstruction *, MyEventAction *)"<<G4endl;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step*)
{
  if(verbose) G4cout<<"====>MySteppingAction::UserSteppingAction(const G4Step* step)"<<G4endl;
}











////////////////////////////////////////////////////////////////////////
#if 0 
void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  if(verbose) G4cout<<"====>MySteppingAction::UserSteppingAction(const G4Step* step)"<<G4endl;

  // get volume of the current step
  G4LogicalVolume* volume
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
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
    G4cout<< namePost << G4endl;

    G4Track* aTrack = step->GetTrack();
  
    SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();

#endif

#if 0
  // primary particle and shoot at detector, get time and position
  if(namePre == "World" && namePost.substr(0, 3) == "Bar" && aTrack->GetParentID() == 0) 
  {
    int n = namePost[3] - '0';
    G4double x = step->GetPostStepPoint()->GetPosition().x();
    G4double y = step->GetPostStepPoint()->GetPosition().y();
    G4double z = step->GetPostStepPoint()->GetPosition().z();
    G4double t = step->GetPostStepPoint()->GetGlobalTime();//-1  first time
    if(fEvt->GetPos(n) == TVector3(0, 0, 0)) fEvt->SetPos(n, TVector3(x, y, z));
    if(fEvt->GetTime(n) == -1) fEvt->SetTime(n, t);
  }
  // collect edep
  if(namePost.substr(0, 3) == "Bar")
  {
    int n = namePost[3] - '0';
    G4double edep = step->GetTotalEnergyDeposit();
    fEvt->AddTotalEdep(n, edep);
  }
}
#endif
/*
     G4double phi  = step->GetTrack()->GetPosition().phi();
     G4double theta= step->GetTrack()->GetPosition().theta();
     fEventAction->Pushback(0, eKin);
     G4cout<<"hit saved: "<<eKin<<" "<<phi<<" "<<theta<<G4endl;
    
  }
  else if(namePre != "World" && namePost == "World" && aTrack->GetParentID() == 0)
  {
    int n = namePre[3] - '0';
     //aTrack->SetTrackStatus(fStopAndKill);
  }
*/