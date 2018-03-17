#include "SimEvent.hh"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"
#include "TKey.h"
#include "iostream"

#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFitResult.h"
#include "TStyle.h"

//*****************************************************************************
// To run this macro in root:
//
// in debug
// gSystem->Load("libSimEventDict.so");
// .L RootFileIO.C++
// RootFileIO();
//
//*****************************************************************************

#if 0
double the_cos_fit(double* vars, double* pars){
  return pars[0]*cos(vars[0]*2+pars[1])+pars[2];
}
TF1 cos_fit("cos_fit",the_cos_fit,0.,3.14,3);
#endif
#if 1
double the_sin2_fit(double *vars, double *pars){
  return pars[0]*pow(sin(vars[0]+pars[1]),2)+pars[2];
}
TF1 sin2_fit("sin2_fit",the_sin2_fit,0.,3.14,3);
#endif
TH1F h("h","PHI_FIT;Phi [rad];Entries [0.02]",157,0.,3.14);
TH2F hxy("px-py","px-py;px [MeV/c];py [MeV/c]",100, -0.05, 0.05, 100, -0.05, 0.05);
TH2F hxz("px-pz","px-pz;px [MeV/c];pz [MeV/c]",100, -0.05, 0.05, 100, -0.05, 0.05);
TH2F hyz("py-pz","py-pz;py [MeV/c];pz [MeV/c]",100, -0.05, 0.05, 100, -0.05, 0.05);
TH1F p2("momentum",";p [MeV/c];Entries [2.5*10^-4]",200,0.,0.05);

// TH1F histo("histo","Signal plus background;X vals;Y Vals",50,0,20);

void ReadRoot();

TString fFileName("tmp.root"); //Filename
//*****************************************************************************

void RootFileIO() { ReadRoot(); }

void ReadRoot()
{
  cout << "---> Read from " << fFileName << " root file." << endl;
  TFile * fRootFp = new TFile(fFileName);    

  gStyle->SetOptStat(0);
  gStyle->SetOptFit(1);

  SimEvent* fEvent = 0;  //declare and initlize
  TTree   * fTree1  = (TTree *)fRootFp->Get("simTree");
  fTree1->SetBranchAddress("SimEvent", &fEvent);

// set the parameters before the fit 
#if 0
  double A=150, delta=0, n=150;
  cos_fit.SetParameters(A,delta,n);
  cos_fit.SetParNames("Amplitude","#delta","n");
#endif
#if 1
  double A=1000, delta=0, n=0;
  sin2_fit.SetParameters(A,delta,n);
  sin2_fit.SetParNames("Amplitude","#delta","n");
#endif
  int sz = fTree1->GetEntries();
  cout << "sz: " << sz << endl; //size

  for(int i=0; i!=sz; ++i){  
    fTree1->GetEntry(i); 
    h.Fill(fEvent->GetPhi());
    hxy.Fill(fEvent->GetMomentum().x(),fEvent->GetMomentum().y());
    hxz.Fill(fEvent->GetMomentum().x(),fEvent->GetMomentum().z());
    hyz.Fill(fEvent->GetMomentum().y(),fEvent->GetMomentum().z());
    p2.Fill(sqrt(pow(fEvent->GetMomentum().x(),2)+pow(fEvent->GetMomentum().y(),2)+pow(fEvent->GetMomentum().z(),2)));
  }
  
  // auto fitResPtr = h.Fit(&cos_fit, "S"); //quiet ="q"
  auto fitResPtr = h.Fit(&sin2_fit, "S"); //quiet ="q"
 
  fitResPtr->Print(); // print fit results
  
  // Same DrawClone
  // h.Draw();
  fRootFp->Close();
}