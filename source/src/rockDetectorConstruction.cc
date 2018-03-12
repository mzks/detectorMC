#include "rockDetectorConstruction.hh"
#include "rockDetectorMessenger.hh"
#include "rockSensorSD.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4SDManager.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include <iostream>


////////////////////////////////////////////////////////////

rockDetectorConstruction::rockDetectorConstruction()
	:pSensorMaterial(0),vSensorThickness(0.),vSensorSize(0.),
	vSensorArm(0.),defaultMaterial(0),
	solidWorld(0),logicWorld(0),physWorld(0),
	solidSensor(0),logicSensor(0),physSensor(0),
	magField(0), pUserLimits(0),
	maxStep(100.0*cm),
	mat_3He(0),mat_detector(0),mat_polyethylene(0),mat_boron(0),
	solidAir(0),logicAir(0),physAir(0),
	solidShield(0),logicShield(0),physShield(0)
{

	// default parameter values of Sensor
	vSensorThickness =  5 *mm;
	vRockSize		=	1.0 * m;

	vSensorSize      = 100.*cm;//UnUse
	vSensorArm       = 200.*cm;//UnUse

	// materials
	DefineMaterials();
	SetSensorMaterial("Herium3");

	// World Size
	WorldSizeYZ =  500.0 *cm;//Unuse
	WorldSizeX = 100.0 * m;//Unuse

	// create commands for interactive definition of the calorimeter
	detectorMessenger = new rockDetectorMessenger(this);

	PEThickness = 5.0*cm;
	BoronThickness = 0.5*cm;
}

/////////////////////////////////////////////////////////

rockDetectorConstruction::~rockDetectorConstruction()
{ 
	delete detectorMessenger;
}

////////////////////////////////////////////////////////

