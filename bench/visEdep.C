#include "/Users/mzks/local/atlasstyle/AtlasStyle.C"
#include "/Users/mzks/local/atlasstyle/AtlasLabels.C"
// ------------------------------- //
// 2017.08.01
// Mizukoshi keita
// ------------------------------- //

void visEdep(string filename = "./rockvis.out"){
    SetAtlasStyle();

	ifstream ifs(filename.c_str());
    auto C = new TCanvas();

	int line;
	int copyNO,trackID,particleID;
	double E,X,Y,Z,T,Edep;

	auto hist = new TH1D("hist","hist",100,0,1.0);

	while(ifs >> line){
		double totalE = 0.0;
		for(int i=0;i<line;i++){
			ifs >> copyNO >> trackID >> particleID >> E >> X >> Y >> Z >> T >> Edep;
			totalE += Edep;
		}
		if(totalE > 0.1 )hist->Fill(totalE);
	}
    C->SetLogy();
    hist->SetTitle(";Energy deposit(MeV);Counts/1M neutrons generated");
	hist->Draw();
}
