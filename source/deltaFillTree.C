#include <iostream>
#include <fstream>
#include <string>

#include "TMath.h"


//#define F_DEBUG 1

using namespace std;

#define MAX_TRK 100000

static Double_t Sigma_x[3]={0., 0., 0.}; //0. mm
static Double_t Sigma_t=0.;              //0. ns

//static Double_t Sigma_x[3]={0., 0.3, 0.3}; //0.3 mm
//static Double_t Sigma_t=0.1;              //0.1 ns


void deltaFillTree()
{
  char root_file[32];
  char data_file[32];

  //Int_t run_num;

  //cout << "Enter RUN number ";
  //cin  >> run_num;
 
  //sprintf(root_file,"RUN%d.root",run_num);
  //sprintf(data_file,"run%d.dat",run_num); 

  sprintf(root_file,"rockTreeE.root");
  sprintf(data_file,"rock.out"); 

  //--- open file -----
  std::ifstream inFile;
  inFile.open(data_file);
  cout << data_file <<endl;

  
  TFile *f=new TFile(root_file,"recreate");

  // for each event, you want up to MAX_TRK candidates
  Int_t    n;
  Int_t    hitSt[MAX_TRK];
  Int_t    code[MAX_TRK];
  Double_t kinE[MAX_TRK];
  Float_t  hitX[MAX_TRK];
  Float_t  hitY[MAX_TRK];
  Float_t  hitZ[MAX_TRK];
  Float_t  hitT[MAX_TRK];

  TTree* prockTree= new TTree("rockTree","An example of a tree");
  prockTree->Branch("n",&n,"n/I");
  prockTree->Branch("station",&hitSt,"hitSt[n]/I");
  prockTree->Branch("code",&code,"code[n]/I");
  prockTree->Branch("E",&kinE,"kinE[n]/D");
  prockTree->Branch("X",&hitX,"hitX[n]/F");
  prockTree->Branch("Y",&hitY,"hitY[n]/F");
  prockTree->Branch("Z",&hitZ,"hitZ[n]/F");
  prockTree->Branch("T",&hitT,"hitT[n]/F");

  
  Int_t  n_evt=0;
  while( !inFile.eof() ){
    n_evt += 1;
    if (n_evt%100 ==0) {
      std::cout <<".";
      if (n_evt%2500 ==0) {
	std::cout <<std::endl;
	if (n_evt%10000 ==0) {
	  std::cout << n_evt << std::endl;
	}
      }
    }

    Int_t     n_trk;
    inFile >> n_trk;
    Int_t itrk = 0;    
    for (size_t i=0; i<n_trk; ++i){
      Int_t   id;
      Float_t x[3],tof;
      Float_t station, pcode, energy;
      inFile >> station
	     >> id  
	     >> pcode 
	     >> energy 
	     >> x[0] 
	     >> x[1] 
	     >> x[2] 
	     >> tof;

 	hitSt[itrk] = station;
	//hitSt[itrk] = pcode;
	code[itrk] = -13;
	kinE[itrk] = energy;
	// smare using resolution   
	hitX[itrk]= x[0]+gRandom->Gaus(0.,Sigma_x[0]);
	hitY[itrk]= x[1]+gRandom->Gaus(0.,Sigma_x[1]);
	hitZ[itrk]= x[2]+gRandom->Gaus(0.,Sigma_x[2]);
	hitT[itrk]= tof + gRandom->Gaus(0., Sigma_t);
        

#ifdef F_DEBUG
	std::cout << "TrackID: " << itrk << std::endl; 
	std::cout << "PDG code: "<< code[itrk] << std::endl;
	std::cout << "enregy: " << kinE[itrk]  << std::endl;
	std::cout << "station: " << hitSt[itrk] <<std::endl;
	std::cout << "position: "
		  << hitX[itrk] << " " << x[0]  <<","
		  << hitY[itrk] << " " << x[1]  <<","
		  << hitZ[itrk] << " " << x[2] << std::endl;
	std::cout << "time: " << hitT[itrk] <<std::endl;
 #endif
        
        itrk += 1;

    }
    n = itrk;
    prockTree->Fill();

  }
  
  prockTree->Write();
  f->Close();
  delete f;
}
