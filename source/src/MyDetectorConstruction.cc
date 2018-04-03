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

MyDetectorConstruction::MyDetectorConstruction()
: G4VUserDetectorConstruction(),
  fDetectorMessenger(0), checkOverlaps(false)
{
  if(verbose) G4cout << "====>MyDetectorConstruction::MyDetectorConstruction()" << G4endl;

  // Init
  for(int i=0;i<SIZE;i++) fDetPar[i] = new MyDetectorParameters();
  for(int i=0;i<SIZE;i++) fSolid[i]  = 0;  
  for(int i=0;i<SIZE;i++) fLogic[i]  = 0;  
  for(int i=0;i<SIZE;i++) fPhysc[i]  = 0;    
  
  fStepLimit = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////  
// MATERIAL!!!!!!
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////  
G4double thickness=3*mm; //(1-10)
////////////////////////////////////////////////////////////////////////////////////////////////////////
  fDetPar[_WORLD]->Name   = "World";
  fDetPar[_WORLD]->Matt   = "G4_Galactic";
  fDetPar[_WORLD]->Siz[0] = 150*mm; 
  fDetPar[_WORLD]->Siz[1] = 150*mm; 
  fDetPar[_WORLD]->Siz[2] = 150*mm;
  fDetPar[_WORLD]->Pos[0] = 0*mm;
  fDetPar[_WORLD]->Pos[1] = 0*mm;
  fDetPar[_WORLD]->Pos[2] = 0*mm;
  fDetPar[_WORLD]->visAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0,0.4));
  fDetPar[_WORLD]->Material = NULL;
  
  fDetPar[_GAS]->Name   = "Gas";
  // fDetPar[_GAS]->Matt   = "He_20_DME_80";
  fDetPar[_GAS]->Matt   = "He_20_DME_80_P0_5";
  fDetPar[_GAS]->Siz[0] = 7.5*mm; 
  fDetPar[_GAS]->Siz[1] = 7.5*mm; 
  fDetPar[_GAS]->Siz[2] = 5*mm;
  fDetPar[_GAS]->Pos[0] = 0*mm;
  fDetPar[_GAS]->Pos[1] = 0*mm;
  fDetPar[_GAS]->Pos[2] = 0*mm;
  fDetPar[_GAS]->visAtt = new G4VisAttributes(G4Colour(0.1, 0.9, 0.7,0.4));
  fDetPar[_GAS]->Material = NULL;

  fDetPar[_CERAMICS]->Name   = "Ceramics";
  fDetPar[_CERAMICS]->Matt   = "ceramics";
  fDetPar[_CERAMICS]->Siz[0] = 12.5*mm; 
  fDetPar[_CERAMICS]->Siz[1] = 12.5*mm; 
  fDetPar[_CERAMICS]->Siz[2] = 5*mm;
  fDetPar[_CERAMICS]->Pos[0] = 0*mm;
  fDetPar[_CERAMICS]->Pos[1] = 0*mm;
  fDetPar[_CERAMICS]->Pos[2] = (40-thickness)/2 *mm;
  fDetPar[_CERAMICS]->visAtt = new G4VisAttributes(G4Colour(0.1,0.1,0.9,0.4));
  fDetPar[_CERAMICS]->Material = NULL;

  fDetPar[_WINDOW]->Name = "Be";
  fDetPar[_WINDOW]->Matt = "G4_Be";
  fDetPar[_WINDOW]->Siz[0] = 7.5*mm; 
  fDetPar[_WINDOW]->Siz[1] = 7.5*mm; 
  // fDetPar[_WINDOW]->Siz[2] = 0.05*mm;
  G4double thickness_Be = 0.05; //mm
  fDetPar[_WINDOW]->Siz[2] = thickness_Be*mm;
  fDetPar[_WINDOW]->Pos[0] = 0*mm;
  fDetPar[_WINDOW]->Pos[1] = 0*mm;
  fDetPar[_WINDOW]->Pos[2] = (20-thickness_Be) *mm;
  fDetPar[_WINDOW]->visAtt = new G4VisAttributes(G4Colour(1,0,0.3,0.4));
  fDetPar[_WINDOW]->Material = NULL;
  

  fDetPar[_SCOPE_INNER]->Name   = "Scope_I";
  fDetPar[_SCOPE_INNER]->Matt   = "G4_Galactic";
  fDetPar[_SCOPE_INNER]->Siz[0] = 7.5*mm; 
  fDetPar[_SCOPE_INNER]->Siz[1] = 7.5*mm; 
  fDetPar[_SCOPE_INNER]->Siz[2] = 20*mm;
  fDetPar[_SCOPE_INNER]->Pos[0] = 0*mm;
  fDetPar[_SCOPE_INNER]->Pos[1] = 0*mm;
  fDetPar[_SCOPE_INNER]->Pos[2] = 0*mm;
  fDetPar[_SCOPE_INNER]->visAtt = new G4VisAttributes(G4Colour(1, 1, 1,0.4));
  fDetPar[_SCOPE_INNER]->Material = NULL;  

  fDetPar[_SCOPE_OUTER]->Name   = "Scope_O";
  fDetPar[_SCOPE_OUTER]->Matt   = "G4_Al";
  fDetPar[_SCOPE_OUTER]->Siz[0] = (7.5+thickness) *mm; 
  fDetPar[_SCOPE_OUTER]->Siz[1] = (7.5+thickness) *mm; 
  fDetPar[_SCOPE_OUTER]->Siz[2] = 20*mm;
  fDetPar[_SCOPE_OUTER]->Pos[0] = 0*mm;
  fDetPar[_SCOPE_OUTER]->Pos[1] = 0*mm;
  fDetPar[_SCOPE_OUTER]->Pos[2] = -(10+thickness)/2 *mm;
  fDetPar[_SCOPE_OUTER]->visAtt = new G4VisAttributes(G4Colour(1, 1, 1,0.4));
  fDetPar[_SCOPE_OUTER]->Material = NULL;  

  fDetPar[_SHELL_INNER]->Name   = "Shell_I";
  fDetPar[_SHELL_INNER]->Matt   = "G4_Galactic";
  fDetPar[_SHELL_INNER]->Siz[0] = (90-thickness)/2 *mm; 
  fDetPar[_SHELL_INNER]->Siz[1] = (90-thickness)/2 *mm; 
  fDetPar[_SHELL_INNER]->Siz[2] = (50-thickness)/2 *mm;
  fDetPar[_SHELL_INNER]->Pos[0] = 0*mm;
  fDetPar[_SHELL_INNER]->Pos[1] = 0*mm;
  fDetPar[_SHELL_INNER]->Pos[2] = 0*mm;
  fDetPar[_SHELL_INNER]->visAtt = new G4VisAttributes(G4Colour(1, 1, 1,0.4));
  fDetPar[_SHELL_INNER]->Material = NULL;  

  fDetPar[_SHELL_OUTER]->Name   = "Shell_O";
  fDetPar[_SHELL_OUTER]->Matt   = "G4_Al";
  fDetPar[_SHELL_OUTER]->Siz[0] = (90+thickness)/2 *mm;
  fDetPar[_SHELL_OUTER]->Siz[1] = (90+thickness)/2 *mm; 
  fDetPar[_SHELL_OUTER]->Siz[2] = (50+thickness)/2 *mm;
  fDetPar[_SHELL_OUTER]->Pos[0] = 0*mm;
  fDetPar[_SHELL_OUTER]->Pos[1] = 0*mm;
  fDetPar[_SHELL_OUTER]->Pos[2] = 0*mm;
  fDetPar[_SHELL_OUTER]->visAtt = new G4VisAttributes(G4Colour(1, 1, 1,0.4));
  fDetPar[_SHELL_OUTER]->Material = NULL;        

  fDetPar[_WAFER]->Name   = "Wafer";
  fDetPar[_WAFER]->Matt   = "G4_Si";
  fDetPar[_WAFER]->Siz[0] =  7.5*mm;
  fDetPar[_WAFER]->Siz[1] =  7.5*mm; 
  G4double thickness_Si = 0.35; //mm
  fDetPar[_WAFER]->Siz[2] = thickness_Si*mm;
  fDetPar[_WAFER]->Pos[0] = 0*mm;
  fDetPar[_WAFER]->Pos[1] = 0*mm;
  fDetPar[_WAFER]->Pos[2] = (5-thickness_Si) *mm;
  fDetPar[_WAFER]->visAtt = new G4VisAttributes(G4Colour(0.9, 0.7, 0.1,0.4));
  fDetPar[_WAFER]->Material = NULL;    

  DefineMaterials();

  SetMaterial(_WORLD,       fDetPar[_WORLD]->Matt);
  SetMaterial(_GAS,         fDetPar[_GAS]->Matt);
  SetMaterial(_CERAMICS,    fDetPar[_CERAMICS]->Matt);
  SetMaterial(_WINDOW,      fDetPar[_WINDOW]->Matt);
  SetMaterial(_SCOPE_INNER, fDetPar[_SCOPE_INNER]->Matt);
  SetMaterial(_SCOPE_OUTER, fDetPar[_SCOPE_OUTER]->Matt);
  SetMaterial(_SHELL_INNER, fDetPar[_SHELL_INNER]->Matt);
  SetMaterial(_SHELL_OUTER, fDetPar[_SCOPE_OUTER]->Matt);
  SetMaterial(_WAFER,       fDetPar[_WAFER]->Matt);

  fDetectorMessenger = new MyDetectorMessenger(this);

