#include "MyRunAction.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyAnalysisManager.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Verbose.hh"

#include "g4root.hh"

MyRunAction::MyRunAction()
 : G4UserRunAction()
{
  if(verbose) G4cout << "====>MyRunAction::MyRunAction()" << G4endl;    
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  if(verbose) G4cout << "====>MyRunAction::BeginOfRunAction()" << G4endl;    
  MyAnalysisManager::GetInstance()->BeginOfRunAction();
}

void MyRunAction::EndOfRunAction(const G4Run* )
{
  if(verbose) G4cout << "====>MyRunAction::EndOfRunAction()" << G4endl;    
  MyAnalysisManager::GetInstance()->EndOfRunAction();
}