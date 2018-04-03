#include "MyStackingAction.hh"
#include "MyEventAction.hh"
#include "MyAnalysisManager.hh"
#include "SimEvent.hh"

#include "G4RunManager.hh"
#include "G4Electron.hh"
#include "G4Track.hh"
#include "Verbose.hh"

MyStackingAction::MyStackingAction()
 : G4UserStackingAction(), fKillSecondary(0)
{
  if(verbose) G4cout << "====>MyStackingAction::MyStackingAction()" << G4endl;
}

MyStackingAction::~MyStackingAction()
{}

G4ClassificationOfNewTrack MyStackingAction::ClassifyNewTrack(const G4Track* aTrack)
{
  if(verbose) G4cout << "====>MyStackingAction::ClassifyNewTrack(const G4Track* aTrack)" << G4endl;
  // Use sim to save
#if 0
    const G4Step* step = aTrack->GetStep();
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
    G4String namere = volumePre->GetName();
    G4String namePost= (volumePost==NULL)?"Null":volumePost->GetName();
#endif

  SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();
  
  G4ThreeVector tmp(aTrack->GetMomentum());
  TVector3 momentum(tmp.x(), tmp.y(), tmp.z());
  // 这里可以优化时间

  if(aTrack->GetParentID() == 1) { fEvt->SetMomentumGetPhi(momentum); }
  // 最开始的momentum处理
     
  return fUrgent;
}