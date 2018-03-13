#ifndef MyAnalysisManager_h
#define MyAnalysisManager_h 1

#include "G4Event.hh"
#include "g4root.hh"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

class SimEvent;

class MyAnalysisManager
{
  public:
    MyAnalysisManager();
    ~MyAnalysisManager();
    void BeginOfEventAction(const G4Event* evt);
    void EndOfEventAction(const G4Event* evt);

    void BeginOfRunAction();
    void EndOfRunAction();

    static MyAnalysisManager* GetInstance()
    {
      if(MyAnalysisManager::fInstance == NULL) MyAnalysisManager::fInstance = new MyAnalysisManager();
      return MyAnalysisManager::fInstance;
    }

    SimEvent* GetSimEvent() { return fEvent; }
    inline void SetFileName(G4String name) { fFileName = name; }

  private:
    G4String fFileName;
    
    FILE * outfile;
    TFile* fRootFp;
    TTree* fTree;  
    SimEvent* fEvent;

    static MyAnalysisManager* fInstance; 
};

#endif