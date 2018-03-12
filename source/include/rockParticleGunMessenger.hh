#ifndef rockParticleGunMessenger_h
#define rockParticleGunMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"
#include "rockParticleGun.hh"

class rockParticleGun;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;


class rockParticleGunMessenger: public G4UImessenger
{
	public:
		rockParticleGunMessenger();
		explicit rockParticleGunMessenger(rockParticleGun*);
		~rockParticleGunMessenger();

		void SetNewValue(G4UIcommand*, G4String);
		G4String GetCurrentValue(G4UIcommand* command);
	private:
		rockParticleGun*		rockPG;
		G4UIdirectory*			cmdDir;
		//G4UIdirectory*			gunDir;
		G4UIcmdWithAnInteger*		vtxCmd;
		G4UIcmdWithAnInteger*		parCmd;
        G4UIcmdWithADoubleAndUnit*  eneCmd;

};

#endif

