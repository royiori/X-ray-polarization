#ifndef MyStackingAction_h
#define MyStackingAction_h 1

#include "G4UserStackingAction.hh"
#include "globals.hh"

class MyStackingAction : public G4UserStackingAction
{
  public:
    MyStackingAction();
   ~MyStackingAction();
   
    void SetKillStatus(G4int value) { fKillSecondary = value;};
     
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track*);
    
  private:
    G4int               fKillSecondary;
};

#endif