#include <iostream>
#include <fstream>
#include <string>

//#define F_DEBUG 1

using namespace std;

#define MAX_TRK 100000

void FillTree(TString filename = "./rock.out")
{
  
  TFile *f=new TFile("tree.root","recreate");

  // for each event, you want up to MAX_TRK candidates
  //
  
  Int_t		n;
  Int_t		line;
  Int_t		sCopyNO;
  Int_t		sTrack;
  Int_t		scode;
  Double_t	sE;
  Double_t	sX;
  Double_t	sY;
  Double_t	sZ;
  Double_t	sT;
  Double_t	sEdep;

  vector<Int_t> CopyNO;
  vector<Int_t> Track;
  vector<Int_t> code;
  vector<Double_t> E;
  vector<Double_t> X;
  vector<Double_t> Y;
  vector<Double_t> Z;
  vector<Double_t> T;
  vector<Double_t> Edep;


  TTree* tree= new TTree("tree","An example of a tree");

  tree->Branch("n",&n,"n/I");
  tree->Branch("CopyNO",&CopyNO);
  tree->Branch("Track",&Track);
  tree->Branch("code",&code);
  tree->Branch("E",&E);
  tree->Branch("X",&X);
  tree->Branch("Y",&Y);
  tree->Branch("Z",&Z);
  tree->Branch("T",&T);
  tree->Branch("Edep",&Edep);

  //--- open file -----
  std::ifstream inFile;
  inFile.open(filename);
  
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
		inFile >> sCopyNO >> sTrack >> scode >> sE >> sX >> sY >> sZ >> sT >> sEdep;
		CopyNO.push_back(sCopyNO);
		Track.push_back(sTrack);
		code.push_back(scode);
		E.push_back(sE);
		X.push_back(sX);
		Y.push_back(sY);
		Z.push_back(sZ);
		T.push_back(sT);
		Edep.push_back(sEdep);
		
    }
    tree->Fill();

  }
  tree->Write();
  f->Close();
  delete f;
}
