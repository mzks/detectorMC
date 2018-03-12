// ------------------------------------ //
// rock.cc
// Mizukoshi keita
// ------------------------------------ //
#include "rockDetectorConstruction.hh"
#include "rockPhysicsList.hh"
#include "rockPrimaryGeneratorAction.hh"
#include "rockRunAction.hh"
#include "rockEventAction.hh"
#include "rockParticleGun.hh"
#include "rockParticleGunMessenger.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"


#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif




int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Choose the Random engine
  //
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
     
  // Construct the default run manager
  //
  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes
  //
  rockDetectorConstruction* detector = new rockDetectorConstruction;
  runManager->SetUserInitialization(detector);
 
  // Physics list
  G4VModularPhysicsList* physicsList = new QGSP_BERT_HP;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // Set user action classes
  //
  G4VUserPrimaryGeneratorAction* gen_action = new rockPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);
  //
  rockRunAction* run_action = new rockRunAction;  
  runManager->SetUserAction(run_action);
  //
  rockEventAction* event_action = new rockEventAction(run_action);
  runManager->SetUserAction(event_action);
 
  //rockSteppingAction* stepping_action = new rockSteppingAction();
  //runManager->SetUserAction(stepping_action);

  //Initialize G4 kernel
  //runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
   
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}

