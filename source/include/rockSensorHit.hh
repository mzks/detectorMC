
#ifndef rockSensorHit_h
#define rockSensorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"

class rockSensorHit : public G4VHit
{
  public:

      rockSensorHit();
     ~rockSensorHit();
      rockSensorHit(const rockSensorHit&);
      const rockSensorHit& operator=(const rockSensorHit&);
      G4int operator==(const rockSensorHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

      void Draw();
      void Print();

  public:
  
      void Set(int copy, const G4Track* track ,G4double eLoss);
      
      G4int GetCopyNO()             const  { return copyNO; };
      G4int GetTrackID()            const  { return trackID; };
      G4int GetPDGcode()            const  { return codePDG; };
      G4double GetCharge()          const  { return charge; };      
      G4double GetEnergy()          const  { return energy; };      
      const G4ThreeVector& GetMomentum() const  { return momentum; };
      const G4ThreeVector& GetPos()      const  { return pos; };
      G4double GetTime()                 const  { return time; };      
	  G4double GetEdep() const { return eDep;};
	  void AddEdep(G4double val){ eDep += val;};
     
  private:
      G4int         copyNO;
      G4int         trackID;
      G4int         codePDG;
      G4double      charge;
      G4double      energy;
      G4ThreeVector momentum;
      G4ThreeVector pos;
      G4double      time;
	  G4double 		eDep;
 };


typedef G4THitsCollection<rockSensorHit> rockSensorHitsCollection;

extern G4Allocator<rockSensorHit> rockSensorHitAllocator;


inline void* rockSensorHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) rockSensorHitAllocator.MallocSingle();
  return aHit;
}


inline void rockSensorHit::operator delete(void *aHit)
{
  rockSensorHitAllocator.FreeSingle((rockSensorHit*) aHit);
}


#endif
