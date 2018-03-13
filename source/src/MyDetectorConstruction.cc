#include "MyDetectorConstruction.hh"
#include "MyDetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4UniformMagField.hh"
#include "G4AutoDelete.hh"

#include "G4HadronicProcessStore.hh"
#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4AutoDelete.hh"
#include "Verbose.hh"

//Initialize
MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction(),
  fDetectorMessenger(0),
  DX(22.*cm), DZ(50.*cm),
  world_size(100.*cm),
  bar_x(10.*cm), bar_y(50.*cm), bar_z(2.5*cm)
{
  if(verbose) G4cout << "====>MyDetectorConstruction::MyDetectorConstruction()" << G4endl;
  
  fDetectorMessenger = new MyDetectorMessenger(this);

  for(int i=0; i<20; i++) fPhysc[i]=NULL;
  logicWorld=NULL;    logicBar=NULL;
  solidWorld=NULL;    solidBar=NULL;

}

MyDetectorConstruction::~MyDetectorConstruction()
{ delete fDetectorMessenger; }

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  if(verbose) G4cout << "====>MyDetectorConstruction::Construct()" << G4endl;
  return DefineVolumes();
}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
  if(verbose) G4cout << "====>MyDetectorConstruction::DefineVolumes()" << G4endl;

  // LEAK prevention!
  for(int i=0; i<10; i++) if(fPhysc[i]!=NULL) delete fPhysc[i];
  if(logicWorld!=NULL) delete logicWorld;
  if(logicBar!=NULL) delete logicBar;
  if(solidWorld!=NULL) delete solidWorld;
  if(solidBar!=NULL) delete solidBar;

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean(); 

  solidWorld = new G4Box("World", world_size, world_size, world_size); 

  logicWorld = new G4LogicalVolume(solidWorld, \
      G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"), "World");

  fPhysc[WORLD] = new G4PVPlacement(0,       //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking 


  solidBar   = new G4Box("Bar", bar_x, bar_y, bar_z);                     

  logicBar   = new G4LogicalVolume(solidBar, \
      G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYSTYRENE"), "Bar");


  G4ThreeVector posBar[9] = {
    G4ThreeVector(DX, 0, DZ),G4ThreeVector(0, 0, DZ),G4ThreeVector(-DX, 0, DZ),
    G4ThreeVector(DX, 0, 0),G4ThreeVector(0, 0, 0),G4ThreeVector(-DX, 0, 0),
    G4ThreeVector(DX, 0, -DZ),G4ThreeVector(0, 0, -DZ),G4ThreeVector(-DX, 0, -DZ)
  };

  for(int i=0; i!=9; ++i)
  {
    fPhysc[i] = new G4PVPlacement(0,         //no rotation
                      posBar[i],             //at posBar[i]
                      logicBar,         //its logic volume
                      "Bar"+std::string(1,i+1+'0'), //its name
                      logicWorld,            //its mother volume
                      false,                 //no boolean operation
                      i,                     //copy number
                      checkOverlaps);        //overlaps checking
  }

  logicWorld->SetVisAttributes(G4VisAttributes::Invisible);

  return fPhysc[WORLD];
}

void MyDetectorConstruction::SetDistanceX(G4double x)
{ DX = x; Update(); }

void MyDetectorConstruction::SetDistanceZ(G4double z)
{ DZ = z; Update(); }

void MyDetectorConstruction::Update()   //Update physWorld
{  
  G4RunManager::GetRunManager()->ReinitializeGeometry(); 
  G4RunManager::GetRunManager()->DefineWorldVolume(DefineVolumes());
}