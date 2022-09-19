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

void hw6_plots(){
  gStyle->SetOptStat(0);

  TFile* fin = new TFile("hw6_hypotheses.root","READ");

  TH1D* h1 = (TH1D*)fin->Get("Background");
  TH1D* h2 = (TH1D*)fin->Get("Signal");

  TH1D* data = (TH1D*)fin->Get("Data");

  cout << h1->Integral() << " " << h2->Integral() << endl;

  cout << "Histogram Bin Contents:" << endl;
  cout << "Format: <bin> <background content> <signal content> <data content>" << endl;
  for(int i=1; i<=h1->GetNbinsX(); i++){
    cout << "Bin " << i << ": " << h1->GetBinContent(i) << " , " << h2->GetBinContent(i) << " , " << data->GetBinContent(i) << endl;
  }
  

  // This fixes the signal rate in the H1 hypothesis
  // to 0.05% of the background.
  h2->Scale(0.05);
  
  // Sum the histograms to make signal + background
  TH1D* h3 = (TH1D*)h1->Clone("Signal + Bkgd");
  h3->Add(h2);
  h3->SetLineColor(4);

  h1->Scale(data->Integral()/h1->Integral());
  h3->Scale(data->Integral()/h3->Integral());

  data->SetLineColor(1);
  data->SetMarkerStyle(22);
  data->SetMarkerSize(1);

  h1_style(h1,"");


  TLegend* leg = new TLegend(0.65,0.6, 0.95, 0.85);
  leg->AddEntry(h1, "Background-Only");
  leg->AddEntry(h3, "Signal+Background");
  leg->AddEntry(data, "Data");
  leg->SetFillColor(0);

  TCanvas* c1 = new TCanvas("c1","c1");
  h1->Draw();
  h3->Draw("same");
  data->Draw("PEsame");
  c1->SetLeftMargin(0.11);
  c1->SetBottomMargin(0.11);
  c1->SetTopMargin(0.035);
  c1->SetRightMargin(0.035);
  leg->Draw("same");

}

