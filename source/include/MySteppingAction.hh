#ifndef MySteppingAction_h
#define MySteppingAction_h 1

#include "G4UserSteppingAction.hh"
//#include "MyDetectorConstruction.hh"

class MyEventAction;

class MySteppingAction : public G4UserSteppingAction
{
	public:
    MySteppingAction();
    virtual ~MySteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif