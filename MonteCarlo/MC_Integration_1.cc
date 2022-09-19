void MC_Integration_1(void){

  //Declare some useful variables here
  TF1* f1 = new TF1("f1","3*x^3 - x",0,1);

  int nTrials = 2000;
  vector<double> trials;
  double nSamples = 50;

  double mean = 0;
  double variance = 0;

  TRandom r(1524);
    TH1D* hi = new TH1D("Integrals","Integrals",100,0,0.5);

  //run several trials to get a sense for mean and RMS
  for(int t = 0; t<nTrials; t+=1){    

    double integral = 0;
    //For each trial, use the same number of samples
    for(int b = 1; b<=nSamples; b+=1){
      double xi = r.Uniform();
      double fi = f1->Eval(xi)/nSamples;  //Why divide by nSamples?
      integral += fi;
    }

    cout << "Integral: " << integral << endl;
    hi->Fill(integral);
    
    trials.push_back(integral);
    mean += integral;
  }
  mean /= nTrials;

  cout << "Mean: " << mean << endl;

  // Calculate average (x-mu)^2
  for(int t = 0; t<nTrials; t+=1){    
    variance += TMath::Power(trials[t]-mean,2);
  }
  
  variance /= nTrials;
  variance = sqrt(variance);  //variance is (std dev)^2
  
  cout << "Std Dev: " << variance << endl;
 TCanvas* c1 = new TCanvas("c1","c1");
  hi->Draw();
}
