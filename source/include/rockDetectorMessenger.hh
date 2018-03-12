
#ifndef rockDetectorMessenger_h
#define rockDetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class rockDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;


class rockDetectorMessenger: public G4UImessenger
{
  public:
    rockDetectorMessenger(rockDetectorConstruction* );
   ~rockDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
  G4String GetCurrentValue(G4UIcommand * command);

  private:
    rockDetectorConstruction* rockDetector;
    
    G4UIdirectory*             rockDir;
    G4UIdirectory*             detDir;
    G4UIcmdWithAString*        MaterialCmd;
    G4UIcmdWithADoubleAndUnit* ThicknessCmd;
    G4UIcmdWithADoubleAndUnit* SizeYZCmd;
    G4UIcmdWithADoubleAndUnit* ArmCmd;
    G4UIcmdWithADoubleAndUnit* MaxStepCmd;
    G4UIcmdWithADoubleAndUnit* MagFieldCmd;
    G4UIcmdWithADoubleAndUnit* PESizeCmd;
    G4UIcmdWithADoubleAndUnit* BoronSizeCmd;
};


#endif

