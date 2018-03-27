#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MySteppingAction.hh"
#include "MyStackingAction.hh"
#include "Verbose.hh"

MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization()
{
  if(verbose) G4cout << "====>MyActionInitialization::MyActionInitialization()" << G4endl;

  masterGPS = new G4GeneralParticleSource;
}

MyActionInitialization::~MyActionInitialization()
{
    delete masterGPS;
}

void MyActionInitialization::BuildForMaster() const
{
  if(verbose) G4cout << "====>MyActionInitialization::BuildForMaster()" << G4endl;
  
  MyRunAction* runAction = new MyRunAction;
  SetUserAction(runAction);
}

void MyActionInitialization::Build() const
{
  if(verbose) G4cout << "====>MyActionInitialization::Build()" << G4endl; 

  MyPrimaryGeneratorAction* primary = new MyPrimaryGeneratorAction();
  SetUserAction(primary);

  MyEventAction* eventaction = new MyEventAction();
  SetUserAction(eventaction);  

  MyRunAction* runaction = new MyRunAction();
  SetUserAction(runaction); 

  SetUserAction(new MySteppingAction());

  SetUserAction(new MyStackingAction());
}