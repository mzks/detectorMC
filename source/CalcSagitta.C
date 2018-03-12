#include <iostream>
#include <fstream>
#include <string>

//#define F_DEBUG 1

using namespace std;

#define MAX_TRK 100000

void CalcSagitta()
{
 // Open file
  TFile *pfile=new TFile("rockTree.root");

  // Get Tree 
  TTree* prockTree = (TTree*)pfile->Get("rockTree");

  // for each event 
  Int_t    n;
  Int_t    code[MAX_TRK];
  Double_t kinE[MAX_TRK];
  Int_t    hitSt[MAX_TRK];
  Float_t  hitX[MAX_TRK];
  Float_t  hitY[MAX_TRK];
  Float_t  hitZ[MAX_TRK];
  Float_t  hitT[MAX_TRK];

  prockTree->SetBranchAddress("n",&n);
  prockTree->SetBranchAddress("code",&code);
  prockTree->SetBranchAddress("E",&kinE);
  
  prockTree->SetBranchAddress("station",&hitSt);
  prockTree->SetBranchAddress("X",&hitX);
  prockTree->SetBranchAddress("Y",&hitY);
  prockTree->SetBranchAddress("Z",&hitZ);
  prockTree->SetBranchAddress("T",&hitT);

  Int_t  total_n_evt = prockTree->GetEntries();
  std::cout << "Total Number Of Events =" << total_n_evt <<endl;

  //define Histogram
  TH1F *hsy  = new TH1F("Sy","Sagitta in X-Y plane", 1000, 55.,65.);
  TH1F *hsz  = new TH1F("Sz","Sagitta in X-Z plane", 250, -2.5.,2.5.);
  TH2F *hsyz  = new TH2F("Syz","Saggita Y vs.Z ",
  		      200, 57.5.,62.5.,  100, -1. ,1.); 
  TH1F *htof  = new TH1F("Tof","TOF between station 0 and 2 ", 500, 12.5.,14.5.);

  Int_t n_evt;
  for (n_evt=0; n_evt<total_n_evt; ++n_evt){
    prockTree->GetEntry(n_evt);

#ifdef F_DEBUG
    std::cout << "Event#: " << n_evt << std::endl; 
#endif

    Int_t itrk;

    Double_t x[3],y[3],z[3],t[3];
    Int_t  nhit=0;

    for(itrk=0; itrk<n; ++itrk){ 
      // neglect other than mu+
      if (code[itrk]!=-13)  continue;
       
      x[hitSt[itrk]] = hitX[itrk];
      y[hitSt[itrk]] = hitY[itrk];
      z[hitSt[itrk]] = hitZ[itrk];
      t[hitSt[itrk]] = hitT[itrk];
      nhit +=1;

#ifdef F_DEBUG
      std::cout << "TrackID: " << itrk << std::endl; 
      std::cout << "Station: "<< hitSt[itrk] << "  "
      std::cout << "enregy: " << kinE[itrk]  << std::endl;
      std::cout << "Posotion: "
		<< hitX[itrk] << " "
		<< hitY[itrk] << " "
		<< hitZ[itrk] << std::endl;
#endif
    }

    if (nhit ==3){
      Double_t sy, sz;
      Double_t tof;
      sy = y[1] - ((x[1]-x[0])/(x[2]-x[0])*(y[2]-y[0]) + y[0]);
      sz = z[1] - ((x[1]-x[0])/(x[2]-x[0])*(z[2]-z[0]) + z[0]);
      tof = t[2]-t[0];
      hsy->Fill(sy);
      hsz->Fill(sz);
      hsyz->Fill(sy,sz);
      htof->Fill(tof);
    }
    
  }

  TCanvas *c1 = new TCanvas("c1","Sagitta",10,10,400,800);
  c1->Divide(1,2);
  c1->cd(1);
  hsy->Draw();  
  hsy->Fit("gaus");  
  c1->cd(2);
  hsz->Draw();  
  hsz->Fit("gaus");  

  TCanvas *c2 = new TCanvas("c2","Correlation",10,10,400,600);
  hsyz->Draw();  

  TCanvas *c3 = new TCanvas("c3","TOF",10,10,400,600);
  htof->Draw();  
  htof->Fit("gaus");  

}
