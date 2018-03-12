


#ifndef rockSensorSD_h
#define rockSensorSD_h 1

#include "G4VSensitiveDetector.hh"
#include "rockSensorHit.hh"

#include <iomanip>
#include <fstream>       

class G4Step;
class G4HCofThisEvent;


class rockSensorSD : public G4VSensitiveDetector
{
  public:
   rockSensorSD(G4String);
   ~rockSensorSD();

   void Initialize(G4HCofThisEvent*);
   G4bool ProcessHits(G4Step*, G4TouchableHistory*);
   void EndOfEvent(G4HCofThisEvent*);

   G4double GetThresholdEnergy() const {return eThreshold;}
   G4double GetTimeResolution()  const {return tResolution;}

   static const G4String& GetCollectionName() {return HCname;}
  
  private:
   rockSensorHitsCollection* sensorCollection;
   std::ofstream outFile;

   G4double eThreshold;
   G4double tResolution;

   static const G4String HCname;

};


#endif

