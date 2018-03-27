#ifndef MyActionInitialization_h
#define MyActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class MyDetectorConstruction;
class G4GeneralParticleSource;

class MyActionInitialization : public G4VUserActionInitialization
{
  public:
    MyActionInitialization();
    virtual ~MyActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
  private:
    G4GeneralParticleSource* masterGPS;
};

#endif