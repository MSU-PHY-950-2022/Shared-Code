void MC_Integration_2(void){
  
  TF1* f1 = new TF1("f1","3*x^3 - x",0,1);
  
  TH1D* h0 = new TH1D("Reso","Reso",1e6,0,2e6);
  
  int nTrials = 20;
  double nSamples = 50;
  
  double mean = 0;
  double trials[100];
  TRandom r(1534);
  for(int n = 2; n<=6; n+=1){
    nSamples = TMath::Power(10,n);
    
    mean = 0;
    for(int t = 0; t<nTrials; t+=1){    
      double integral = 0;
      for(int b = 1; b<=nSamples; b+=1){
	double xi = r.Uniform();
	double fi = f1->Eval(xi)/nSamples;
	integral += fi;
      }
      trials[t] = integral;
      mean += integral;
    }
    mean /= nTrials;
    
    cout << "Mean: " << nSamples << " " << mean << endl;
    
    double variance = 0;
    for(int t = 0; t<nTrials; t+=1){    
      variance += TMath::Power(trials[t]-mean,2);
    }
    variance /= nTrials;
    variance = sqrt(variance);
    
    cout << "Std Dev: " << nSamples << " " << variance << endl;
    
    h0->Fill(nSamples,mean);
    int bb = h0->FindBin(nSamples);
    h0->SetBinError(bb,variance);
  }


  gStyle->SetOptStat(0);
  
  TCanvas* c1 = new TCanvas("c1","c1");			   
  h0->SetMarkerStyle(28);
  h0->SetMarkerSize(0.7);
  h0->Draw("P");

  TLine* ll = new TLine(0,0.25,2e6,0.25);
  ll->SetLineColor(2);
  ll->SetLineWidth(2);
  ll->Draw("same");

  h0->Draw("Psame");

  c1->SetLogx();

  }
  