G4VPhysicalVolume* rockDetectorConstruction::Construct()
{
	// Clean old geometry, if any
	//
	G4GeometryManager::GetInstance()->OpenGeometry();
	G4PhysicalVolumeStore::GetInstance()->Clean();
	G4LogicalVolumeStore::GetInstance()->Clean();
	G4SolidStore::GetInstance()->Clean();

	//     
	// World
	//
	//
	//
	WorldSizeX = 50*cm;

	//solidWorld = new G4Box("World",				//its name
	//WorldSizeX/2.0,WorldSizeX/2.0,WorldSizeX/2.0);	//its size
	solidWorld = new G4Orb("World",WorldSizeX);

	logicWorld = new G4LogicalVolume(solidWorld,		//its solid
			defaultMaterial,	//its material
			"World");		//its name

	physWorld = new G4PVPlacement(0,			//no rotation
			G4ThreeVector(),	//at (0,0,0)
			logicWorld,		//its logical volume	 
			"World",		//its name
			0,			//its mother  volume
			false,			//no boolean operation
			0);			//copy number

	solidShield = new G4Box("Shield",30.0*cm/2.0,30.0*cm/2.0,63.0*cm/2.0);
	logicShield = new G4LogicalVolume(solidShield, mat_polyethylene, "Shield");
	physShield = new G4PVPlacement(0,G4ThreeVector(),logicShield,"Shield",logicWorld,false,1001);

	solidAir = new G4Box("Air",20.0*cm/2.0,20.0*cm/2.0,53.0*cm/2.0);
	logicAir = new G4LogicalVolume(solidAir, mat_air, "Air");
	physAir = new G4PVPlacement(0,G4ThreeVector(),logicAir,"Air",logicShield,false,1000);


	solidBoron = new G4Tubs("Boron",
			0.0*cm,
			9.09*cm+BoronThickness, //boron thickness 0.5 cm
			25.5*cm+BoronThickness,
			0,
			CLHEP::twopi);
	logicBoron = new G4LogicalVolume(solidBoron,
			mat_boron,  // CAUTION
			//mat_air, //Change materials
			"Boron");
	physBoron = new G4PVPlacement(0,G4ThreeVector(),logicBoron,"Boron",logicAir,false,203);

	solidPolyethylene = new G4Tubs("Polyethylene",
			0.0*cm,
			9.09*cm,
			25.5*cm,
			0,
			CLHEP::twopi);
	logicPolyethylene = new G4LogicalVolume(solidPolyethylene,
			mat_polyethylene, //Change materials
			//mat_air,//CAUTION
			"Polyethylene");
	physPolyethylene = new G4PVPlacement(0,G4ThreeVector(),logicPolyethylene,"Polyethylene",logicBoron,false,200);

	solidDetector = new G4Tubs("Detector",
			0.0*cm,
			2.59*cm,
			19.00*cm,
			0,
			CLHEP::twopi);
	logicDetector = new G4LogicalVolume(solidDetector,
			mat_detector,
			"Detector");
	physDetector = new G4PVPlacement(0,G4ThreeVector(),logicDetector,"Detector",logicPolyethylene,false,201);


	solidSensor = new G4Tubs("Sensor",
			0.0*cm,
			2.54*cm,
			18.95*cm,
			0,
			CLHEP::twopi);
	logicSensor = new G4LogicalVolume(solidSensor,
			mat_3He	,
			"Sensor");
	physSensor = new G4PVPlacement(0,G4ThreeVector(),logicSensor,"Sensor",logicDetector,false,202);




	// Rock
	//  solidRock = new G4Box("Rock",
	//		  			vRockSize/2,vRockSize/2,vRockSize/2);
	//
	//  logicRock = new G4LogicalVolume(solidRock,
	//		  							pSensorMaterial,
	//									"Rock");
	//  physRock  = new G4PVPlacement(0,
	//		  		G4ThreeVector(),
	//				logicRock,
	//				"Rock",
	//				logicWorld,
	//				false,
	//				100);
	//  
	//                               
	// Traget
	//  

	//  solidSensor = new G4Box("Sensor",		//its name
	//   		  vSensorThickness/2,vRockSize/2,vRockSize/2);//size
	// 
	// logicSensor = new G4LogicalVolume(solidSensor,	//its solid
	//   			    pSensorMaterial,	//its material
	//   			    "Sensor");       	//its name
	// G4RotationMatrix matY = G4RotationMatrix();
	// matY.rotateY(90.0*deg);
	// G4RotationMatrix matZ = G4RotationMatrix();
	// matZ.rotateZ(90.0*deg);

	// sensors
	//  physSensor = new G4PVPlacement(0,			//no rotation
	//				 G4ThreeVector((WorldSizeX-vSensorThickness)/2,0,0),       //position
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 0);	        	//copy number
	// 
	//   physSensor = new G4PVPlacement(0,			//no rotation
	//				 G4ThreeVector(-(WorldSizeX-vSensorThickness)/2,0,0),  //position
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 1);	        	//copy number
	//
	//   physSensor = new G4PVPlacement(
	//		   		G4Transform3D(matZ, G4ThreeVector(0,(WorldSizeX-vSensorThickness)/2,0)),
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 2);	        	//copy number
	//
	//   physSensor = new G4PVPlacement(
	//		   		G4Transform3D(matZ, G4ThreeVector(0,-(WorldSizeX-vSensorThickness)/2,0)),
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 3);	        	//copy number
	//
	//   physSensor = new G4PVPlacement(
	//		   		G4Transform3D(matY, G4ThreeVector(0,0,(WorldSizeX-vSensorThickness)/2)),
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 4);	        	//copy number
	//
	//   physSensor = new G4PVPlacement(
	//		   		G4Transform3D(matY, G4ThreeVector(0,0,-(WorldSizeX-vSensorThickness)/2)),
	//				 logicSensor,   	//its logical volume
	//				 "Sensor",	        //its name
	//				 logicWorld,    	//its mother  volume
	//				 false,  		//no boolean operation
	//				 5);	        	//copy number
	//
	//------------------------------------------------ 
	// Sensitive detectors
	//------------------------------------------------ 

	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	rockSensorSD* aSensorSD = (rockSensorSD*)SDman->FindSensitiveDetector( "rock/SensorSD");
	if ( aSensorSD == 0){
		aSensorSD = new rockSensorSD(  "rock/SensorSD" );
		SDman->AddNewDetector( aSensorSD );
	}
	logicSensor->SetSensitiveDetector( aSensorSD );

	// Set UserLimits
	G4double maxTrkLen = 10.0*WorldSizeX;
	G4double maxTime   = 1000.0 * ns;
	pUserLimits = new G4UserLimits(maxStep, maxTrkLen, maxTime);
	logicWorld->SetUserLimits(pUserLimits);



	//                                        
	// Visualization attributes
	//


	logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

	G4VisAttributes* simpleBoxVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
	simpleBoxVisAtt->SetVisibility(true);
	logicSensor->SetVisAttributes(simpleBoxVisAtt);

	//always return the physical World

	return physWorld;
}


///////////////////////////////////////////////////////
void rockDetectorConstruction::DefineMaterials()
{ 
	//This function illustrates the possible ways to define materials

	G4String symbol,name;             //a=mass of a mole;
	G4double a, z, density,temperature,pressure;      //z=mean number of protons;  
	G4int iz, n,in;                 //iz=number of protons  in an isotope; 
	// n=number of nucleons in an isotope;

	G4int ncomponents, natoms;
	G4double abundance, fractionmass;

	//
	// define Elements
	//

	G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
	G4Element* B  = new G4Element("Boron",symbol="B" , z= 5., a= 10.81*g/mole);
	G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
	G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
	G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
	G4Element* Na = new G4Element("Sodium",symbol="Na" , z= 11., a= 22.99*g/mole);
	G4Element* Mg = new G4Element("Magnesium",symbol="Mg" , z= 12., a= 24.31*g/mole);
	G4Element* Al = new G4Element("Aluminium",symbol="Al" , z= 13., a= 26.98*g/mole);
	G4Element* Si = new G4Element("Silicon",symbol="Si" , z= 14., a= 28.09*g/mole);
	G4Element* P = new G4Element("Phosphorus",symbol="P" , z= 15., a= 30.97*g/mole);
	G4Element* K = new G4Element("Kalium",symbol="K" , z= 19., a= 39.10*g/mole);
	G4Element* Ca = new G4Element("Calcium",symbol="Ca" , z= 20., a= 40.01*g/mole);
	G4Element* Ti = new G4Element("Titan",symbol="Ti" , z= 22., a= 47.87*g/mole);
	G4Element* Mn = new G4Element("Manganese",symbol="Mn" , z= 25., a= 54.94*g/mole);
	G4Element* Fe = new G4Element("Iron",symbol="Fe" , z= 26., a= 55.85*g/mole);


	//
	// define an Element from isotopes, by relative abundance 
	//


	G4Isotope* U5 = new G4Isotope("U235", iz=92, n=235, a=235.01*g/mole);
	G4Isotope* U8 = new G4Isotope("U238", iz=92, n=238, a=238.03*g/mole);

	G4Element* U  = new G4Element("enriched Uranium",symbol="U",ncomponents=2);
	U->AddIsotope(U5, abundance= 90.*perCent);
	U->AddIsotope(U8, abundance= 10.*perCent);

	//
	// define simple materials
	//

	//new G4Material("Aluminium", z=13., a=26.98*g/mole, density=2.700*g/cm3);
	new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
	new G4Material("Lead"     , z=82., a= 207.19*g/mole, density= 11.35*g/cm3);
	new G4Material("Tungsten" , z=74., a= 183.84*g/mole, density= 19.25*g/cm3);
	//new G4Material("Iron" , z=26., a= 55.845*g/mole, density= 7.874*g/cm3);

	//
	// define a material from elements.   case 1: chemical molecule
	//

	G4Material* H2O = 
		new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
	H2O->AddElement(H, natoms=2);
	H2O->AddElement(O, natoms=1);
	// overwrite computed meanExcitationEnergy with ICRU recommended value 
	H2O->GetIonisation()->SetMeanExcitationEnergy(75.0*eV);

	G4Material* Sci = 
		new G4Material("Scintillator", density= 1.032*g/cm3, ncomponents=2);
	Sci->AddElement(C, natoms=9);
	Sci->AddElement(H, natoms=10);

	G4Material* Myl = 
		new G4Material("Mylar", density= 1.397*g/cm3, ncomponents=3);
	Myl->AddElement(C, natoms=10);
	Myl->AddElement(H, natoms= 8);
	Myl->AddElement(O, natoms= 4);

	G4Material* SiO2 = 
		new G4Material("quartz",density= 2.200*g/cm3, ncomponents=2);
	SiO2->AddElement(Si, natoms=1);
	SiO2->AddElement(O , natoms=2);

	//
	// define a material from elements.   case 2: mixture by fractional mass
	//

	G4Material* Air = 
		new G4Material("Air"  , density= 1.290*mg/cm3, ncomponents=2);
	Air->AddElement(N, fractionmass=0.7);
	Air->AddElement(O, fractionmass=0.3);

	G4Material* RockKam =
		new G4Material("RockKam", density= 3.0*g/cm3, ncomponents=13);
	RockKam->AddElement(H, fractionmass=0.006);
	RockKam->AddElement(C, fractionmass=0.003);
	RockKam->AddElement(O, fractionmass=0.607);
	RockKam->AddElement(Na, fractionmass=0.039);
	RockKam->AddElement(Mg, fractionmass=0.003);
	RockKam->AddElement(Al, fractionmass=0.106);
	RockKam->AddElement(Si, fractionmass=0.185);
	RockKam->AddElement(P, fractionmass=0.001);
	RockKam->AddElement(K, fractionmass=0.021);
	RockKam->AddElement(Ca, fractionmass=0.018);
	RockKam->AddElement(Ti, fractionmass=0.001);
	RockKam->AddElement(Mn, fractionmass=0.000);
	RockKam->AddElement(Fe, fractionmass=0.010);

	//define for detector
	// stailess SUS304
	G4Element* Ni = new G4Element( "Nickel", "Ni", 28., 58.69*g/mole);
	//G4Element* Mn = new G4Element( "Manganese", "Mn", 25., 54.93*g/mole);
	G4Element* Cr = new G4Element( "Chromium", "Cr", 24., 51.996*g/mole);
	G4Material* sus304 = new G4Material(name="Sus304", density=8.03*g/cm3, ncomponents=5);
	sus304->AddElement(Ni, 0.09);
	sus304->AddElement(C, 0.005);
	sus304->AddElement(Mn, 0.01);
	sus304->AddElement(Cr, 0.18);
	sus304->AddElement(Fe, 0.715);
	G4Material* polyethylene=new G4Material(name="polyethylene",density=0.92*g/cm3,ncomponents=2);	
	polyethylene->AddElement(C,1);
	polyethylene->AddElement(H,2);
	G4Isotope* he3 = new G4Isotope(name="he3", iz=2, in=3, a=3.0160293191*g/mole);
	G4Element* He3 = new G4Element(name="He3", symbol="He3", ncomponents=1);
	He3->AddIsotope(he3, abundance=100.*perCent);
	G4Material* Herium3 = new G4Material(name="Herium3",density=1.34644166*mg/cm3,ncomponents=1,kStateGas,temperature=300.15*kelvin,pressure=10.*atmosphere);
	Herium3->AddElement(He3, 1);

	//the follow definition from CANDLES MC

	// Sillion rubber + B4C 40%
	//   //  http://www.askcorp.co.jp/sanshin/work/engineering/pdf/material.pdf
	//     //-------------------------------------------------//
	const G4double R_B4C  = 40;    // target value, wt-%
	//-------------------------------------------------//
	const G4double R0_B4C = 20;    // original value, wt-%
	const G4double W0_H   = 0.065; // fraction Mass
	const G4double W0_O   = 0.173;
	const G4double W0_Si  = 0.303;
	const G4double W0_B   = 0.157;
	const G4double W0_C   = 0.302;

	G4double totalMass = R_B4C / R0_B4C * (W0_B + W0_C) + (100.0 - R_B4C) / (100.0 - R0_B4C) * (W0_H + W0_O + W0_Si);
	G4double W_H       = (100.0 - R_B4C) / (100.0 - R0_B4C) * W0_H  / totalMass;
	G4double W_O       = (100.0 - R_B4C) / (100.0 - R0_B4C) * W0_O  / totalMass;
	G4double W_Si      = (100.0 - R_B4C) / (100.0 - R0_B4C) * W0_Si / totalMass;
	G4double W_B       = R_B4C / R0_B4C * W0_B / totalMass;
	G4double W_C       = R_B4C / R0_B4C * W0_C / totalMass;

	// ref. density (2015/7/30 from T.Iida)
	G4Material* RubberB4C = new G4Material("RubberB4C", density = 1.42 *g/cm3, ncomponents = 5);
	RubberB4C -> AddElement(H,  fractionmass = W_H);
	RubberB4C -> AddElement(O,  fractionmass = W_O);
	RubberB4C -> AddElement(Si, fractionmass = W_Si);
	RubberB4C -> AddElement(B,  fractionmass = W_B);
	RubberB4C -> AddElement(C,  fractionmass = W_C);


	//define a material from elements and/or others materials (mixture of mixtures)


	G4Material* Aerog = 
		new G4Material("Aerogel", density= 0.200*g/cm3, ncomponents=3);
	Aerog->AddMaterial(SiO2, fractionmass=62.5*perCent);
	Aerog->AddMaterial(H2O , fractionmass=37.4*perCent);
	Aerog->AddElement (C   , fractionmass= 0.1*perCent);

	//
	// examples of gas in non STP conditions
	//

	G4Material* CO2 = 
		new G4Material("CarbonicGas", density= 27.*mg/cm3, ncomponents=2,
				kStateGas, 325.*kelvin, 2.*atmosphere);
	CO2->AddElement(C, natoms=1);
	CO2->AddElement(O, natoms=2);

	G4Material* steam = 
		new G4Material("WaterSteam", density= 0.3*mg/cm3, ncomponents=1,
				kStateGas, 500.*kelvin, 2.*atmosphere);
	steam->AddMaterial(H2O, fractionmass=1.);

	//
	// examples of vacuum
	//

	G4Material* Vacuum =
		new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
				kStateGas, 2.73*kelvin, 3.e-18*pascal);

	G4Material* beam = 
		new G4Material("Beam", density= 1.e-5*g/cm3, ncomponents=1,
				kStateGas, STP_Temperature, 2.e-2*bar);
	beam->AddMaterial(Air, fractionmass=1.);

	G4cout << *(G4Material::GetMaterialTable()) << G4endl;

	//default materials of the World
	defaultMaterial  = Vacuum;
	mat_3He = Herium3;
	mat_detector = sus304;
	mat_polyethylene = polyethylene;
	mat_boron = RubberB4C;
    mat_air = Air;
}

