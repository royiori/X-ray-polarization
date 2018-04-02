#ifndef MyDetectorMessenger_h
#define MyDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;

class MyDetectorMessenger: public G4UImessenger
{
  public:
    MyDetectorMessenger(MyDetectorConstruction* );
    virtual ~MyDetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    MyDetectorConstruction* fDetectorConstruction;

    G4UIdirectory*           fMyDirectory;
    G4UIdirectory*           fDetDirectory;

    // G4UIcmdWithADouble*      fStepMaxCmd;
    // G4UIcmdWithoutParameter* fUpdateCmd;
};

#endif
/* 功能：
设置
*/