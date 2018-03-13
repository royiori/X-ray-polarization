#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector3.h"
#include "iostream"
//#include "../source/include/SimEvent.hh"

TString fFileName("tmp.root");
void WriteRoot();
void ReadRoot();

class SimEvent  : public TObject 
{
  public:
    SimEvent() {};
    ~SimEvent(){};

    inline void MyClear();

    void SetTime(int n, Float_t t){ fT[n] = t; }
    Float_t GetTime(int n){ return fT[n]; }
    void SetPos(int n, TVector3 pos){ fPos[n] = pos; }
    TVector3 GetPos(int n){ return fPos[n]; }
    void AddTotalEdep(int n, Float_t edep){ fTotalEdep[n] = edep; }

  private:
    Float_t fT[9];
    Float_t fTotalEdep[9];
    TVector3 fPos[9];

    ClassDef(SimEvent, 1);
};

inline void SimEvent::MyClear()
{
  for(int i=0; i!=9; ++i)
  {
    fT[i] = -1;
    fTotalEdep[i] = 0;
    fPos[i] = TVector3(0, 0, 0);
  }
}


ClassImp(SimEvent);


int RootFileIO()
{

   WriteRoot();

   ReadRoot();

}


void WriteRoot()
{
  cout<<"---> Write to "<<fFileName<<" root file."<<endl;

  TFile * fRootFp = new TFile(fFileName, "recreate");

  SimEvent* fEvent = new SimEvent();
  TTree   * fTree1 = new TTree("sim", "Tree of GasTPC events");


  fTree1->Branch("SimEvent", "SimEvent", &fEvent, 32000, 99);
  for(int i=0; i<9; i++) fEvent->SetTime(i, 10*i);

  fTree1->Fill();
  fEvent->Clear();

  fRootFp->Write();
  fRootFp->Close();
}
////
//analysis
void ReadRoot()
{
  cout<<"---> Read from "<<fFileName<<" root file."<<endl;

  TFile * fRootFp = new TFile(fFileName);    
  
  SimEvent* fEvent = 0;
  TTree   * fTree1  = (TTree *)fRootFp->Get("sim");
  fTree1->SetBranchAddress("SimEvent", &fEvent);

  fTree1->GetEntry(0);
  cout<<fEvent->GetTime(2)<<endl;  

  fRootFp->Close();
}
