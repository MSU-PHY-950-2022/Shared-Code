void MC_Integration_6(void){

  TF1* f1 = new TF1("f1","3*x^3 - x",0,1);

  int nTrials = 2000;
  double nSamples = 50;

  vector<double> trials;
  double mean = 0;
  TRandom r(1530);
  
  TH1D* h0 = new TH1D("h0","h0",100,0,1.1);
  TH1D* hi = new TH1D("Integrals","Integrals",100,0,0.5);

  for(int t = 0; t<nTrials; t+=1){    
    double integral = 0;

    for(int b = 1; b<=nSamples; b+=1){
      double xi = TMath::Power(r.Uniform(),1.0/3.0);
      double fi = f1->Eval(xi)/(xi*xi);
      integral += fi;
      //      h0->Fill(xi);
    }

    integral /= (3*nSamples);
    cout << "Integral: " << integral << endl;
    trials.push_back(integral);
    hi->Fill(integral);
    mean += integral;
  }
  mean /= (nTrials);
  
  cout << "Mean: " << mean << endl;
  
  double variance = 0;
  for(int t = 0; t<nTrials; t+=1){    
    variance += TMath::Power(trials[t]-mean,2);
  }
  variance /= nTrials;
  variance = sqrt(variance);
  
  cout << "Std Dev: " << variance << endl;

  TCanvas* c1 = new TCanvas("c1","c1");
  hi->Draw();

}
