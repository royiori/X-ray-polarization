#include "MyActionInitialization.hh"
#include "MyDetectorConstruction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "QBBC.hh"

#include "G4PhysListFactory.hh"
#include "G4StepLimiterPhysics.hh"

G4int verbose = 0;

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes
  //
  // Detector construction
  MyDetectorConstruction* detector = new MyDetectorConstruction;
  runManager->SetUserInitialization(detector);

/////////////
/////////////
/////////////

  // Physics ist
  // G4VModularPhysicsList* physicsList = new QBBC;
#if 0  
  // fEmPhysicsList = new G4EmLivermorePolarizedPhysics();
        
//      G4VModularPhysicsList* phys = 0;
//      phys = factory.GetReferencePhysList(physName"Emlivermore");
//      phys->RegisterPhysics(new G4StepLimiterPhysics());
//      runManager->SetUserInitialization(phys);
//      G4cout<<"---> Loading "<<physName<<"."<<G4endl; 

/* 
  G4PhysListFactory factory;  
  G4VModularPhysicsList* physicsList = factory.GetReferencePhysList("G4EmLivermorePolarizedPhysics");
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());  */
#endif
#if 0
  G4VModularPhysicsList* physicsList = new G4VModularPhysicsList; 
  physicsList->RegisterPhysics(new G4EmLivermorePolarizedPhysics);
#endif
#if 1
  G4VModularPhysicsList* physicsList = new QBBC;
  physicsList->RegisterPhysics(new G4StepLimiterPhysics());
#endif
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);
    
  // User action initialization
  //runManager->SetUserInitialization(new MyActionInitialization(detector));
  runManager->SetUserInitialization(new MyActionInitialization());
  
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}