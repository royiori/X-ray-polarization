#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Region.hh"
#include "G4RunManager.hh"

class G4CSGSolid;

#define SIZE 20
#define _WORLD 0
#define _GAS 1
#define _CERAMICS 2
#define _WINDOW 3
#define _SCOPE_INNER 4
#define _SCOPE_OUTER 5
#define _SHELL_INNER 6
#define _SHELL_OUTER 7
#define _WAFER 8

class MyDetectorParameters
{
  public:
    MyDetectorParameters()
    {
      Name = ""; 
      Matt = ""; 
      for(int i=0; i<10; i++) Siz[i] = 0; 
      for(int i=0; i<5; i++) Pos[i] = 0; 
      Material = 0; 
      visAtt   = 0; 
      // Region   = 0;
    }
    virtual ~MyDetectorParameters() {};
   
    G4String Name;
    G4String Matt;
    G4double Siz[10];
    G4double Pos[5];
    G4Material      *Material;
    G4VisAttributes *visAtt;
    // G4Region        *Region;
};

class MyDetectorConstruction : public G4VUserDetectorConstruction
{ 
  public:
    MyDetectorConstruction();
    virtual ~MyDetectorConstruction();
    
    G4VPhysicalVolume* DefineVolumes();
    virtual G4VPhysicalVolume* Construct();		
    
    void SetMaterial(int, G4String);
    // void Update();

  private:
    void DefineMaterials();

    // fDetectorMessenger

    G4bool checkOverlaps;

    G4UserLimits* fStepLimit;            // pointer to user step limits

    // G4Material*        fWorldMaterial;   // pointer to the world  material
    // G4Material*        fDetMaterial;     // pointer to the detector  material
    // G4Box * solidWorld ;    
    // G4Box * solidDet   ;                  
    // G4LogicalVolume* logicWorld;
    // G4LogicalVolume* logicDet;
    // G4VPhysicalVolume*  physcWorld;
    // G4VPhysicalVolume*  physcDet;
    // G4double world_size; 
    // G4double det_x, det_y, det_z;
    MyDetectorParameters * fDetPar[SIZE];
    G4CSGSolid           * fSolid[SIZE];
    G4LogicalVolume      * fLogic[SIZE];
    G4VPhysicalVolume    * fPhysc[SIZE];
};

#endif