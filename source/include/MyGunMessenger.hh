#ifndef MyGunMessenger_h
#define MyGunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MyPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADouble;

class MyGunMessenger: public G4UImessenger
{
  public:
    MyGunMessenger(MyPrimaryGeneratorAction* );
    virtual ~MyGunMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:    
    MyPrimaryGeneratorAction*  fPrimaryGeneratorAction;

    G4UIdirectory*           fMyDirectory;
    G4UIdirectory*           fGunDirectory;
    // new cmds
    G4UIcmdWithADouble*  fAlpha;
    G4UIcmdWithADouble*  fBeta;
    G4UIcmdWithADouble*  fPolar;
};

#endif