
#include "rockSensorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4SystemOfUnits.hh"

G4Allocator<rockSensorHit> rockSensorHitAllocator;


rockSensorHit::rockSensorHit():
              copyNO(-1),
              trackID(0),
	      codePDG(0),
	      charge(0.0),
	      energy(0.0),
	      time(0.0),
		  eDep(0.0)
{}


rockSensorHit::~rockSensorHit() 
{}



rockSensorHit::rockSensorHit(const rockSensorHit& right)
  : G4VHit()
{
  copyNO      = right.copyNO;
  trackID     = right.trackID;
  codePDG     = right.codePDG;
  charge      = right.charge;
  energy      = right.energy;
  momentum    = right.momentum;
  pos         = right.pos;
  eDep 		= right.eDep;
  
}


const rockSensorHit& rockSensorHit::operator=(const rockSensorHit& right)
{
  if (this != &right) {
    copyNO      = right.copyNO;
    trackID     = right.trackID;
    codePDG     = right.codePDG;
    charge      = right.charge;
    energy      = right.energy;
    momentum    = right.momentum;
    pos         = right.pos;
	eDep 		= right.eDep;
  }
  return *this;
}



G4int rockSensorHit::operator==(const rockSensorHit& right) const
{
  return (this==&right) ? 1 : 0;
}


void rockSensorHit::Set(int copy, const G4Track* track,G4double eLoss)
{
  copyNO   =  copy;
  eDep		= eLoss;

  trackID  =  track->GetTrackID();
  codePDG  =  track->GetDefinition()->GetPDGEncoding();
  charge   =  track->GetDefinition()->GetPDGCharge();
  energy   =  track->GetKineticEnergy();
  momentum =  track->GetMomentum();
  pos      =  track->GetPosition();
  if(time > track->GetGlobalTime()){
  time     =  track->GetGlobalTime();
  }
}

void rockSensorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager){
    G4Circle circle(pos);
    circle.SetScreenSize(2.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}



void rockSensorHit::Print()
{
  G4cout << "Copy Number: " << copyNO << G4endl; 
  G4cout << "TrackID: " << trackID << G4endl; 
  G4cout << "PDG code: "<< codePDG << "  "
         << "charge: " << charge/eplus << G4endl;
  G4cout << "enregy: " << energy /MeV  << G4endl;
  G4cout << "momentum: "<< momentum.x()/MeV << " "
	 << momentum.y()/MeV << " "
	 << momentum.z()/MeV << G4endl;
  G4cout << "position: "<< pos.x()/mm << " "
	 << pos.y()/mm << " "
	 << pos.z()/mm << G4endl;
  G4cout << "time: "<< time/ns << G4endl;
  G4cout << "Energy deposit" << eDep/MeV << G4endl;
}