///////////////////////////////////////////////////////
void rockDetectorConstruction::SetMaxStep(G4double value)
{
	//--------- example of User Limits -------------------------------
	// below is an example of how to set tracking constraints in a given
	// logical volume
	//
	if (value >0.) {
		maxStep = value;
	} else {
		maxStep = DBL_MAX;
	}
	if (pUserLimits) {
		delete pUserLimits;
	}
	UpdateGeometry();
}
/////////////////////////////////////////////////////////////

void rockDetectorConstruction::SetSensorMaterial(G4String materialChoice)
{
	// search the material by its name
	G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
	if (pttoMaterial) {
		pSensorMaterial = pttoMaterial;
		G4cout << " rockDetectorConstruction::SetSensorMaterial:  ";
		G4cout << "Sensor material is " << materialChoice << G4endl;
		UpdateGeometry();
	} else {
		G4cout << " rockDetectorConstruction::SetSensorMaterial:  ";
		G4cout << materialChoice << " is not in the Material Table.";
		G4cout <<G4endl;
	}
}

//////////////////////////////////////////////////////////////

void rockDetectorConstruction::SetSensorThickness(G4double val)
{
	if (2*val < vSensorArm) {
		vSensorThickness = val;
		G4cout << " rockDetectorConstruction::SetSensorThickness:  ";
		G4cout << "Sensor thickness is " << val/mm << "mm" << G4endl;
		UpdateGeometry();
	}
}

