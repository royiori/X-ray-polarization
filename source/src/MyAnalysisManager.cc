#include "MyAnalysisManager.hh"
#include "SimEvent.hh"
#include "Verbose.hh"

ClassImp(SimEvent);


MyAnalysisManager* MyAnalysisManager::fInstance = 0;

MyAnalysisManager::MyAnalysisManager()
{
  if(verbose) G4cout << "====>MyAnalysisManager::MyAnalysisManager()" << G4endl;
  fFileName = "tmp.root";
  fRootFp = NULL;
  fTree   = NULL;
  fEvent  = NULL;
}

void MyAnalysisManager::BeginOfRunAction()
{
  if(verbose) G4cout << "====>MyAnalysisManager::BeginOfRunAction()" << G4endl;
  fRootFp = new TFile(fFileName, "recreate");
  if (!fRootFp) {
    G4cout << "\n--->MyAnalysisManager::BeginOfRunAction(): "<< "cannot open " << fFileName << G4endl;
    return;
  }

  fEvent = new SimEvent();
  fTree  = new TTree("simTree", "Tree of GasTPC events");
  fTree->Branch("SimEvent", "SimEvent", &fEvent, 32000, 99);
}

void MyAnalysisManager::EndOfRunAction()
{
  if(verbose) G4cout << "====>MyAnalysisManager::EndOfRunAction()" << G4endl; 
  if(!fRootFp) {
    G4cout << "\n--->MyAnalysisManager::EndOfRunAction(): " << "cannot open " << fFileName << G4endl;
    return;
  }
  fRootFp->Write();
  fRootFp->Close();
}

void MyAnalysisManager::BeginOfEventAction(const G4Event* evt)
{
  if(verbose) G4cout << "====>MyAnalysisManager::BeginOfEventAction(const G4Event* evt)" << G4endl;
  fEvent->MyClear();
}

void MyAnalysisManager::EndOfEventAction(const G4Event* evt)
{
  // fTree->Fill();
  fEvent->MyClear();
}