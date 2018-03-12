// ------------------------------- //
// calcTotalEdep.C
// Mizukoshi keita
// 2017.06.01
// ------------------------------- //

void calcTotalEdep(string filename = "./rock.out"){
	//ifstream ifs("./rock.out");
	//ifstream ifs("B1P0_25eV1M.out");
	ifstream ifs(filename.c_str());

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
	hist->Draw();
}
