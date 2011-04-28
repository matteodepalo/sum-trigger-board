// -----------------------
//  Sum Trigger Board Project
//  analyze overall gain of the board
//
//  Input:
//   - data file
//  Output:
//   -  plots regarding the gain of the board
//
//   Structure:
//   1. read data file
//   2. fill trees with gain data
//   3. data analysis
//
//
// m.depalo jul.2010
//

void AnalyzeGain(const char *inFile = "Data.root") {
	
	//try to access data file and in case of failure return
	if(gSystem->AccessPathName(inFile,kFileExists)) {
		cout << "Error: file " << inFile << " does not exsist. Run .x DataParse.C to create it" << endl;
		return;
	}

	TFile *f = TFile::Open(inFile);
	TFolder *dataSet;
	
	TString dataFolderS = "SumTriggerBoardData";
	dataFolderS.Append(";1");

	dataSet = (TFolder*)f->Get(dataFolderS);
	
	cout << dataSet << endl;

	cout << dataSet->GetName() << endl;

	TNtuple *nx;
	TNtuple *ny;
	TNtuple *nex;
	TNtuple *ney;

	Int_t graphPoints;

	Float_t px,py,pex,pey;

	vector<float> vx,vy,vex,vey;
	
	Int_t nProbe = 500;
	Int_t nScope = 150;
	
	// gain for all channels
	
	TString path = "Overall gain/All channels/";
	
	// fetch every TNtuple containing data and fill graphs
	
	vector<float> vChannel;
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "Channel");
	cout << nx << endl;
	nx->SetBranchAddress("values",&px);
	
	graphPoints = nx->GetEntries();
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vChannel.push_back(px);
	}
	
	nx->ResetBranchAddresses();
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
	}
	
	vector<float> vGain, vGainErrors;
	for(Int_t i = 0; i < graphPoints; i++) {
		vGain.push_back(vx.at(i) / vy.at(i));
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		cout << "vGain channel " << vChannel.at(i) << " = " << vGain.at(i) << endl;
		vGainErrors.push_back(vGain.at(i)*TMath::Sqrt(TMath::Power(vex.at(i)/vx.at(i),2) + TMath::Power(vey.at(i)/vy.at(i),2)));
		cout << "vGainErrors channel " << i + 1 << " = " << vGainErrors.at(i) << endl;
	}

	TGraphErrors *gGainAllChannels = new TGraphErrors(graphPoints,&vChannel.at(0),&vGain.at(0),0,&vGainErrors.at(0)); 
	//gGainAllChannels->Fit("pol0");
	gGainAllChannels->GetXaxis()->SetRangeUser(-2,10);

	gGainAllChannels->SetTitle("Gain in function of the channel");

	gGainAllChannels->SetMarkerStyle(20);
	gGainAllChannels->SetMarkerSize(1);
	gGainAllChannels->GetXaxis()->SetTitle("Channel");
	gGainAllChannels->GetYaxis()->SetTitle("Gain");

	TCanvas *cGainAllChannels = new TCanvas("cGainAllChannels","Gain vs Channel",800,600);
	gGainAllChannels->Draw("APE");
	
	// Channel 5 gain, one width
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	path = "Overall gain/Channel 5/One width/";
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
	}
	
	vector<float> vGain, vGainErrors;
	for(Int_t i = 0; i < graphPoints; i++) {
		vGain.push_back(vx.at(i) / vy.at(i));
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		cout << "vGain input amplitude " << vx.at(i) << " = " << vGain.at(i) << endl;
		vGainErrors.push_back(vGain.at(i)*TMath::Sqrt(TMath::Power(vex.at(i)/vx.at(i),2) + TMath::Power(vey.at(i)/vy.at(i),2)));
		cout << "vGainErrors input amplitude " << vx.at(i) << " = " << vGainErrors.at(i) << endl;
	}

	TGraphErrors *gGainCh51Gs = new TGraphErrors(graphPoints,&vx.at(0),&vGain.at(0),&vex.at(0),&vGainErrors.at(0)); 
	//gGainCh51Gs->Fit("pol0");
	gGainCh51Gs->GetXaxis()->SetRangeUser(-2,10);

	gGainCh51Gs->SetTitle("Channel 5 gain in function of the input amplitude");

	gGainCh51Gs->SetMarkerStyle(20);
	gGainCh51Gs->SetMarkerSize(1);
	gGainCh51Gs->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gGainCh51Gs->GetYaxis()->SetTitle("Gain");

	TCanvas *cGainCh51Gs = new TCanvas("cGainCh51Gs","Gain vs Input amplitude",800,600);
	gGainCh51Gs->Draw("APE");
	
/*	TH1F *hGainCh51Gs = new TH1F("hGainCh51Gs","Distribution of the gain for channel 5",graphPoints,0,0);
	hGainCh51Gs->SetBit(TH1::kCanRebin);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		hGainCh51Gs->Fill(vGain.at(i));
	}
	
	TCanvas *chGainCh51Gs = new TCanvas("chGainCh51Gs","Distribution of the gain for channel 5",800,600);
	hGainCh51Gs->Draw(); 
	hGainCh51Gs->Fit("gaus"); */
	
	// Channel 5 gain, one amplitude
	
	path = "Overall gain/Channel 5/One amplitude/";
	
	vector<float> vFWHM, vFWHM_errors;

	nx = (TNtuple*)dataSet->FindObjectAny(path + "Input_FWHM");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "Input_FWHM_errors");
	cout << nx << endl;
	nx->SetBranchAddress("values",&px);
	nex->SetBranchAddress("values",&pex);

	graphPoints = nx->GetEntries();

	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vFWHM.push_back(px);
		nex->GetEntry(i); vFWHM_errors.push_back(pex);
	}

	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);

	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
	}

	vector<float> vGain, vGainErrors;
	for(Int_t i = 0; i < graphPoints; i++) {
		vGain.push_back(vx.at(i) / vy.at(i));
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		cout << "vGain input width " << vFWHM.at(i) << " = " << vGain.at(i) << endl;
		vGainErrors.push_back(vGain.at(i)*TMath::Sqrt(TMath::Power(vex.at(i)/vx.at(i),2) + TMath::Power(vey.at(i)/vy.at(i),2)));
		cout << "vGainErrors input width " << vFWHM.at(i) << " = " << vGainErrors.at(i) << endl;
	}

	TGraphErrors *gGainCh5OneAmpl = new TGraphErrors(graphPoints,&vFWHM.at(0),&vGain.at(0),&vFWHM_errors.at(0),&vGainErrors.at(0)); 
	//gGainCh5OneAmpl->Fit("pol0");
	gGainCh5OneAmpl->GetXaxis()->SetRangeUser(-2,10);

	gGainCh5OneAmpl->SetTitle("Channel 5 gain in function of the input signal FWHM");

	gGainCh5OneAmpl->SetMarkerStyle(20);
	gGainCh5OneAmpl->SetMarkerSize(1);
	gGainCh5OneAmpl->GetXaxis()->SetTitle("Input signal FWHM (ns)");
	gGainCh5OneAmpl->GetYaxis()->SetTitle("Gain");

	TCanvas *cGainCh5OneAmpl = new TCanvas("cGainCh5OneAmpl","Gain vs Input width",800,600);
	gGainCh5OneAmpl->Draw("APE");
	
}