/*
  G4cout << "x:\t" << GetXSide() << G4endl;
  G4cout << "y:\t" << GetYSide() << G4endl;
  G4cout << "z:\t" << GetZTop() << G4endl;
  G4cout << "h:\t" << GetHeight() << G4endl;
*/         
}


MyDetectorConstruction::~MyDetectorConstruction()
{
  delete fDetectorMessenger; 
  delete fStepLimit;
}


G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  if(verbose) G4cout << "====>MyDetectorConstruction::Construct()" << G4endl;

  return DefineVolumes();  
}

G4VPhysicalVolume* MyDetectorConstruction::DefineVolumes()
{
  if(verbose) G4cout << "====>MyDetectorConstruction::DefineVolumes()" << G4endl;

  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  //From outside to inside
  fSolid[_WORLD] = new G4Box(fDetPar[_WORLD]->Name, 
      fDetPar[_WORLD]->Siz[0], fDetPar[_WORLD]->Siz[1], fDetPar[_WORLD]->Siz[2]);
  // fLogic[_WORLD] = new G4LogicalVolume(fSolid[_WORLD], G4NistManager::Instance()->FindOrBuildMaterial("G4_Ar"), "World");
  //fDetPar[_WORLD]->Material, fDetPar[_WORLD]->Name);
  fLogic[_WORLD] = new G4LogicalVolume(fSolid[_WORLD], fDetPar[_WORLD]->Material, fDetPar[_WORLD]->Name);
  fPhysc[_WORLD] = new G4PVPlacement(0, 
      G4ThreeVector(fDetPar[_WORLD]->Pos[0], fDetPar[_WORLD]->Pos[1], fDetPar[_WORLD]->Pos[2]), 
      fLogic[_WORLD], fDetPar[_WORLD]->Name, 0, false, 0, checkOverlaps);
// SHELL OUT
// SHELL IN
  fSolid[_SHELL_OUTER] = new G4Box(fDetPar[_SHELL_OUTER]->Name,
      fDetPar[_SHELL_OUTER]->Siz[0], fDetPar[_SHELL_OUTER]->Siz[1], fDetPar[_SHELL_OUTER]->Siz[2]);
  fLogic[_SHELL_OUTER] = new G4LogicalVolume(fSolid[_SHELL_OUTER], fDetPar[_SHELL_OUTER]->Material, fDetPar[_SHELL_OUTER]->Name);
  fPhysc[_SHELL_OUTER] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_SHELL_OUTER]->Pos[0], fDetPar[_SHELL_OUTER]->Pos[1], fDetPar[_SHELL_OUTER]->Pos[2]),
      fLogic[_SHELL_OUTER], fDetPar[_SHELL_OUTER]->Name, fLogic[_WORLD], false, 0, checkOverlaps);      
  
  fSolid[_SHELL_INNER] = new G4Box(fDetPar[_SHELL_INNER]->Name,
      fDetPar[_SHELL_INNER]->Siz[0], fDetPar[_SHELL_INNER]->Siz[1], fDetPar[_SHELL_INNER]->Siz[2]);
  fLogic[_SHELL_INNER] = new G4LogicalVolume(fSolid[_SHELL_INNER], fDetPar[_SHELL_INNER]->Material, fDetPar[_SHELL_INNER]->Name);
  fPhysc[_SHELL_INNER] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_SHELL_INNER]->Pos[0], fDetPar[_SHELL_INNER]->Pos[1], fDetPar[_SHELL_INNER]->Pos[2]),
      fLogic[_SHELL_INNER], fDetPar[_SHELL_INNER]->Name, fLogic[_SHELL_OUTER], false, 0, checkOverlaps);            
