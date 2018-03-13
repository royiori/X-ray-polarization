#ifndef MyEventAction_h
#define MyEventAction_h 1

#include "G4RunManager.hh"
#include "G4UserEventAction.hh"
#include "globals.hh"

class MyRunAction;

class MyEventAction : public G4UserEventAction
{
	public:
    MyEventAction();
    virtual ~MyEventAction();

    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );
};

#endif