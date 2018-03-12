void Plot()
{
  // Open file
  TFile *pfile=new TFile("rockTree.root");

  // Get Tree 
  TTree* pTree = (TTree*)pfile->Get("rockTree");
  
  TCanvas *c0 = new TCanvas("c0","code",10,10,400,400);
  c0->Divide(1,2);
  c0->cd(1);
  pTree->Draw("code","station==0");
  c0->cd(2);
  pTree->Draw("code","station==2");

  TCanvas *c1 = new TCanvas("c1","E/Time mu",10,10,400,600);
  c1->Divide(1,2);
  c1->cd(1);
  pTree->Draw("E","code==-13 && station==2");
  c1->cd(2);
  pTree->Draw("T","code==-13 && station==2");

  TCanvas *c2 = new TCanvas("c2","Position mu",10,10,300,900);
  c2->Divide(1,3);
  c2->cd(1);
  pTree->Draw("Y:Z","code==-13 && station==0");
  c2->cd(2);
  pTree->Draw("Y:Z","code==-13 && station==1");
  c2->cd(3);
  pTree->Draw("Y:Z","code==-13 && station==2");

  TCanvas *c3 = new TCanvas("c3","Position Y mu",10,10,300,900);
  c3->Divide(1,3);
  c3->cd(1);
  pTree->Draw("Y","code==-13 && station==0");
  c3->cd(2);
  pTree->Draw("Y","code==-13 && station==1");
  c3->cd(3);
  pTree->Draw("Y","code==-13 && station==2");

  TCanvas *c4 = new TCanvas("c4","Position all",10,10,300,900);
  c4->Divide(1,3);
  c4->cd(1);
  pTree->Draw("Y:Z","station==0");
  c4->cd(2);
  pTree->Draw("Y:Z","station==1");
  c4->cd(3);
  pTree->Draw("Y:Z","station==2");


}
