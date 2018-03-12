#ifndef rockPhysicsList_h
#define rockPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"


class rockPhysicsList: public G4VUserPhysicsList
{
  public:
    rockPhysicsList();
   ~rockPhysicsList();

  protected:
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
 
    void SetCuts();

   
  protected:
    // these methods Construct particles 
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();

  protected:
    // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();
    void ConstructOp();
};


#endif