//
  fSolid[_SCOPE_OUTER] = new G4Box(fDetPar[_SCOPE_OUTER]->Name,
      fDetPar[_SCOPE_OUTER]->Siz[0], fDetPar[_SCOPE_OUTER]->Siz[1], fDetPar[_SCOPE_OUTER]->Siz[2]);
  fLogic[_SCOPE_OUTER] = new G4LogicalVolume(fSolid[_SCOPE_OUTER], fDetPar[_SCOPE_OUTER]->Material, fDetPar[_SCOPE_OUTER]->Name);
  fPhysc[_SCOPE_OUTER] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_SCOPE_OUTER]->Pos[0], fDetPar[_SCOPE_OUTER]->Pos[1], fDetPar[_SCOPE_OUTER]->Pos[2]),
      fLogic[_SCOPE_OUTER], fDetPar[_SCOPE_OUTER]->Name, fLogic[_SHELL_OUTER], false, 0, checkOverlaps);   

  fSolid[_SCOPE_INNER] = new G4Box(fDetPar[_SCOPE_INNER]->Name,
      fDetPar[_SCOPE_INNER]->Siz[0], fDetPar[_SCOPE_INNER]->Siz[1], fDetPar[_SCOPE_INNER]->Siz[2]);
  fLogic[_SCOPE_INNER] = new G4LogicalVolume(fSolid[_SCOPE_INNER], fDetPar[_SCOPE_INNER]->Material, fDetPar[_SCOPE_INNER]->Name);
  fPhysc[_SCOPE_INNER] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_SCOPE_INNER]->Pos[0], fDetPar[_SCOPE_INNER]->Pos[1], fDetPar[_SCOPE_INNER]->Pos[2]),
      fLogic[_SCOPE_INNER], fDetPar[_SCOPE_INNER]->Name, fLogic[_SCOPE_OUTER], false, 0, checkOverlaps);   
