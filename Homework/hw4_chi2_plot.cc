void h1_style(TH1D* h1, const char* title){
  
  h1->GetXaxis()->SetTitle("X");
  h1->GetYaxis()->SetTitle("N(X)");
  h1->GetXaxis()->SetTitleSize(0.05);
  h1->GetYaxis()->SetTitleSize(0.05);

  h1->GetXaxis()->SetLabelSize(0.04);
  h1->GetYaxis()->SetLabelSize(0.04);
  h1->SetTitle(title);

  h1->SetMaximum(1.25*h1->GetMaximum());

}

double getChi2(TH1D* h1, TH1D* data){

  double chi2 = 0;
  for(int i=1; i<=h1->GetNbinsX(); i++){
    double model = h1->GetBinContent(i);
    if(model == 0) model += 1e-20; ///protect against zeros
    chi2 += pow(model-data->GetBinContent(i),2)/model; 
  }
  return chi2;
}

void hw4_chi2_plot(){
  gStyle->SetOptStat(0);

  TFile* fin = new TFile("hw4_chi2.root","READ");

  TH1D* h1 = (TH1D*)fin->Get("Hypothesis 1");
  TH1D* h2 = (TH1D*)fin->Get("Hypothesis 2");

  TH1D* data = (TH1D*)fin->Get("Data");

  cout << h1->Integral() << " " << h2->Integral() << endl;

  //print out contents of each bin of each histogram
  if(false){
    cout << "Histogram Bin Contents:" << endl;
    cout << "Format: <bin> <h1 content> <h2 content> <data content>" << endl;
    for(int i=1; i<=h1->GetNbinsX(); i++){
      cout << "Bin " << i << ": " << h1->GetBinContent(i) <<  "," << h2->GetBinContent(i) << "," << data->GetBinContent(i) << endl;
    }
  }
  
  int rebinF = 4;
  data->Rebin(rebinF);
  h1->Rebin(rebinF);
  h2->Rebin(rebinF);

  h1->Scale(data->Integral());
  h2->Scale(data->Integral());

  data->SetLineColor(1);
  data->SetMarkerStyle(22);
  data->SetMarkerSize(1);

  h1_style(h1,"");


  TLegend* leg = new TLegend(0.65,0.6, 0.95, 0.85);
  leg->AddEntry(h1, "Hypothesis 1");
  leg->AddEntry(h2, "Hypothesis 2");
  leg->AddEntry(data, "Data");
  leg->SetFillColor(0);

  TCanvas* c1 = new TCanvas("c1","c1");
  h1->Draw();
  h2->Draw("same");
  data->Draw("PEsame");
  c1->SetLeftMargin(0.11);
  c1->SetBottomMargin(0.11);
  c1->SetTopMargin(0.035);
  c1->SetRightMargin(0.035);
  leg->Draw("same");

  cout << "Chi2 by hand: " << getChi2(h1,data) << endl;
  cout << "Chi2 from ROOT: " << data->Chi2Test(h1,"UWCHI2") << endl;
  // https://root.cern.ch/doc/master/classTH1.html#a6c281eebc0c0a848e7a0d620425090a5
  return;
}
