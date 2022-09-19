
double calcChi2(TH1D* data, TH1D* model){

  double chi2 = 0;
  double diff = 0;
  double mod = 0;
  for(int i=1; i<=data->GetNbinsX(); i++){
    mod = model->GetBinContent(i);
    if(mod==0) continue;
    
    diff = data->GetBinContent(i) - mod; 
    chi2 += diff*diff/mod;
  }

  cout << "Chi2: " << chi2 << endl;
  
  return chi2;
}

void chi2_example(void){

  TH1D* dataHist = new TH1D("data", "data", 100, 0, 99);
  TH1D* modelHist = new TH1D("model", "model", 100, 0, 99);

  double meanD = 50;
  double stddevD = 5;

  double meanM = 50;
  double stddevM = 5;
  
  for(int i=0; i<100; i++) dataHist->Fill(gRandom->Gaus(meanD, stddevD));
  
  for(int i=0; i<1E6; i++) modelHist->Fill(gRandom->Gaus(meanM,stddevM));

  modelHist->Scale(dataHist->Integral()/modelHist->Integral());
  modelHist->SetLineColor(2);

  char str[256];
  sprintf(str,"Chi2: %0.3f",calcChi2(dataHist,modelHist));
  
  TCanvas* c1 = new TCanvas("histo","histo");
  dataHist->Draw("PE");
  modelHist->Draw("samehist");
  TLatex* text = new TLatex(10,0.7*dataHist->GetMaximum(),TString(str));
  text->Draw("same");

  dataHist->Chi2Test(modelHist,"UWP");
  
}












void chi2_example2(void){
  gStyle->SetOptStat(0);
  
  vector<double> dataX;
  vector<double> dataY;
  vector<double> errX;
  vector<double> errY;

  double slope = 10;
  double offset = 5;
  
  for(int i=0; i<5; i++){
    double x = (i+1)*5;
    dataX.push_back(x);
    dataY.push_back(offset+slope*x*gRandom->Gaus(1,0.3));
    errY.push_back(offset+slope*x*0.3);
    errX.push_back(0);
  }

  TGraphErrors* errG = new TGraphErrors(5,&dataX[0],&dataY[0],&errX[0],&errY[0]);
  errG->SetMarkerStyle(22);
  errG->SetMarkerSize(1.5);
  
  TCanvas* c2 = new TCanvas("graph","graph");
  TH2D* h2 = new TH2D("hist","hist",100,0,30,100,0,400);
  h2->Draw();
  errG->Draw("samePE");
  
}
