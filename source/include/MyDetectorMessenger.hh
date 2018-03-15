#ifndef MyDetectorMessenger_h
#define MyDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;


// Messenger class that defines commands for MyDetectorConstruction.

class MyDetectorMessenger: public G4UImessenger
{
  public:
    MyDetectorMessenger(MyDetectorConstruction* );
    virtual ~MyDetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:    
    MyDetectorConstruction*  fDetectorConstruction;

    G4UIdirectory*           fMyDirectory;
    G4UIdirectory*           fDetDirectory;    
    // new cmds
};

/*
// Messenger class that defines commands for MyDetectorConstruction.

class MyDetectorMessenger: public G4UImessenger
{
  public:
    MyDetectorMessenger(MyDetectorConstruction* );
    virtual ~MyDetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:    
    MyDetectorConstruction*  fDetectorConstruction;

    G4UIdirectory*           fMyDirectory;
    G4UIdirectory*           fDetDirectory;    

    G4UIcmdWithADoubleAndUnit*      fDistanceX;
    G4UIcmdWithADoubleAndUnit*      fDistanceZ;
};
*/
#endif
