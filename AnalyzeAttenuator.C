// -----------------------
//  Sum Trigger Board Project
//  analyze the behavior of the attenuators on the board
//
//  Input:
//   - data file
//  Output:
//   -  many plots
//
//   Structure:
//   1. read data file
//   2. fill trees with attenuator data
//   3. data analysis
//
//
// m.depalo jul.2010
//


#include <vector.h>


void AnalyzeAttenuator(const char *inFile = "Data.root") {
	
	// channel 5
	
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

	std::vector<float> vx,vy,vex,vey;
	
	Int_t nProbe = 500;
	Int_t nScope = 150;
	
	// attenuator value : 700 mV
	
	TString path = "Attenuator/3 attenuator values/Channel 5/Attenuator 700mV/";
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
	}
	
	TGraphErrors *gAtt700mVCh5 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAtt700mVCh5->SetTitle("Channel 5 | V output in function of V input | Attenuator 700mV");

	gAtt700mVCh5->SetMarkerStyle(20);
	gAtt700mVCh5->SetMarkerSize(0.8);
	gAtt700mVCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gAtt700mVCh5->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	
	TCanvas *cgAtt700mVCh5 = new TCanvas("cgAtt700mVCh5","Channel 5 V output in function of V input | Attenuator 700mV",800,600);
	gAtt700mVCh5->GetYaxis()->SetTitleOffset(1.2);
	cgAtt700mVCh5->SetLeftMargin(0.12);
	gAtt700mVCh5->Draw("APEL");
	
	vector<float> vOutput700mV = vy;
	vector<float> vOutput700mV_err = vey;
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// attenuator value: 1000 mV
	
	path = "Attenuator/3 attenuator values/Channel 5/Attenuator 1000mV/";
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
	}
	
	TGraphErrors *gAtt1000mVCh5 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAtt1000mVCh5->SetTitle("Channel 5 | V output in function of V input | Attenuator 1000mV");

	gAtt1000mVCh5->SetMarkerStyle(21);
	gAtt1000mVCh5->SetMarkerSize(0.8);
	gAtt1000mVCh5->SetLineColor(kBlue);
	gAtt1000mVCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gAtt1000mVCh5->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	
	TCanvas *cgAtt1000mVCh5 = new TCanvas("cgAtt1000mVCh5","Channel 5 V output in function of V input | Attenuator 1000mV",800,600);
	gAtt1000mVCh5->GetYaxis()->SetTitleOffset(1.2);
	cgAtt1000mVCh5->SetLeftMargin(0.12);
	gAtt1000mVCh5->Draw("APEL");
	
	vector<float> vOutput1000mV = vy;
	vector<float> vOutput1000mV_err = vey;
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// attenuator value: 2000 mV
	
	path = "Attenuator/3 attenuator values/Channel 5/Attenuator 2000mV/";
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
	}
	
	TGraphErrors *gAtt2000mVCh5 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAtt2000mVCh5->SetTitle("Channel 5 | V output in function of V input | Attenuator 2000mV");

	gAtt2000mVCh5->SetMarkerStyle(22);
	gAtt2000mVCh5->SetMarkerSize(0.8);
	gAtt2000mVCh5->SetLineColor(kRed);
	gAtt2000mVCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gAtt2000mVCh5->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	
	TCanvas *cgAtt2000mVCh5 = new TCanvas("cgAtt2000mVCh5","Channel 5 V output in function of V input | Attenuator 2000mV",800,600);
	gAtt2000mVCh5->GetYaxis()->SetTitleOffset(1.2);
	cgAtt2000mVCh5->SetLeftMargin(0.12);
	gAtt2000mVCh5->Draw("APEL");
	
	vector<float> vOutput2000mV = vy;
	vector<float> vOutput2000mV_err = vey;
	
	// ratio graph. 700mV data set is taken as a reference and i divide the other two set of values by this reference
	
	TGraphErrors *gRatio1000mVCh5 = new TGraphErrors(graphPoints);
	
	gRatio1000mVCh5->SetTitle("1000 mV / 700 mV values");

	gRatio1000mVCh5->SetMarkerStyle(21);
	gRatio1000mVCh5->SetMarkerSize(0.8);
	gRatio1000mVCh5->SetLineColor(kBlue);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		gRatio1000mVCh5->SetPoint(i,vx.at(i),vOutput1000mV.at(i) / vOutput700mV.at(i));
		gRatio1000mVCh5->SetPointError(i,vex.at(i),
		(vOutput1000mV.at(i) / vOutput700mV.at(i))*TMath::Sqrt(TMath::Power(vOutput1000mV_err.at(i)/vOutput1000mV.at(i),2) + 
		TMath::Power(vOutput700mV_err.at(i)/vOutput700mV.at(i),2)));
	}
	
	gRatio1000mVCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gRatio1000mVCh5->GetYaxis()->SetTitle("Ratio");
	
	TGraphErrors *gRatio2000mVCh5 = new TGraphErrors(graphPoints);
	
	gRatio2000mVCh5->SetTitle("2000 mV / 700 mV values");

	gRatio2000mVCh5->SetMarkerStyle(22);
	gRatio2000mVCh5->SetMarkerSize(0.8);
	gRatio2000mVCh5->SetLineColor(kRed);
	
	for(Int_t i = 0; i< graphPoints; i++) {
		gRatio2000mVCh5->SetPoint(i,vx.at(i),vOutput2000mV.at(i) / vOutput700mV.at(i));
		gRatio2000mVCh5->SetPointError(i,vex.at(i),
		(vOutput2000mV.at(i) / vOutput700mV.at(i))*TMath::Sqrt(TMath::Power(vOutput2000mV_err.at(i)/vOutput2000mV.at(i),2) + 
		TMath::Power(vOutput700mV_err.at(i)/vOutput700mV.at(i),2)));
	}
	
	gRatio2000mVCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gRatio2000mVCh5->GetYaxis()->SetTitle("Ratio");
	
	TCanvas *cgRatio1000mVCh5 = new TCanvas("gRatio1000mVCh5", "Ratio 1000 mV / 700 mV",800,600);
	gRatio1000mVCh5->Draw("APEL");
	
	TCanvas *cgRatio2000mVCh5 = new TCanvas("gRatio2000mVCh5", "Ratio 2000 mV / 700 mV",800,600);
	gRatio2000mVCh5->Draw("APEL");
	
	// collection of ratio graphs
	
	TMultiGraph *mgRatioCh5 = new TMultiGraph();
	mgRatioCh5->SetTitle("Collection of ratio graphs");
	
	mgRatioCh5->Add(gRatio1000mVCh5);
	mgRatioCh5->Add(gRatio2000mVCh5);
	
	TCanvas *cmgRatioCh5 = new TCanvas("cmgRatioCh5","Collection of ratio graphs",800,600);
	mgRatioCh5->Draw("APEL");
	
	legend = new TLegend(0.6,0.45,0.87,0.60);
	legend->AddEntry(gRatio1000mVCh5, "1000 / 700 mV", "lp");
	legend->AddEntry(gRatio2000mVCh5, "2000 / 700 mV", "lp");
	legend->SetTextSize(0.028);
	legend->SetMargin(0.5);
	legend->Draw();
	
	cmgRatioCh5->Update();
	mgRatioCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	mgRatioCh5->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	cmgRatioCh5->Modified();
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// collection of graphs for channel 5
	
	TMultiGraph *mgAttCh5 = new TMultiGraph();
	mgAttCh5->SetTitle("Collection of graphs for channel 5 | 700,1000,2000 mV attenuator values");
	
	mgAttCh5->Add(gAtt700mVCh5);
	mgAttCh5->Add(gAtt1000mVCh5);
	mgAttCh5->Add(gAtt2000mVCh5);
	
	TCanvas *cmgAttCh5 = new TCanvas("cmgAttCh5","Collection of graphs for channel 5 | 700,1000,2000 mV attenuator values",800,600);
	cmgAttCh5->SetLogy();
	mgAttCh5->Draw("APEL");
	
	legend = new TLegend(0.65,0.14,0.88,0.35,"Attenuator values");
	legend->AddEntry(gAtt700mVCh5, "700mV", "lp");
	legend->AddEntry(gAtt1000mVCh5, "1000mV", "lp");
	legend->AddEntry(gAtt2000mVCh5, "2000mV","lp");
	legend->SetMargin(0.5);
	legend->SetTextSize(0.03);
	legend->Draw();
	
	cmgAttCh5->Update();
	mgAttCh5->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	mgAttCh5->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	cmgAttCh5->Modified();
	
	// channel 6
	
	// attenuator value: 1000 mV
	
	path = "Attenuator/3 attenuator values/Channel 6/Attenuator 1000mV/";
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
	}
	
	TGraphErrors *gAtt1000mVCh6 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAtt1000mVCh6->SetTitle("Channel 6 | V output in function of V input | Attenuator 1000mV");

	gAtt1000mVCh6->SetMarkerStyle(21);
	gAtt1000mVCh6->SetMarkerSize(0.8);
	gAtt1000mVCh6->SetLineColor(kRed);
	gAtt1000mVCh6->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	gAtt1000mVCh6->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	
	TCanvas *cgAtt1000mVCh6 = new TCanvas("cgAtt1000mVCh6","Channel 6 V output in function of V input | Attenuator 1000mV",800,600);
	gAtt1000mVCh6->GetYaxis()->SetTitleOffset(1.2);
	cgAtt1000mVCh6->SetLeftMargin(0.12);
	gAtt1000mVCh6->Draw("APEL");
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// channel 5 and 6 attenuator value 1000 mV
	
	TMultiGraph *mgAtt1000mV = new TMultiGraph();
	mgAtt1000mV->SetTitle("Collection of graphs | Channel 5 and 6 | Attenuator value 1000mV");
	
	mgAtt1000mV->Add(gAtt1000mVCh5);
	mgAtt1000mV->Add(gAtt1000mVCh6);
	
	TCanvas *cmgAtt1000mV = new TCanvas("cmgAtt1000mV","Collection of graphs | Channel 5 and 6 | Attenuator value 1000mV",800,600);
	mgAtt1000mV->Draw("APEL");
	
	legend = new TLegend(0.70,0.15,0.86,0.37,"Channel");
	legend->AddEntry(gAtt1000mVCh5, "5", "lp");
	legend->AddEntry(gAtt1000mVCh6, "6","lp");
	legend->SetMargin(0.5);
	legend->SetTextSize(0.03);
	legend->Draw();
	
	cmgAtt1000mV->Update();
	mgAtt1000mV->GetXaxis()->SetTitle("Input signal amplitude (mV)");
	mgAtt1000mV->GetYaxis()->SetTitle("Output signal amplitude (mV)");
	cmgAtt1000mV->Modified();
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// channel 5, fixed amplitude 953mV, many attenuator values
	
	Float_t amplitude, amplitude_err;
	
	path = "Attenuator/Several attenuator values/Channel 5/One width/Amplitude 953mV/";
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	
	nx->SetBranchAddress("values",&px);
	nex->SetBranchAddress("values",&pex);
	
	nx->GetEntry(0);
	amplitude = px;
	nex->GetEntry(0);
	amplitude_err = pex;
	amplitude_err /= TMath::Sqrt(nProbe);
	
	nx->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	Float_t vOutput;
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		
		vOutput = vy.at(i);
		vy.at(i) /= amplitude;
		vey.at(i) = vy.at(i)*TMath::Sqrt(TMath::Power(amplitude_err/amplitude,2) + TMath::Power(vey.at(i)/vOutput,2));
	}
	
	TGraphErrors *gAmp953mVCh5 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAmp953mVCh5->SetTitle("Channel 5 | V output / V input in function of Attenuator value | Amplitude 953mV | 1.873 ns");

	gAmp953mVCh5->SetMarkerStyle(20);
	gAmp953mVCh5->SetMarkerSize(0.8);
	gAmp953mVCh5->GetXaxis()->SetTitle("Attenuator value (mV)");
	gAmp953mVCh5->GetYaxis()->SetTitle("Output amplitude / Input amplitude");
	
	TCanvas *cgAmp953mVCh5 = new TCanvas("cgAmp953mVCh5","Channel 5 | V output / V input in function of Attenuator value | Amplitude 953mV | 1.873 ns",800,600);
	gAmp953mVCh5->GetYaxis()->SetTitleOffset(1.2);
	cgAmp953mVCh5->SetLeftMargin(0.12);
	gAmp953mVCh5->Draw("APEL");
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// channel 5, fixed amplitude 1615mV, many attenuator values
	
	path = "Attenuator/Several attenuator values/Channel 5/One width/Amplitude 1615mV/";
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "V_input");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "V_input_errors");
	
	nx->SetBranchAddress("values",&px);
	nex->SetBranchAddress("values",&pex);
	
	nx->GetEntry(0);
	amplitude = px;
	nex->GetEntry(0);
	amplitude_err = pex;
	amplitude_err /= TMath::Sqrt(nProbe);
	
	nx->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		
		vOutput = vy.at(i);
		vy.at(i) /= amplitude;
		vey.at(i) = vy.at(i)*TMath::Sqrt(TMath::Power(amplitude_err/amplitude,2) + TMath::Power(vey.at(i)/vOutput,2));
	}
	
	TGraphErrors *gAmp1615mVCh5 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAmp1615mVCh5->SetTitle("Channel 5 | V output / V input in function of Attenuator value | Amplitude 1615mV");

	gAmp1615mVCh5->SetMarkerStyle(21);
	gAmp1615mVCh5->SetMarkerSize(0.8);
	gAmp1615mVCh5->SetLineColor(kRed);
	gAmp1615mVCh5->GetXaxis()->SetTitle("Attenuator value (mV)");
	gAmp1615mVCh5->GetYaxis()->SetTitle("Output amplitude / Input amplitude");
	
	TCanvas *cgAmp1615mVCh5 = new TCanvas("cgAmp1615mVCh5","Channel 5 | V output / V input in function of Attenuator value | Amplitude 1615mV",800,600);
	gAmp1615mVCh5->GetYaxis()->SetTitleOffset(1.2);
	cgAmp1615mVCh5->SetLeftMargin(0.12);
	gAmp1615mVCh5->Draw("APEL");
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// collection of graphs for different input amplitudes
	
	TMultiGraph *mg2AmpCh5 = new TMultiGraph();
	
	mg2AmpCh5->SetTitle("Collection of graphs | Channel 5 | Amplitude 953 and 1615 mV | Width 1.873 ns");
	
	mg2AmpCh5->Add(gAmp953mVCh5);
	mg2AmpCh5->Add(gAmp1615mVCh5);

	TCanvas *cmg2AmpCh5 = new TCanvas("cmg2AmpCh5","Collection of graphs | Channel 5 | Amplitude 953mV and 1615 | Width 1.873",800,600);
	cmg2AmpCh5->SetLeftMargin(0.12);
	mg2AmpCh5->Draw("APEL");
	
	legend = new TLegend(0.66,0.15,0.87,0.42,"Input amplitude");
	legend->AddEntry(gAmp953mVCh5, "953 mV", "lp");
	legend->AddEntry(gAmp1615mVCh5, "1615 mV","lp");
	legend->SetMargin(0.5);
	legend->SetTextSize(0.03);
	legend->Draw();
	
	cmg2AmpCh5->Update();
	mg2AmpCh5->GetYaxis()->SetTitleOffset(1.2);
	mg2AmpCh5->GetXaxis()->SetTitle("Attenuator value (mV)");
	mg2AmpCh5->GetYaxis()->SetTitle("Output amplitude / Input amplitude");
	cmg2AmpCh5->Modified();
	
	// channel 5, fixed width 2.533 ns, fixed amplitude 953, many attenuator values
	
	amplitude = 953.2;
	amplitude_err = 9;
	
	path = "Attenuator/Several attenuator values/Channel 5/One amplitude/Width value 2/";
	
	// fetch every TNtuple containing data and fill graphs
	
	nx = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value");
	ny = (TNtuple*)dataSet->FindObjectAny(path + "V_output");
	nex = (TNtuple*)dataSet->FindObjectAny(path + "Attenuator_value_errors");
	ney = (TNtuple*)dataSet->FindObjectAny(path + "V_output_errors");
	
	graphPoints = nx->GetEntries();

	nx->SetBranchAddress("values",&px);
	ny->SetBranchAddress("values",&py);
	nex->SetBranchAddress("values",&pex);
	ney->SetBranchAddress("values",&pey);
	
	for(Int_t i = 0; i < graphPoints; i++) {
		nx->GetEntry(i); vx.push_back(px);
		ny->GetEntry(i); vy.push_back(py);
		nex->GetEntry(i); vex.push_back(pex);
		ney->GetEntry(i); vey.push_back(pey);
		
		vex.at(i) /= TMath::Sqrt(nProbe);
		vey.at(i) /= TMath::Sqrt(nScope);
		
		vOutput = vy.at(i);
		vy.at(i) /= amplitude;
		vey.at(i) = vy.at(i)*TMath::Sqrt(TMath::Power(amplitude_err/amplitude,2) + TMath::Power(vey.at(i)/vOutput,2));
	}
	
	TGraphErrors *gAmp953mVCh5W2 = new TGraphErrors(graphPoints,&vx.at(0),&vy.at(0),&vex.at(0),&vey.at(0));
	
	gAmp953mVCh5W2->SetTitle("Channel 5 | V output / V input in function of Attenuator value | Amplitude 953mV | 2.533 ns");

	gAmp953mVCh5W2->SetMarkerStyle(21);
	gAmp953mVCh5W2->SetMarkerSize(0.8);
	gAmp953mVCh5W2->SetLineColor(kRed);
	gAmp953mVCh5W2->GetXaxis()->SetTitle("Attenuator value (mV)");
	gAmp953mVCh5W2->GetYaxis()->SetTitle("Output amplitude / Input amplitude");
	
	TCanvas *cgAmp953mVCh5W2 = new TCanvas("cgAmp953mVCh5W2","Channel 5 | V output / V input in function of Attenuator value | Amplitude 953mV | 2.533 ns",800,600);
	gAmp953mVCh5W2->GetYaxis()->SetTitleOffset(1.2);
	cgAmp953mVCh5W2->SetLeftMargin(0.12);
	gAmp953mVCh5W2->Draw("APEL");
	
	nx->ResetBranchAddresses();
	ny->ResetBranchAddresses();
	nex->ResetBranchAddresses();
	ney->ResetBranchAddresses();
	vx.clear(); vy.clear(); vey.clear(); vex.clear();
	
	// collection of graphs for different widths, many attenuator values
	
	TMultiGraph *mgCh5Amp953 = new TMultiGraph();
	mgCh5Amp953->SetTitle("Collection of graphs | Channel 5 | Amplitude 953mV | Widths 1.873 and 2.533 ns");
	
	mgCh5Amp953->Add(gAmp953mVCh5W2);
	mgCh5Amp953->Add(gAmp953mVCh5);

	TCanvas *cmgCh5Amp953 = new TCanvas("cmgCh5Amp953","Collection of graphs | Channel 5 | Amplitude 953mV | Widths 1.873 and 2.533 ns",800,600);
	cmgCh5Amp953->SetLeftMargin(0.12);
	mgCh5Amp953->Draw("APEL");
	
	legend = new TLegend(0.66,0.15,0.87,0.42,"Input FWHM");
	legend->AddEntry(gAmp953mVCh5, "1.876 ns", "lp");
	legend->AddEntry(gAmp953mVCh5W2, "2.533 ns","lp");
	legend->SetMargin(0.5);
	legend->SetTextSize(0.03);
	legend->Draw();
	
	cmgCh5Amp953->Update();
	mgCh5Amp953->GetYaxis()->SetTitleOffset(1.2);
	mgCh5Amp953->GetXaxis()->SetTitle("Attenuator value (mV)");
	mgCh5Amp953->GetYaxis()->SetTitle("Output amplitude / Input amplitude");
	cmgCh5Amp953->Modified();
}