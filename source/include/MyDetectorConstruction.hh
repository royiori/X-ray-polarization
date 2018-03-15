#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Region.hh"
#include "G4RunManager.hh"

class MyDetectorMessenger;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{ 
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();
    
    G4VPhysicalVolume* DefineVolumes();
    virtual G4VPhysicalVolume* Construct();		
    
    // void Update();
    
    // void SetDetMaterial()  work with messenger 

  private:
    void DefineMaterials();

    MyDetectorMessenger*  fDetectorMessenger;   // messenger

    G4bool checkOverlaps;

    G4Material*        fWorldMaterial;   // pointer to the world  material
    G4Material*        fDetMaterial;     // pointer to the detector  material

    G4Box * solidWorld ;    
    G4Box * solidDet   ;                  
    
    G4LogicalVolume* logicWorld;
    G4LogicalVolume* logicDet;

    G4VPhysicalVolume*  physcWorld;
    G4VPhysicalVolume*  physcDet;

    G4double world_size; 
    G4double det_x, det_y, det_z;
};

#if 0

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
    
    //G4Box                * fSolid[SIZE];    //not using, only two
    //G4LogicalVolume      * fLogic[SIZE];    //not using, only two

    G4Box * solidWorld ;    
    G4Box * solidBar   ;                  
    
    G4LogicalVolume* logicWorld;
    G4LogicalVolume* logicBar;

    G4VPhysicalVolume    * fPhysc[SIZE];    
};
#endif

#endif