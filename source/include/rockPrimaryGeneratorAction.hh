
#ifndef rockPrimaryGeneratorAction_h
#define rockPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

//class G4ParticleGun;
class G4ParticleGun;
class G4ParticleTable;
class G4Event;
class rockDetectorConstruction;

class rockPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    rockPrimaryGeneratorAction(const rockDetectorConstruction*);    
   ~rockPrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

private:
    G4ParticleGun*              particleGun;	  //pointer a to G4  class
	G4ParticleTable*			particleTable;
    const rockDetectorConstruction* rockDetector;  
};


#endif


