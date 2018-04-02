#ifndef SimEvent_h
#define SimEvent_h

#include "TVector3.h"
// #include "G4ThreeVector.hh"

#include "TObject.h"
#include <map>
#include <vector>

#define PAD_NUM 375
#define SWITCH 0
// Whether use PADS or not

class SimEvent : public TObject
{
  public:
    SimEvent() { MyClear(); } 
    ~SimEvent() {}
    void MyClear() 
    { 
      fMomentum = TVector3(0, 0, 0); 
      fPhi = -1; 
      EdepGas = 0; 
      EdepSi = 0;
/////////////
#if SWITCH
      for(int i=0; i!=PAD_NUM; ++i){
        for(int j=0; j!=PAD_NUM; ++j){
          EdepPad[i][j]=0;
        }
      }
      ECount = 0;
#endif
/////////////
#if 1
    count = 0;
#endif 
    };

    void SetMomentumGetPhi(TVector3 momentum) 
    {
      fMomentum = momentum; 
      fPhi = acos(fMomentum.x()/sqrt(fMomentum.x()*fMomentum.x()+fMomentum.y()*fMomentum.y()));
    }

    TVector3 GetMomentum() { return fMomentum; }
    Float_t GetPhi() { return fPhi; }

    void AddEdepGas(Float_t edep){ EdepGas += edep; }
    Float_t GetEdepGas(){ return EdepGas;}
  
    void AddEdepSi (Float_t edep){ EdepSi  += edep; } 
    Float_t GetEdepSi() { return EdepSi;}
#if 1 
    void AddCount(){ count+=1; }
#endif

/////////////
#if SWITCH
    void AddEdepPad (int x, int y, Float_t edep) { EdepPad[x][y] += edep; }
    Float_t GetEdepPad (int x, int y) {  return EdepPad[x][y]; }

    void AddECount() { ECount +=1; }
    Int_t GetECount() { return ECount; }
  private:
    Float_t EdepPad[PAD_NUM][PAD_NUM];
    Int_t ECount; //Electron generated in Be
#endif
/////////////
  private:
#if 1
    Float_t count; //Monte Carlo index
#endif
    TVector3 fMomentum;
    Float_t fPhi;
    
    Float_t EdepGas;
    Float_t EdepSi;

    ClassDef(SimEvent, 1);
};

#endif