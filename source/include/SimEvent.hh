#ifndef SimEvent_h
#define SimEvent_h

#include "TVector3.h"
// #include "G4ThreeVector.hh"

#include "TObject.h"
#include <map>
#include <vector>


class SimEvent : public TObject
{
  public:
    SimEvent() { MyClear(); } 
    ~SimEvent() {}
    void MyClear() { fMomentum = TVector3(0, 0, 0); fPhi = -1; };

    void SetMomentumGetPhi(TVector3 momentum) 
    {
      fMomentum = momentum; 
      fPhi = acos(fMomentum.x()/sqrt(fMomentum.x()*fMomentum.x()+fMomentum.y()*fMomentum.y()));
    }

    TVector3 GetMomentum() { return fMomentum; }
    Float_t GetPhi() { return fPhi; }
    
  private:
    TVector3 fMomentum;
    Float_t fPhi;

    ClassDef(SimEvent, 1);
};

// inline void SimEvent::MyClear()
// {
  // Initialize to -1
// }

#if 0
class SimEvent : public TObject
{
  public:

    void SetTime(int n, Float_t t){ fT[n] = t; }
    void SetPos(int n, TVector3 pos){ fPos[n] = pos; }
    Float_t GetTime(int n){ return fT[n]; }
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
};
#endif
#endif

/*
TWO WAYS:
1 vectors
  Saves all messages Step by Step, able to reconstruct every track.
    
  e/g.  
    vector<Float_t> fTotalEdep; 
    vector<Float_t> fT; 
    vector<Tvector3> vPos;
    And Get... Set... functions for them.

2 array buf
  Collect important messages.
  e.g.
    in this sim
*/