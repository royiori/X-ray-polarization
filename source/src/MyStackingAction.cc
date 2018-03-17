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
  SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();
#if 1
  if(aTrack->GetParentID() == 1)
  {
    G4ThreeVector tmp(aTrack->GetMomentum());
    TVector3 momentum(tmp.x(), tmp.y(), tmp.z());
    fEvt->SetMomentumGetPhi(momentum);
  }
#endif
#if 0
    G4cout << "x" << momentum.x() << G4endl;
    G4cout << "y" << momentum.y() << G4endl;
    G4cout << "z" << momentum.z() << G4endl;
    
    G4cout << "x" << tmp.x() << G4endl;
    G4cout << "y" << tmp.y() << G4endl;
    G4cout << "z" << tmp.z() << G4endl;    
    G4cout << "x" << momentum.x() << G4endl;
    G4cout << "y" << momentum.y() << G4endl;
    G4cout << "z" << momentum.z() << G4endl;    
    G4cout << "Phi" << fEvt->GetPhi() << G4endl;
  }
#endif  

  return fUrgent;
}