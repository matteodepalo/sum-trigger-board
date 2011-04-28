// -----------------------
//  Sum Trigger Board Project
//  analyze the clipping
//
//  Input:
//   - data file
//	 - input wave
//	 - output wave
// 	 - input delay
//	 - input and output x axis cut
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

#include "TBGraphErrors.h"
#include "functions.h"

#include "Math/WrappedTF1.h"
#include "Math/BrentRootFinder.h"

void AnalyzeClipping(TString inputWaveName = "sum trigger input ch5 960mV",
TString outputWaveName = "sum trigger output ch5 - 2V clip - 960mV input", 
Double_t inputDelay = 1.1E-8, Double_t lowerCut = 16E-9, Double_t upperCut = 23E-9,
const char *inFile = "Data.root",const char *WaveformsFile = "Waveforms.root") {
	
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
	
	Int_t nScope = 150; // number of measurements done by the scope evey time
	
	//try to access waveforms file and in case of failure return
	if(gSystem->AccessPathName(WaveformsFile,kFileExists)) {
		cout << "Error: file " << WaveformsFile << " does not exsist. Run .x WaveformsFileMaker.C to create it" << endl;
		return;
	}
	
	TFile *f = TFile::Open(WaveformsFile);
	TList *listOfKeys = f->GetListOfKeys();
	Int_t numberOfKeys = listOfKeys->GetEntries();
	TList *listOfGraphs = new TList();
	
	// if the waveform file name begins with the string "comparator" it goes in this list
	TList *listOfCompWaves = new TList();
	// if the waveform file name begins with the string "sum output" it goes in this list
	TList *listOfAdderWaves = new TList();

	for(Int_t i = 0; i < numberOfKeys; i++) {
		TString *keyName = new TString(listOfKeys->At(i)->GetName());
		TTree *tree = (TTree*)f->Get(keyName->Data());
		Float_t x = 0;
		Float_t y = 0;
		tree->SetBranchAddress("x",&x);
		tree->SetBranchAddress("y",&y);
		Int_t nentries = tree->GetEntries();

		TString *gName = new TString(keyName->Data());
		gName->Append(" graph");
		TGraphErrors *gWave = new TGraphErrors(nentries);
		gWave->SetName(gName->Data());
		gWave->SetTitle(gName->Data());
		gWave->GetXaxis()->SetTitle("Time");
		gWave->GetYaxis()->SetTitle("Voltage");

		for (Int_t j = 0; j < nentries; j++) {
			tree->GetEntry(j);
			gWave->SetPoint(j,x,y);
		}

		listOfGraphs->Add(gWave);
	}
	
	// Global variables
	
	Double_t *xInput, *xOutput, *yInput, *yOutput;
	
	// V input 960 mV
	
	TString path = "Clipping/Output width analysis/Channel 5/V input 960mV/";
	
	TGraphErrors *gClip960mV = TBGraphErrors(dataSet,path,"V clip","Output FWHM",1,nScope);
	
	gClip960mV->SetMarkerStyle(20);
	gClip960mV->SetMarkerSize(0.8);
	gClip960mV->GetXaxis()->SetTitle("V clipping (mV)");
	gClip960mV->GetYaxis()->SetTitle("Output FWHM (ns)");
	
	TCanvas *cClip960mV = new TCanvas("cClip960mV","Output FWHM in function of V clipping",800,600);
	gClip960mV->Draw("APEL");
	
	// Expected output FWHM
	
	TGraphErrors *gInput960mV = listOfGraphs->FindObject("sum trigger input ch5 960mV graph");
	
	Double_t *xClip = gClip960mV->GetX();
	Int_t nClip = gClip960mV->GetN();
	cout << "nClip = " << nClip << endl;
	Long64_t graphPoints = gInput960mV->GetN();
	yInput = gInput960mV->GetY();
	xInput = gInput960mV->GetX();
	
	vector<double> xFirst(nClip);
	vector<double> xLast(nClip);
	Double_t half;
	
	Int_t flag = 0;
	
	vector<double> yConv(graphPoints);
	for(Int_t i = 0; i < graphPoints; i++) {
		yConv[i] = -(yInput[i]);
		yConv[i] *= 1000;
		if(xInput[i] + inputDelay < lowerCut || xInput[i] + inputDelay > upperCut) 
			yConv[i] = 0;
	}
	
	Double_t yInput960mVMax = TMath::MaxElement(graphPoints,&yConv[0]);
	
	for(Int_t i = 0; i < nClip; i++) {
		if(xClip[i] > yInput960mVMax) half = yInput960mVMax;
		else half = xClip[i];
		
		half /=2;
		cout << half << endl;
		
		flag = 0;
		
		for(Int_t j = 0; j < graphPoints - 3; j++) {
			if((yConv[j + 1] - half)*(yConv[j] - half) < 0 && flag == 0) {
				xFirst[i] = xInput[j];
				flag = 1;
				cout << "found first point! " << xFirst[i] << endl;
				continue;
			}
			if((yConv[j + 1] - half)*(yConv[j] - half) < 0 && flag == 1) {
				xLast[i] = xInput[j];
				cout << "found last point! " << xLast[i] << endl;
				break;
			}
		}
	}
	
	vector<double> expectedFWHM960mV(nClip);
	for(Int_t i = 0; i < expectedFWHM960mV.size(); i++) {
		expectedFWHM960mV[i] = xLast[i] - xFirst[i];
		// convert from seconds to nanoseconds
		expectedFWHM960mV[i] *= 10E8;
		cout << "expectedFWHM960mV[" << i << "] = " << expectedFWHM960mV[i] << endl;
	}
	
	// expected FWHM 960 mV graph
	
	TGraphErrors *gExpClip960mV = new TGraphErrors(nClip,xClip,&expectedFWHM960mV[0],0,0);
	gExpClip960mV->SetLineStyle(7);
	gExpClip960mV->SetMarkerStyle(20);
	gExpClip960mV->SetMarkerSize(0.8);
	
	// V input 1.9 V
	
	path = "Clipping/Output width analysis/Channel 5/V input 1.9V/";
	
	TGraphErrors *gClip1Point9V = TBGraphErrors(dataSet,path,"V clip","Output FWHM",1,nScope);
	
	gClip1Point9V->SetMarkerStyle(20);
	gClip1Point9V->SetMarkerSize(0.8);
	gClip1Point9V->SetLineColor(kRed);
	gClip1Point9V->GetXaxis()->SetTitle("V clipping (mV)");
	gClip1Point9V->GetYaxis()->SetTitle("Output FWHM (ns)");
	TCanvas *cClip1Point9V = new TCanvas("cClip1Point9V","Output FWHM in function of V clipping",800,600);
	gClip1Point9V->Draw("APEL");
	
	// Expected output FWHM
	
	TGraphErrors *gInput1Point9V = listOfGraphs->FindObject("sum trigger input ch5 1900mV graph");
	
	xClip = gClip1Point9V->GetX();
	nClip = gClip1Point9V->GetN();
	cout << "nClip = " << nClip << endl;
	graphPoints = gInput1Point9V->GetN();
	yInput = gInput1Point9V->GetY();
	xInput = gInput1Point9V->GetX();
	
	vector<double> xFirst(nClip);
	vector<double> xLast(nClip);
	
	flag = 0;
	
	vector<double> yConv(graphPoints);
	for(Int_t i = 0; i < graphPoints; i++) {
		yConv[i] = -(yInput[i]);
		yConv[i] *= 1000;
		if(xInput[i] + inputDelay < lowerCut || xInput[i] + inputDelay > upperCut) yConv[i] = 0;
	}
	
	Double_t yInput1Point9VMax = TMath::MaxElement(graphPoints,&yConv[0]);
	
	for(Int_t i = 0; i < nClip; i++) {
		if(xClip[i] > yInput1Point9VMax) half = yInput1Point9VMax;
		else half = xClip[i];
		
		half /= 2;
		cout << half << endl;
		
		flag = 0;
		
		for(Int_t j = 0; j < graphPoints - 3; j++) {
			if((yConv[j + 1] - half)*(yConv[j] - half) < 0 && flag == 0) {
				xFirst[i] = xInput[j];
				flag = 1;
				cout << "found first point! " << xFirst[i] << endl;
				continue;
			}
			if((yConv[j + 1] - half)*(yConv[j] - half) < 0 && flag == 1) {
				xLast[i] = xInput[j];
				cout << "found last point! " << xLast[i] << endl;
				break;
			}
		}
	}
	
	vector<double> expectedFWHM1Point9V(nClip);
	for(Int_t i = 0; i < expectedFWHM1Point9V.size(); i++) {
		expectedFWHM1Point9V[i] = xLast[i] - xFirst[i];
		// convert from seconds to nanoseconds
		expectedFWHM1Point9V[i] *= 10E8;
		cout << "expectedFWHM1Point9V[" << i << "] = " << expectedFWHM1Point9V[i] << endl;
	}
	
	// expected FWHM 960 mV graph
	
	TGraphErrors *gExpClip1Point9V = new TGraphErrors(nClip,xClip,&expectedFWHM1Point9V[0],0,0);
	gExpClip1Point9V->SetLineStyle(7);
	gExpClip1Point9V->SetLineColor(kRed);
	gExpClip1Point9V->SetMarkerStyle(20);
	gExpClip1Point9V->SetMarkerSize(0.8);
	
	// Collection of Output FWHM graphs, 2 amplitudes, serveral V clipping
	
	TMultiGraph *mgClipOutputFWHM = new TMultiGraph();
	mgClipOutputFWHM->SetTitle("Collection of Output FWHM graphs, 2 amplitudes, serveral V clipping");
	
	mgClipOutputFWHM->Add(gClip1Point9V);
	mgClipOutputFWHM->Add(gClip960mV);
	mgClipOutputFWHM->Add(gExpClip960mV);
	mgClipOutputFWHM->Add(gExpClip1Point9V);
	
	
	TCanvas *cmgClipOutputFWHM = new TCanvas("cmgClipOutputFWHM","Collection of Output FWHM graphs, 2 amplitudes, serveral V clipping");
	mgClipOutputFWHM->Draw("APEL");
	
	cmgClipOutputFWHM->Modified();
	mgClipOutputFWHM->GetXaxis()->SetTitle("V clipping (mV)");
	mgClipOutputFWHM->GetYaxis()->SetTitle("Output FWHM (ns)");
	cmgClipOutputFWHM->Update();
		
	legend = new TLegend(0.6,0.67,0.89,0.86,"V input");
	legend->AddEntry(gClip1Point9V, "1.9 V", "lp");
	legend->AddEntry(gClip960mV, "960 mV", "lp");
	legend->AddEntry(gExpClip960mV, "Exp 960 mV", "lp");
	legend->AddEntry(gExpClip1Point9V, "Exp 1.9 V", "lp");
	legend->SetTextSize(0.04);
	legend->SetMargin(0.5);
	legend->Draw();
	
	// Hysteresis plot: V output (t) in function of V input (t) for several clipping values
	
	// variables used in the analysis
	
	Long64_t iInputMax, iOutputMax;
	Float_t xInputMax, xOutputMax, xInputHalf, xOutputHalf;
	Double_t InputMax, OutputMax, InputHalf, OutputHalf;
	
	Long64_t firstIndex = 0;
	Long64_t lastIndex = 0;
	Long64_t inputGraphPoints = 0;
	Long64_t outputGraphPoints = 0;
	
	// hard coded values to cut the x axis of both waves
	// Input wave
	
	inputWaveName += " graph";
	
	TGraphErrors *gInput = listOfGraphs->FindObject(inputWaveName);
	gInput->SetLineColor(kRed);
	gInput->SetLineWidth(2);
	
	xInput = gInput->GetX();
	yInput = gInput->GetY();
	inputGraphPoints = gInput->GetN();
	
	cout << inputGraphPoints << endl;
	
	// Invert the input wave
	
	for(Int_t i = 0; i < inputGraphPoints; i++) {
		yInput[i] = -(yInput[i]);
	}
	
	// find the x at which the graph reaches the max value
	
	iInputMax = TMath::LocMax(inputGraphPoints, yInput);
	xInputMax = xInput[iInputMax];
	cout << "iInputMax = " << iInputMax << endl;
	cout << "xInputMax = " << xInputMax << endl;
	InputMax = gInput->Eval(xInput[iInputMax]);
	cout << "InputMax = " << InputMax << endl;
	
	// Output wave
	
	outputWaveName += " graph";
	
	TGraphErrors *gOutput = listOfGraphs->FindObject(outputWaveName);
	gOutput->SetLineWidth(2);
	
	xOutput = gOutput->GetX();
	yOutput = gOutput->GetY();
	outputGraphPoints = gOutput->GetN();
	
	// find the x at which the graph reaches the max value
	
	iOutputMax = TMath::LocMax(outputGraphPoints, yOutput);
	xOutputMax = xOutput[iOutputMax];
	cout << "iOutputMax = " << iOutputMax << endl;
	cout << "xOutputMax = " << xOutputMax << endl;
	OutputMax = gOutput->Eval(xOutput[iOutputMax]);
	cout << "OutputMax = " << OutputMax << endl;
	
	// compute x delay between max points
	
	Double_t delay = xOutputMax - xInputMax;
	cout << "delay = " << delay << endl;
	
	// Shift the x axis of the input graph and create a new graph with only a portion of the first graph
	
	for(Int_t i = 0; i < inputGraphPoints; i++) {
		xInput[i] += inputDelay;
		
		if(xInput[i] >= lowerCut) {
			if(firstIndex == 0) firstIndex = i;
		}

		if(xInput[i] <= upperCut)
			lastIndex = i;
	}
	
	cout << "firstIndex = " << firstIndex << endl;
	cout << "lastIndex = " << lastIndex << endl;
	cout << "xInput[firstIndex] = " << xInput[firstIndex] << endl;
	cout << lastIndex - firstIndex << endl;
	
	Long64_t input2GraphPoints = lastIndex - firstIndex;
	
	TGraphErrors *gInput2 = new TGraphErrors(input2GraphPoints);
	gInput2->SetTitle(inputWaveName);
	
	for(Int_t i = firstIndex; i <= lastIndex; i++) {
		gInput2->SetPoint(i - firstIndex,xInput[i],yInput[i]);
	}
	
	TCanvas *cgInput2 = new TCanvas("cgInput2", "cgInput2", 1200,800);
	gInput2->Draw("AL");
	
	// create a new graph with only a portion of the first graph
	
	firstIndex = 0;
	lastIndex = 0;
	
	for(Int_t i = 0; i < outputGraphPoints; i++) {
		if(xOutput[i] >= lowerCut) {
			if(firstIndex == 0) firstIndex = i;
		}

		if(xOutput[i] <= upperCut)
			lastIndex = i;
	}
	
	cout << "firstIndex = " << firstIndex << endl;
	cout << "lastIndex = " << lastIndex << endl;
	cout << "xOutput[firstIndex] = " << xOutput[firstIndex] << endl;
	cout << lastIndex - firstIndex << endl;
	
	Long64_t output2GraphPoints = lastIndex - firstIndex;
	
	TGraphErrors *gOutput2 = new TGraphErrors(output2GraphPoints);
	gOutput2->SetTitle(outputWaveName);
	
	for(Int_t i = firstIndex; i <= lastIndex; i++) {
		gOutput2->SetPoint(i - firstIndex,xOutput[i],yOutput[i]);
	}
	
	TCanvas *cgOutput2 = new TCanvas("cgOutput2", "cgOutput2", 1200,800);
	gOutput2->Draw("AL");
	
	// first hysteresis plot
	
	Double_t step;
	
	Double_t *xInput2;
	xInput2 = gInput2->GetX();
	
	cout << "xInput2[input2GraphPoints - 1] = " << xInput2[input2GraphPoints - 1] << endl;
	cout << "xInput2[0] = " << xInput2[0] << endl;
	
	step = (xInput2[input2GraphPoints - 1] - xInput2[0])/output2GraphPoints;
	
	cout << "step = " << step << endl;
	
	// in case gInput2 and gOutput2 contain a different number of points create the hysteresis plot with gOutput2 points
	// and modify the yInput2 to match the number of points of yOutput2
	
	vector<double> yInput2;
	
	for(Int_t i = 0; i < output2GraphPoints; i++) {
		yInput2.push_back(gInput2->Eval(xInput2[0] + i*step));
	}
	
	Double_t *yOutput2;
	yOutput2 = gOutput2->GetY();
	
	TGraphErrors *gHyst = new TGraphErrors(output2GraphPoints, &yInput2.at(0),yOutput2);
	gHyst->SetTitle("Hysteresis plot");
	
	gHyst->GetXaxis()->SetTitle("Vin(t) [mV]");
	gHyst->GetYaxis()->SetTitle("Vout(t) [mV]");
	gHyst->GetYaxis()->SetTitleOffset(1.4);
	
	TCanvas *cgHyst = new TCanvas("cgHyst", "cgHyst", 1200,800);
	cgHyst->SetLeftMargin(0.12);
	gHyst->Draw("AL");
	
	// collection of graphs
	
	TMultiGraph *mgInputOutput = new TMultiGraph();
	mgInputOutput->Add(gInput);
	mgInputOutput->Add(gOutput);
	mgInputOutput->SetTitle("Input and output");
	
	TCanvas *cmgInputOutput = new TCanvas("cmgInputOutput", "Input and output", 1200,800);
	mgInputOutput->Draw("AL");
	cmgInputOutput->Update();
	legend = new TLegend(0.65,0.68,0.86,0.86);
	legend->AddEntry(gInput, "Input", "lp");
	legend->AddEntry(gOutput, "Output", "lp");
	legend->SetMargin(0.4);
	legend->SetTextSize(0.04);
	legend->Draw();
	cmgInputOutput->Modified();

	
}

