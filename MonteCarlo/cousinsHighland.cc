
using namespace std;

void generatePseudoData(TH1D* histo, double bkgd, double bkgdErr, double signal){

  float b = 0;
  float pd = 0;
  for(int i=0; i<1E5; i++){
    b = bkgd*gRandom->Gaus(1,bkgdErr);
    pd = gRandom->PoissonD(signal + b);

    histo->Fill(pd);
    
  }
  return;
}

void cousinsHighland(void){

  gStyle->SetOptStat(0);
  
  vector<float> sigRates;
  vector<float> pvals;
  vector<TH1D*> histos;

  float background = 50;
  float bkgdErr = 0.20;
  float signal = 0;
  float maxSig = 40;
  int data = background+5;
  
  TString name;
  
  for(int i=0; i<100; i+=1){
    signal = maxSig/100.0*i;
    name = "pseudoData s=";
    name.Append(to_string(signal).c_str());
    
    TH1D* hist = new TH1D(name,name,175*2,0,175);

    generatePseudoData(hist,background,bkgdErr,signal);

    histos.push_back(hist);
    sigRates.push_back(signal);
    pvals.push_back(hist->Integral(0,hist->FindBin(data))/hist->Integral());
  }

  int comp = 99;
  TCanvas* can1 = new TCanvas("histos","histos");
  histos[0]->SetXTitle("N events");
  histos[0]->Draw();
  histos[comp]->SetLineColor(2);
  histos[comp]->Draw("same");
  cout << "Signal rate: " << sigRates[comp] << endl;
  cout << "P-value: " << pvals[comp] << endl;
  TLine* dataL = new TLine(data,0,data,histos[0]->GetMaximum());
  dataL->SetLineWidth(3);
  dataL->Draw("same");
  
  TGraph* gr = new TGraph(100,&sigRates[0],&pvals[0]);

  TCanvas* can2 = new TCanvas("Pvalues","Pvalues");
  TH2D* h2d = new TH2D("Pvalue Graph","Pvalue Graph",100,0,maxSig,100,0,pvals[0]+0.05);
  h2d->SetXTitle("Signal Rate");
  h2d->SetYTitle("P-value");
  h2d->Draw();
  
  gr->SetLineWidth(2);
  gr->SetLineColor(4);
  gr->Draw("same");

  TLine* alpha = new TLine(0,0.10,maxSig,0.10);
  alpha->SetLineWidth(2);
  alpha->SetLineColor(2);
  alpha->Draw("same");
  
}