//
  fSolid[_WINDOW] = new G4Box(fDetPar[_WINDOW]->Name,
      fDetPar[_WINDOW]->Siz[0], fDetPar[_WINDOW]->Siz[1], fDetPar[_WINDOW]->Siz[2]);
  fLogic[_WINDOW] = new G4LogicalVolume(fSolid[_WINDOW], fDetPar[_WINDOW]->Material, fDetPar[_WINDOW]->Name);
  fPhysc[_WINDOW] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_WINDOW]->Pos[0], fDetPar[_WINDOW]->Pos[1], fDetPar[_WINDOW]->Pos[2]),
      fLogic[_WINDOW], fDetPar[_WINDOW]->Name, fLogic[_SCOPE_INNER], false, 0, checkOverlaps);   

  fSolid[_CERAMICS] = new G4Box(fDetPar[_CERAMICS]->Name,
      fDetPar[_CERAMICS]->Siz[0], fDetPar[_CERAMICS]->Siz[1], fDetPar[_CERAMICS]->Siz[2]);
  fLogic[_CERAMICS] = new G4LogicalVolume(fSolid[_CERAMICS], fDetPar[_CERAMICS]->Material, fDetPar[_CERAMICS]->Name);
  fPhysc[_CERAMICS] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_CERAMICS]->Pos[0], fDetPar[_CERAMICS]->Pos[1], fDetPar[_CERAMICS]->Pos[2]),
      fLogic[_CERAMICS], fDetPar[_CERAMICS]->Name, fLogic[_SHELL_INNER], false, 0, checkOverlaps);   

  fSolid[_GAS] = new G4Box(fDetPar[_GAS]->Name,
      fDetPar[_GAS]->Siz[0], fDetPar[_GAS]->Siz[1], fDetPar[_GAS]->Siz[2]);
  fLogic[_GAS] = new G4LogicalVolume(fSolid[_GAS], fDetPar[_GAS]->Material, fDetPar[_GAS]->Name);
  fPhysc[_GAS] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_GAS]->Pos[0], fDetPar[_GAS]->Pos[1], fDetPar[_GAS]->Pos[2]),
      fLogic[_GAS], fDetPar[_GAS]->Name, fLogic[_CERAMICS], false, 0, checkOverlaps);      

  fSolid[_WAFER] = new G4Box(fDetPar[_WAFER]->Name,
      fDetPar[_WAFER]->Siz[0], fDetPar[_WAFER]->Siz[1], fDetPar[_WAFER]->Siz[2]);
  fLogic[_WAFER] = new G4LogicalVolume(fSolid[_WAFER], fDetPar[_WAFER]->Material, fDetPar[_WAFER]->Name);
  fPhysc[_WAFER] = new G4PVPlacement(0,
      G4ThreeVector(fDetPar[_WAFER]->Pos[0], fDetPar[_WAFER]->Pos[1], fDetPar[_WAFER]->Pos[2]),
      fLogic[_WAFER], fDetPar[_WAFER]->Name, fLogic[_CERAMICS], false, 0, checkOverlaps);         

  fLogic[_WORLD]->SetVisAttributes(G4VisAttributes::Invisible);
  fLogic[_CERAMICS]->SetVisAttributes(fDetPar[_CERAMICS]->visAtt);
  fLogic[_GAS]->SetVisAttributes(fDetPar[_GAS]->visAtt);
  fLogic[_WINDOW]->SetVisAttributes(fDetPar[_WINDOW]->visAtt);
  fLogic[_SCOPE_INNER]->SetVisAttributes(fDetPar[_SCOPE_INNER]->visAtt);
  fLogic[_SCOPE_OUTER]->SetVisAttributes(fDetPar[_SCOPE_OUTER]->visAtt);
  fLogic[_SHELL_INNER]->SetVisAttributes(fDetPar[_SHELL_INNER]->visAtt);
  fLogic[_SHELL_OUTER]->SetVisAttributes(fDetPar[_SHELL_OUTER]->visAtt);
  fLogic[_WAFER]->SetVisAttributes(fDetPar[_WAFER]->visAtt);

#if 0
  // G4double maxStep = 0.02*fDetPar[_GAS]->Siz[2];
  G4double maxStep = 0.02 * mm;
  fStepLimit = new G4UserLimits(maxStep);//, maxLength, maxTime, minEkin);
  fLogic[_GAS]->SetUserLimits(fStepLimit);
  // fLogic[_WORLD]->SetUserLimits(fStepLimit);
