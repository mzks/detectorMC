

#ifndef rockRunAction_h
#define rockRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"


class G4Run;

class rockRunAction : public G4UserRunAction
{
  public:
    rockRunAction();
   ~rockRunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    
  private:
};


#endif

