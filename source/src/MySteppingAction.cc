#include "MySteppingAction.hh"
#include "MyEventAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyAnalysisManager.hh"
#include "SimEvent.hh"
#include "Verbose.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"

MySteppingAction::MySteppingAction()
: G4UserSteppingAction()
{
  if(verbose) G4cout << "====>MySteppingAction::MySteppingAction(MyDetectorConstruction *, MyEventAction *)" << G4endl;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step)
{
  if(verbose) G4cout << "====>MySteppingAction::UserSteppingAction(const G4Step* step)" << G4endl;

    // positions in the global coordinate system:
    G4StepPoint* PreStep  = step->GetPreStepPoint();
    G4StepPoint* PostStep = step->GetPostStepPoint();


    G4ThreeVector posPreStep  = PreStep->GetPosition();
    G4ThreeVector posPostStep = PostStep->GetPosition();

    G4TouchableHandle touchPreStep = PreStep->GetTouchableHandle();
    G4TouchableHandle touchPostStep = PostStep->GetTouchableHandle();

    //To get the current volume:
    G4VPhysicalVolume* volumePre = touchPreStep->GetVolume();
    G4VPhysicalVolume* volumePost =touchPostStep->GetVolume();

    //To get its name:
    G4String namePre = volumePre->GetName();
    G4String namePost= (volumePost==NULL)?"Null":volumePost->GetName();
    //G4cout<< namePost << G4endl;

    G4Track* aTrack = step->GetTrack();

    SimEvent *fEvt = MyAnalysisManager::GetInstance()->GetSimEvent();

  G4double edep = step->GetTotalEnergyDeposit();
  G4double x0 = step->GetPostStepPoint()->GetPosition().x();     
  G4double y0 = step->GetPostStepPoint()->GetPosition().y();   

  if(namePost == "Gas")   { fEvt->AddEdepGas(edep); }   // Edep of Gas
  if(namePost == "Wafer") { fEvt->AddEdepSi (edep); }   // Edep of Si

#if 1
  if(aTrack->GetParentID() == 0 && namePre == "World" && namePost=="Scope_I"){
    G4ThreeVector momentum(aTrack->GetMomentum());
    G4double x = x0+40/momentum.z()*momentum.x()*mm; 
    G4double y = y0+40/momentum.z()*momentum.y()*mm;
    if(x >= -7.5*mm && x <= 7.5*mm && y >= -7.5*mm && y <= 7.5*mm) 
      fEvt->AddCount();
  }
  // calculate efficiency
#endif

   
    // G4ParticleDefinition* particle = particleTable->FindParticle(ParticleType="e-");
#if 1
  if(aTrack->GetParticleDefinition()->GetParticleName()=="e-" && namePre == "Be" && namePost == "Gas")
  {
    fEvt->AddECount();
  }
#endif

// Should be off if lots of beam on
#if SWITCH
  // PAD
  if(namePost == "Gas")
  {
    //     G4double z = step->GetPostStepPoint()->GetPosition().z();    
    // -7.5mm ~ 7.5mm
    G4double sz = 15/PAD_NUM; //without mm
    
    for(int i=0; i!=PAD_NUM; ++i){
      if(x >= (-7.5 + i*sz)*mm && x < (-7.5 + (i+1)*sz)*mm){
        for(int j=0; j!=PAD_NUM; ++j){ 
          if(y >= (-7.5 + j*sz)*mm && y < (-7.5 + (j+1)*sz)*mm){
            fEvt->AddEdepPad(i, j, edep);
          }
        }
      }
    }
  }

  // E count
  // 电子产生在Be
  // 并且进入气体
  // if(namePost == "Gas") 

  // pre==Be
#endif
}