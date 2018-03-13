#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Region.hh"
#include "G4RunManager.hh"

#define SIZE 20
#define WORLD 10
//Bar 1~9

class MyDetectorMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();
    
    G4VPhysicalVolume* DefineVolumes();
    virtual G4VPhysicalVolume* Construct();		
    
    void Update();

    void SetDistanceX(G4double x);
    void SetDistanceZ(G4double z);
  
  private:
    MyDetectorMessenger*  fDetectorMessenger;   // messenger

    G4bool checkOverlaps = true;

    G4double DX;
    G4double DZ;
    
    //G4Box                * fSolid[SIZE];    //not using, only two
    //G4LogicalVolume      * fLogic[SIZE];    //not using, only two

    G4Box * solidWorld ;    
    G4Box * solidBar   ;                  
    
    G4LogicalVolume* logicWorld;
    G4LogicalVolume* logicBar;

    G4VPhysicalVolume    * fPhysc[SIZE];    

    G4double world_size; 
    G4double bar_x, bar_y, bar_z;
};

#endif