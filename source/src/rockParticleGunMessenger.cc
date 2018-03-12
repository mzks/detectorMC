#include "rockParticleGun.hh"
#include "rockParticleGunMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include <iostream>


rockParticleGunMessenger::rockParticleGunMessenger()
	:rockPG(0)
{
}

rockParticleGunMessenger::rockParticleGunMessenger(rockParticleGun* pg)
	:G4UImessenger(),
	rockPG(pg)
{

	//gunDir = new G4UIdirectory("/gun/");
	//gunDir->SetGuidance("UI commands for rock simulation");

	cmdDir = new G4UIdirectory("/gun/rock/");
	cmdDir->SetGuidance("UI commands for primary generator");

	vtxCmd = new G4UIcmdWithAnInteger("/gun/rock/vtx",this);
	vtxCmd->SetGuidance("Select vertex 0:User 1:Top 2:centre 3:Random flux");
	vtxCmd->SetParameterName("vtx",false);
	vtxCmd->SetRange("vtx >= 0 && vtx <= 3");
	vtxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	parCmd = new G4UIcmdWithAnInteger("/gun/rock/particle",this);
	parCmd->SetGuidance("Select particle 0:User 1:neutron 2:mu- 3:Random flux neutron 4:Real neutron spectrum 5:fission(Cf)");
	parCmd->SetParameterName("part",false);
	parCmd->SetRange("part >= 0 && part <= 5");
	parCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

	eneCmd = new G4UIcmdWithADoubleAndUnit("/gun/rock/energy",this);
	eneCmd->SetGuidance("set energy for neutron flux");
	eneCmd->SetParameterName("ene",false);
	eneCmd->SetRange("ene > 0.");
	eneCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

rockParticleGunMessenger::~rockParticleGunMessenger()
{
	delete vtxCmd;
	delete parCmd;
	delete eneCmd;
	delete cmdDir;

}

void rockParticleGunMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
	if (command == vtxCmd ){
		rockPG->positionFlag = vtxCmd->GetNewIntValue(newValue);
	}else if ( command == parCmd){
		rockPG->particleFlag = parCmd->GetNewIntValue(newValue);
	}else if ( command == eneCmd){
		rockPG->monoEnergy = eneCmd->GetNewDoubleValue(newValue);
	}

}

G4String rockParticleGunMessenger::GetCurrentValue(G4UIcommand* command)
{
	G4String cv;

	if (command == vtxCmd ){
		cv = vtxCmd->ConvertToString(rockPG->positionFlag);
	}else if ( command == parCmd){
		cv = parCmd->ConvertToString(rockPG->particleFlag);
	}else if ( command == eneCmd){
		cv = eneCmd->ConvertToString(rockPG->monoEnergy, "cm");
	}

	return cv;

}
