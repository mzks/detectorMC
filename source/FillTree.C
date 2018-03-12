#include <iostream>
#include <fstream>
#include <string>

//#define F_DEBUG 1

using namespace std;

#define MAX_TRK 100000

void FillTree()
{
  
  TFile *f=new TFile("rockTree.root","recreate");

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

  //--- open file -----
  std::ifstream inFile;
  inFile.open("rock.out");
  
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

    inFile >> n;
    for (size_t itrk=0; itrk<n; ++itrk){
      Int_t id;
      inFile >> hitSt[itrk]
	     >> id  
	     >> code[itrk] 
	     >> kinE[itrk] 
	     >> hitX[itrk] 
	     >> hitY[itrk] 
	     >> hitZ[itrk] 
	     >> hitT[itrk];  
      
#ifdef F_DEBUG
      std::cout << "TrackID: " << itrk << std::endl; 
      std::cout << "PDG code: "<< code[itrk] << std::endl;
      std::cout << "enregy: " << kinE[itrk]  << std::endl;
      std::cout << "station: " << hitSt[itrk] <<std::endl;
      std::cout << "position: "
		<< hitX[itrk] << " "
		<< hitY[itrk] << " "
		<< hitZ[itrk] << std::endl;
      std::cout << "time: " << hitT[itrk] <<std::endl;
 #endif
    }
    prockTree->Fill();

  }
  
  prockTree->Write();
  f->Close();
  delete f;
}
