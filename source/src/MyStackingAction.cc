#include "MyStackingAction.hh"

#include "MyEventAction.hh"

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
  return fUrgent;
}