//////////////////////////////////////////////////////////////

void rockDetectorConstruction::SetSensorSize(G4double val)
{
	if (val<WorldSizeX) {
		vSensorSize = val;
		UpdateGeometry();
	}
}
//////////////////////////////////////////////////////////////

void rockDetectorConstruction::SetSensorLeverArm(G4double val)
{
	if (val+vSensorThickness<WorldSizeX) {
		vSensorArm = val;
		UpdateGeometry();
	}
}

void rockDetectorConstruction::SetPESize(G4double val)
{
		PEThickness = val;
		UpdateGeometry();
}

void rockDetectorConstruction::SetBoronSize(G4double val)
{
		BoronThickness = val;
		UpdateGeometry();
}


///////////////////////////////////////////////////////////////////

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

void rockDetectorConstruction::SetMagField(G4double value)
{
	//apply a global uniform magnetic field along Z axis
	G4FieldManager* fieldMgr
		= G4TransportationManager::GetTransportationManager()->GetFieldManager();

	if(magField) delete magField;		//delete the existing magn field

	if(value!=0.){			// create a new one if non nul
		fieldValue = value;
		magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
		fieldMgr->SetDetectorField(magField);
		fieldMgr->CreateChordFinder(magField);
	} else {
		magField = 0;
		fieldMgr->SetDetectorField(magField);
	}
}

#include "G4RunManager.hh"

void rockDetectorConstruction::UpdateGeometry()
{
	G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

