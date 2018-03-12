
#include "rockEventAction.hh"

#include "rockRunAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>


rockEventAction::rockEventAction(rockRunAction* action)
{
  runAction = action;
}


rockEventAction::~rockEventAction()
{
}


void rockEventAction::BeginOfEventAction(const G4Event*)
{  
}


void rockEventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();   
  if (evtNb%1000  == 0) {
    G4cout << " Event #" << evtNb << G4endl;
  }
}  


