//

#ifndef rockEventAction_h
#define rockEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class rockRunAction;



class rockEventAction : public G4UserEventAction
{
 public:
   rockEventAction(rockRunAction*);
  ~rockEventAction();

 public:
   void  BeginOfEventAction(const G4Event*);
   void  EndOfEventAction(const G4Event*);
    
    
 private:
  rockRunAction* runAction;                          

};


#endif

    