#endif
  return fPhysc[_WORLD];  
}

void MyDetectorConstruction::SetMaterial(int id, G4String materialName)
{
  if(verbose) G4cout << "====>MyDetectorConstruction::SetMaterial(int, G4String)" << G4endl;
  
  // search the material by its name, or build it from nist data base
  G4Material* pttoMaterial = G4NistManager::Instance()->FindOrBuildMaterial(materialName);

  fDetPar[id]->Matt = materialName;  

  if (pttoMaterial && fDetPar[id]->Material != pttoMaterial) {
    fDetPar[id]->Material = pttoMaterial;
    if(fLogic[id]) fLogic[id]->SetMaterial(fDetPar[id]->Material);
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}
#if 1
void MyDetectorConstruction::DefineMaterials()
{
   //
   // define Elements
   //
  //This function illustrates the possible ways to define materials
 
  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  

  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double temperature, pressure;
  
  //
  // define Elements
  //
  G4Element* H  = new G4Element("Hydrogen", symbol="H",  z= 1, a=   1.01*g/mole);
  G4Element* He = new G4Element("Helium",   symbol="He", z= 2.,a=   4.00*g/mole);
  G4Element* C  = new G4Element("Carbon",   symbol="C",  z= 6, a=  12.01*g/mole);
  G4Element* elN= new G4Element("Nitrogen", symbol="N",  z= 7, a=  14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",   symbol="O",  z= 8, a=  16.00*g/mole);
  G4Element* F  = new G4Element("Fluorine", symbol="F",  z= 9, a=  19.00*g/mole);
  G4Element* Ne = new G4Element("Neon",     symbol="Ne", z=10, a=  20.17*g/mole);
  G4Element* Na = new G4Element("Sodium",   symbol="Na", z=11, a=  22.99*g/mole);
  G4Element* Al = new G4Element("Aluminium",symbol="Al", z=13, a=  26.98*g/mole);
  G4Element* Si = new G4Element("Silicon",  symbol="Si", z=14, a=  28.09*g/mole);
  G4Element* S  = new G4Element("Sulfur",   symbol="S",  z=16.,a=  32.066*g/mole);
  G4Element* Ar = new G4Element("Argon",    symbol="Ar", z=18, a=  39.95*g/mole);
  G4Element* Cr = new G4Element("Chrome",   symbol="Cr", z=25, a=  51.996*g/mole);
  G4Element* Fe = new G4Element("Iron"  ,   symbol="Fe", z=26, a=  55.845*g/mole);
  G4Element* Co = new G4Element("Cobalt",   symbol="Co", z=27, a=  58.933*g/mole);
  G4Element* Ni = new G4Element("Nickel",   symbol="Ni", z=28, a=  58.693*g/mole);
  G4Element* Br = new G4Element("Bromine",  symbol="Br", z=35, a=  79.904*g/mole);
  G4Element* Y  = new G4Element("Yttrium",  symbol="Y",  z=39, a=  88.91*g/mole);
  G4Element* I  = new G4Element("Iodine",   symbol="I" , z=53, a= 126.90*g/mole);
  G4Element* Xe = new G4Element("Xenon",    symbol="Xe", z=54, a= 131.29*g/mole);
  G4Element* La = new G4Element("Lanthanum",symbol="La", z=57, a= 138.9055*g/mole);
  G4Element* Ce = new G4Element("Cerium",   symbol="Ce", z=58, a= 140.12*g/mole);
  G4Element* Lu = new G4Element("Lutetium", symbol="Lu", z=71, a= 174.97*g/mole);
  G4Element* W  = new G4Element("Tungsten", symbol="W",  z=74, a= 183.850*g/mole);

  G4Isotope* GdIsotope1 = new G4Isotope("Gd_152", 64, 152, 152.0*g/mole);
  G4Isotope* GdIsotope2 = new G4Isotope("Gd_154", 64, 154, 154.0*g/mole);
  G4Isotope* GdIsotope3 = new G4Isotope("Gd_155", 64, 155, 155.0*g/mole);
  G4Isotope* GdIsotope4 = new G4Isotope("Gd_156", 64, 156, 156.0*g/mole);
  G4Isotope* GdIsotope5 = new G4Isotope("Gd_157", 64, 157, 157.0*g/mole);
  G4Isotope* GdIsotope6 = new G4Isotope("Gd_158", 64, 158, 158.0*g/mole);
  G4Isotope* GdIsotope7 = new G4Isotope("Gd_160", 64, 160, 160.0*g/mole);

  G4Element* Gd = new G4Element("Gadolinium", "Gd", 7);
  Gd->AddIsotope(GdIsotope1, 100.0*0.002*152/157.318*perCent);
  Gd->AddIsotope(GdIsotope2, 100.0*0.022*154/157.318*perCent);
  Gd->AddIsotope(GdIsotope3, 100.0*0.149*155/157.318*perCent);
  Gd->AddIsotope(GdIsotope4, 100.0*0.206*156/157.318*perCent);
  Gd->AddIsotope(GdIsotope5, 100.0*0.157*157/157.318*perCent);
  Gd->AddIsotope(GdIsotope6, 100.0*0.247*158/157.318*perCent);
  Gd->AddIsotope(GdIsotope7, 100.0*0.217*160/157.318*perCent);
  //
  // define simple materials
  //
  new G4Material("H2Liq"    , z= 1, a= 1.01*g/mole, density= 70.8*mg/cm3);
  new G4Material("Beryllium", z= 4, a= 9.01*g/mole, density= 1.848*g/cm3);
  new G4Material("Aluminium", z=13, a=26.98*g/mole, density= 2.700*g/cm3);
  new G4Material("Silicon"  , z=14, a=28.09*g/mole, density= 2.330*g/cm3);

  G4Material* lAr = 
    new G4Material("liquidArgon", density= 1.390*g/cm3, ncomponents=1);
  lAr->AddElement(Ar, natoms=1);

  new G4Material("Iron",     z=26, a= 55.85*g/mole, density= 7.870*g/cm3);
  new G4Material("Copper",   z=29, a= 63.55*g/mole, density= 8.960*g/cm3);
  new G4Material("Germanium",z=32, a= 72.61*g/mole, density= 5.323*g/cm3);
  new G4Material("Silver",   z=47, a=107.87*g/mole, density= 10.50*g/cm3);
  new G4Material("Tungsten", z=74, a=183.85*g/mole, density= 19.30*g/cm3);
  new G4Material("Gold",     z=79, a=196.97*g/mole, density= 19.32*g/cm3);
  new G4Material("Lead",     z=82, a=207.19*g/mole, density= 11.35*g/cm3);

  //
  // define a material from elements.   case 1: chemical molecule
  //

  G4Material* H2O = new G4Material("Water",density= 1.000*g/cm3,ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->GetIonisation()->SetMeanExcitationEnergy(78*eV);

  G4Material* CH = new G4Material("Plastic",density= 1.04*g/cm3,ncomponents=2);
  CH->AddElement(C, natoms=1);
  CH->AddElement(H, natoms=1);

  G4Material* NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
  NaI->AddElement(Na, natoms=1);
  NaI->AddElement(I , natoms=1);
  NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);

  G4Material* LaBr3 = new G4Material("LaBr3", density= 5.06*g/cm3, ncomponents=2);
  LaBr3->AddElement(La, natoms=1);
  LaBr3->AddElement(Br, natoms=3);

  //
  // define a material from elements.   case 2: mixture by fractional mass
  //

  G4Material* Air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(elN, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);

  G4Material* Air20 = 
    new G4Material("Air20", density= 1.205*mg/cm3, ncomponents=2,
                   kStateGas, 293.*kelvin, 1.*atmosphere);
  Air20->AddElement(elN, fractionmass=0.7);
  Air20->AddElement(O, fractionmass=0.3);

  //Graphite
  //
  G4Material* Graphite = 
    new G4Material("Graphite", density= 1.7*g/cm3, ncomponents=1);
  Graphite->AddElement(C, fractionmass=1.);

  //Havar
  //
  G4Material* Havar = 
    new G4Material("Havar", density= 8.3*g/cm3, ncomponents=5);
  Havar->AddElement(Cr, fractionmass=0.1785);
  Havar->AddElement(Fe, fractionmass=0.1822);
  Havar->AddElement(Co, fractionmass=0.4452);
  Havar->AddElement(Ni, fractionmass=0.1310);
  Havar->AddElement(W , fractionmass=0.0631);

  // LSO
  //
  G4Material* LSO = new G4Material("Lu2SiO5", 7.4*g/cm3, 3);
  LSO->AddElement(Lu, 2);
  LSO->AddElement(Si, 1);
  LSO->AddElement(O , 5); 
 
  // LYSO:Ce,   Assuming Lu2(x-1)Y2(x)SiO5:Ce. x=10%, Ce=5%. 
  // So, Ce=5%, LYSO=95%.(mole faction) => mass fraction: Ce=0.19%, LYSO=99.91%
  // then for LYSO, the same as above
  //
  G4Material *Scint_mat = new G4Material("Scint", density=7.4*g/cm3, ncomponents = 4);
  Scint_mat->AddElement(Lu, 71*perCent);
  Scint_mat->AddElement(Si, 7*perCent);
  Scint_mat->AddElement(O, 18*perCent);   
  Scint_mat->AddElement(Y, 4*perCent);

  G4Material *LYSO = new G4Material("LYSO", density=7.4*g/cm3, ncomponents = 2); 
  LYSO->AddMaterial(Scint_mat, 99.81*perCent); 
  LYSO->AddElement(Ce, 0.19*perCent);


  //
  // examples of gas
  //  
  new G4Material("ArgonGas", z=18, a=39.948*g/mole, density= 1.782*mg/cm3,
                 kStateGas, 273.15*kelvin, 1*atmosphere);
                           
  new G4Material("XenonGas", z=54, a=131.29*g/mole, density= 5.458*mg/cm3,
                 kStateGas, 293.15*kelvin, 1*atmosphere);
                           
  G4Material* CO2 =
    new G4Material("CarbonicGas", density= 1.977*mg/cm3, ncomponents=2);
  CO2->AddElement(C, natoms=1);
  CO2->AddElement(O, natoms=2);

  G4Material* ArCO2 =
    new G4Material("ArgonCO2",   density= 1.8223*mg/cm3, ncomponents=2);
  ArCO2->AddElement (Ar,  fractionmass=0.7844);
  ArCO2->AddMaterial(CO2, fractionmass=0.2156);

  //another way to define mixture of gas per volume
  G4Material* NewArCO2 =
    new G4Material("NewArgonCO2", density= 1.8223*mg/cm3, ncomponents=3);
  NewArCO2->AddElement (Ar, natoms=8);
  NewArCO2->AddElement (C,  natoms=2);
  NewArCO2->AddElement (O,  natoms=4);

  G4Material* ArCH4 = 
    new G4Material("ArgonCH4",    density= 1.709*mg/cm3,  ncomponents=3);
  ArCH4->AddElement (Ar, natoms=93);
  ArCH4->AddElement (C,  natoms=7);
  ArCH4->AddElement (H,  natoms=28);

  G4Material* XeCH = 
    new G4Material("XenonMethanePropane", density= 4.9196*mg/cm3, ncomponents=3,
                   kStateGas, 293.15*kelvin, 1*atmosphere);
  XeCH->AddElement (Xe, natoms=875);
  XeCH->AddElement (C,  natoms=225);
  XeCH->AddElement (H,  natoms=700);

  G4Material* steam = 
    new G4Material("WaterSteam", density= 1.0*mg/cm3, ncomponents=1);
  steam->AddMaterial(H2O, fractionmass=1.);
  steam->GetIonisation()->SetMeanExcitationEnergy(71.6*eV);  

  G4Material* LS = new G4Material("LS", 0.859*g/cm3, 5);
  LS->AddElement(C, 0.87924);
  LS->AddElement(H, 0.1201);
  LS->AddElement(O, 0.00034);
  LS->AddElement(elN, 0.00027);
  LS->AddElement(S, 0.00005);

  G4Material* ESR = new G4Material("ESR", 1.0*g/cm3, 2);
  ESR->AddElement(H, 2.*1.00794/(12.0107+2.*1.00794));
  ESR->AddElement(C, 12.0107/(12.0107+2.*1.00794));

  G4Material* Tyvek = new G4Material("Tyvek", 0.94*g/cm3, 2);
  Tyvek->AddElement(C, 2);
  Tyvek->AddElement(H, 4);

  G4Material* Acrylic = new G4Material("Acrylic", 1.18*g/cm3, 3);
  Acrylic->AddElement(C, 0.59984);
  Acrylic->AddElement(H, 0.08055);
  Acrylic->AddElement(O, 0.31961);

  G4Material* GdLS  = new G4Material("GdDopedLS", 0.8602*g/cm3, 6);
  GdLS->AddElement(C,  0.87705);
  GdLS->AddElement(H,  0.12051);
  GdLS->AddElement(O,  0.00109);
  GdLS->AddElement(Gd, 0.0010315);
  GdLS->AddElement(elN,  0.00027);
  GdLS->AddElement(S,  0.00005);

  //
  // example of vacuum
  //

  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  new G4Material("Galactic", z=1, a=1.01*g/mole,density,
                 kStateGas,temperature,pressure); 

  // define higher pressure of Argon
  // 
  new G4Material("Ar_P0_1", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.1, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_3", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.3, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.5, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P0_8", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 0.8, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P1_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 1.0, kStateGas, 293.15*kelvin, atmosphere * 1.5);
  new G4Material("Ar_P2_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 2.0, kStateGas, 293.15*kelvin, atmosphere * 2.0);
  new G4Material("Ar_P2_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 2.5, kStateGas, 293.15*kelvin, atmosphere * 2.5);
  new G4Material("Ar_P3_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 3.0, kStateGas, 293.15*kelvin, atmosphere * 3.0);
  new G4Material("Ar_P3_5", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 3.5, kStateGas, 293.15*kelvin, atmosphere * 3.5);
  new G4Material("Ar_P4_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 4.0, kStateGas, 293.15*kelvin, atmosphere * 4.0);
  new G4Material("Ar_P5_0", z=18, a=39.95*g/mole, 1.782*mg/cm3 * 5.0, kStateGas, 293.15*kelvin, atmosphere * 5.0);
  new G4Material("Ar_P10_0",z=18, a=39.95*g/mole, 1.782*mg/cm3 *10.0, kStateGas, 293.15*kelvin, atmosphere * 10.0);

  new G4Material("Xe_P10_0", z=54, a=131.29*g/mole, 5.48536*mg/cm3 * 10.0, kStateGas, 293.15*kelvin, atmosphere * 10.0);

  G4Material* CF4 = new G4Material("CF4", density= 3.720*mg/cm3, ncomponents=2);
  CF4->AddElement(C, natoms=1);
  CF4->AddElement(F, natoms=4);

  G4Material* CF4_P3 = new G4Material("CF4_P3_0", density= 3.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P3->AddElement(C, natoms=1);
  CF4_P3->AddElement(F, natoms=4);

  G4Material* CF4_P5 = new G4Material("CF4_P5_0", density= 5.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P5->AddElement(C, natoms=1);
  CF4_P5->AddElement(F, natoms=4);

  G4Material* CF4_P10 = new G4Material("CF4_P10_0", density= 10.0 * 3.720*mg/cm3, ncomponents=2);
  CF4_P10->AddElement(C, natoms=1);
  CF4_P10->AddElement(F, natoms=4);


  G4Material* ceramics = new G4Material("ceramics", density = 2.88*g/cm3, ncomponents = 2);
  ceramics->AddElement(Al,2);
  ceramics->AddElement(O,3);

  //double rho_DME=0.00197, rho_He=0.0001786, rho_Ne=0.0009002, rho_CF4=0.00372;
  G4Material* DME = new G4Material("DME",density=0.00197*g/cm3,ncomponents=3);
  DME->AddElement(H,natoms=6);
  DME->AddElement(C,natoms=2);
  DME->AddElement(O,natoms=1);

  G4Material* He_20_DME_80 = new G4Material("He_20_DME_80",density = 0.001932*g/cm3,ncomponents=2);
  He_20_DME_80->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_5 = new G4Material("He_20_DME_80_P0_5",density = 0.001932*0.5*g/cm3,ncomponents=2);
  He_20_DME_80_P0_5->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_5->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_6 = new G4Material("He_20_DME_80_P0_6",density = 0.001932*0.6*g/cm3,ncomponents=2);
  He_20_DME_80_P0_6->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_6->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_7 = new G4Material("He_20_DME_80_P0_7",density = 0.001932*0.7*g/cm3,ncomponents=2);
  He_20_DME_80_P0_7->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_7->AddMaterial(DME,fractionmass=97.3*perCent);

  G4Material* He_20_DME_80_P0_8 = new G4Material("He_20_DME_80_P0_8",density = 0.001932*0.8*g/cm3,ncomponents=2);
  He_20_DME_80_P0_8->AddElement(He,    fractionmass=2.7*perCent);
  He_20_DME_80_P0_8->AddMaterial(DME,fractionmass=97.3*perCent);


  G4Material* Ne_80_DME_20 = new G4Material("Ne_80_DME_20",density = 0.00111416*g/cm3,ncomponents=2);
  Ne_80_DME_20->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_5 = new G4Material("Ne_80_DME_20_P0_5",density = 0.00111416*0.5*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_5->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_5->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_6 = new G4Material("Ne_80_DME_20_P0_6",density = 0.00111416*0.6*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_6->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_6->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_7 = new G4Material("Ne_80_DME_20_P0_7",density = 0.00111416*0.7*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_7->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_7->AddMaterial(DME,fractionmass=0.08*perCent);

  G4Material* Ne_80_DME_20_P0_8 = new G4Material("Ne_80_DME_20_P0_8",density = 0.00111416*0.8*g/cm3,ncomponents=2);
  Ne_80_DME_20_P0_8->AddElement(Ne,    fractionmass=99.92*perCent);
  Ne_80_DME_20_P0_8->AddMaterial(DME,fractionmass=0.08*perCent);




  G4Material* Ne_95_CF4_5 = new G4Material("Ne_95_CF4_5", density = 0.00104119*g/cm3, ncomponents = 2);
  Ne_95_CF4_5->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_5 = new G4Material("Ne_95_CF4_5_P0_5", density = 0.00104119*0.5*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_5->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_5->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_6 = new G4Material("Ne_95_CF4_5_P0_6", density = 0.00104119*0.6*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_6->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_6->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_7 = new G4Material("Ne_95_CF4_5_P0_7", density = 0.00104119*0.7*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_7->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_7->AddMaterial(CF4, fractionmass = 17.86*perCent);

  G4Material* Ne_95_CF4_5_P0_8 = new G4Material("Ne_95_CF4_5_P0_8", density = 0.00104119*0.8*g/cm3, ncomponents = 2);
  Ne_95_CF4_5_P0_8->AddElement(Ne  , fractionmass = 82.14*perCent);
  Ne_95_CF4_5_P0_8->AddMaterial(CF4, fractionmass = 17.86*perCent);

  //G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}
#endif