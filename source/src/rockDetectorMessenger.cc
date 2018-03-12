#include "rockDetectorMessenger.hh"
#include "rockDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"


rockDetectorMessenger::rockDetectorMessenger(
                                           rockDetectorConstruction* rockDet)
:rockDetector(rockDet)
{ 
  rockDir = new G4UIdirectory("/rock/");
  rockDir->SetGuidance("UI commands of this example");
  detDir = new G4UIdirectory("/rock/det/");
  detDir->SetGuidance("UI commands for detector setup");
  
  MaterialCmd = new G4UIcmdWithAString("/rock/det/setMaterial",this);
  MaterialCmd->SetGuidance("Select Material of the sensor");
  MaterialCmd->SetParameterName("choice",false);
  MaterialCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  ThicknessCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setThickness",this);
  ThicknessCmd->SetGuidance("Set Thickness of the sensor");
  ThicknessCmd->SetParameterName("Size",false);
  ThicknessCmd->SetRange("Size>=0.");
  ThicknessCmd->SetUnitCategory("Length");
  ThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  SizeYZCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setSize",this);
  SizeYZCmd->SetGuidance("Set tranverse size of the sensor");
  SizeYZCmd->SetParameterName("Size",false);
  SizeYZCmd->SetRange("Size>0.");
  SizeYZCmd->SetUnitCategory("Length");    
  SizeYZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ArmCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setArm",this);
  ArmCmd->SetGuidance("Set Lever Arm of the sensor");
  ArmCmd->SetParameterName("Arm",false);
  ArmCmd->SetRange("Arm>0.");
  ArmCmd->SetUnitCategory("Length");    
  ArmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setField",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false);
  MagFieldCmd->SetUnitCategory("Magnetic flux density");
  MagFieldCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  

  MaxStepCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setMaxStep",this);
  MaxStepCmd->SetGuidance("Set MaxStep ");
  MaxStepCmd->SetParameterName("MaxStep",false);
  MaxStepCmd->SetRange("MaxStep>0.");
  MaxStepCmd->SetUnitCategory("Length");    
  MaxStepCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  PESizeCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setPESize",this);
  PESizeCmd->SetGuidance("Set PE size");
  PESizeCmd->SetParameterName("PESize",false);
  PESizeCmd->SetRange("PESize>0.");
  PESizeCmd->SetUnitCategory("Length");    
  PESizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BoronSizeCmd = new G4UIcmdWithADoubleAndUnit("/rock/det/setBoronSize",this);
  BoronSizeCmd->SetGuidance("Set Boron size");
  BoronSizeCmd->SetParameterName("BoronSize",false);
  BoronSizeCmd->SetRange("BoronSize>0.");
  BoronSizeCmd->SetUnitCategory("Length");    
  BoronSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}


rockDetectorMessenger::~rockDetectorMessenger()
{
  delete MaterialCmd;
  delete ThicknessCmd;
  delete SizeYZCmd;  
  delete ArmCmd;  
  delete MagFieldCmd;
  delete MaxStepCmd;  
  delete rockDir;  
  delete BoronSizeCmd;
  delete PESizeCmd;
}


void rockDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == MaterialCmd ){
    rockDetector->SetSensorMaterial(newValue);

  } else if( command == ThicknessCmd ){
    rockDetector->SetSensorThickness(
		   ThicknessCmd->GetNewDoubleValue(newValue)
		  );
   
  } else if( command == SizeYZCmd ){
    rockDetector->SetSensorSize(SizeYZCmd->GetNewDoubleValue(newValue));
    

  } else if( command == ArmCmd ){
    rockDetector->SetSensorLeverArm(ArmCmd->GetNewDoubleValue(newValue));
    

  } else if( command == MaxStepCmd ){
    rockDetector->SetMaxStep(MaxStepCmd->GetNewDoubleValue(newValue));
    

  } else if( command == MagFieldCmd ){
    rockDetector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));

  } else if( command == PESizeCmd ){
    rockDetector->SetPESize(PESizeCmd->GetNewDoubleValue(newValue));

  } else if( command == BoronSizeCmd ){
    rockDetector->SetBoronSize(BoronSizeCmd->GetNewDoubleValue(newValue));

  }
}


G4String rockDetectorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  
  if( command==MaterialCmd ){
    cv =  rockDetector->GetSensorMaterial()->GetName();

  } else if( command==ThicknessCmd ){
    cv =  ThicknessCmd->ConvertToString( rockDetector->GetSensorThickness(),"mm");

  } else if( command==SizeYZCmd ){
    cv =  SizeYZCmd->ConvertToString( rockDetector->GetSensorSize(),"mm");

  } else if( command==ArmCmd ){
    cv =  ArmCmd->ConvertToString( rockDetector->GetSensorLeverArm(),"cm");

  } else if( command==MaxStepCmd ){
    cv =  MaxStepCmd->ConvertToString( rockDetector->GetMaxStep(),"mm");

  } else if( command==MagFieldCmd ){
    cv =  MagFieldCmd->ConvertToString( rockDetector->GetFieldValue(),"tesla");

  } else if( command==PESizeCmd ){
    cv =  PESizeCmd->ConvertToString( rockDetector->GetPESize(),"mm");

  } else if( command==BoronSizeCmd ){
    cv =  BoronSizeCmd->ConvertToString( rockDetector->GetBoronSize(),"mm");

  }
  
  return cv;
}

