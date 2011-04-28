// analyze linearity of the input

void AnalyzeLinearity() {
	Float_t y[7] = {691.33,836.34,1011,1146,1332,1492,1728};
	Float_t x[7] = {253.8,259.1,271.1,291.7,359.7,372.2,445.1};
	
	TGraph *gInputLinearity = new TGraph(7,x,y);
	gInputLinearity->SetTitle("Input Linearity");
	gInputLinearity->GetXaxis()->SetTitle("Generator output (mV)");
	gInputLinearity->GetYaxis()->SetTitle("Board input (mV)");
	gInputLinearity->SetMarkerStyle(20);
	gInputLinearity->SetMarkerSize(0.8);
	gInputLinearity->GetYaxis()->SetTitleOffset(1.3);
	
	TCanvas *cgInputLinearity = new TCanvas("cgInputLinearity","cgInputLinearity",800,600);
	cgInputLinearity->SetLeftMargin(0.12);
	gInputLinearity->Draw("APL");
}