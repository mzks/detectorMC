
#include "rockPrimaryGeneratorAction.hh"

#include "rockDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4MuonMinus.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "rockParticleGun.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

rockPrimaryGeneratorAction::rockPrimaryGeneratorAction(
                           const rockDetectorConstruction* rockDC)
  :rockDetector(rockDC),
	particleTable(G4ParticleTable::GetParticleTable())
{
	particleGun = new rockParticleGun();
	G4ParticleDefinition* particle = particleTable->FindParticle("geantino");
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleMomentumDirection(G4ThreeVector(1.0,0.0,0.0));
	particleGun->SetParticleEnergy(electron_mass_c2);
	particleGun->SetParticlePosition(G4ThreeVector(0.0,0.0,0.0));


}



rockPrimaryGeneratorAction::~rockPrimaryGeneratorAction()
{
  delete particleGun;
}



void rockPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	particleGun->GeneratePrimaryVertex(anEvent);

}



