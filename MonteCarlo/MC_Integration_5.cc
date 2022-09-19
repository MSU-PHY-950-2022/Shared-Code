void MC_Integration_5(void){

  TF1* f1 = new TF1("f1","3*x^3 - x",0,1);

  int nTrials = 2000;
  double nSamples = 50;

  double trials[20];
  double mean = 0;
  TRandom r(1534);
  for(int t = 0; t<nTrials; t+=1){    
    double integral = 0;
    for(int b = 1; b<=nSamples; b+=1){
      double xi = r.Uniform();
      double fi = f1->Eval(xi);
      integral += fi;

      double xxi = 1-xi;
      fi = f1->Eval(xxi);
      integral += fi;
    }
    integral /= nSamples*2;
    cout << "Integral: " << integral << endl;
    trials[t] = integral;
    mean += integral;
  }
  mean /= nTrials;

  cout << "Mean: " << mean << endl;

  double variance = 0;
  for(int t = 0; t<nTrials; t+=1){    
    variance += TMath::Power(trials[t]-mean,2);
  }
  variance /= nTrials;
  variance = sqrt(variance);
  
  cout << "Std Dev: " << variance << endl;

}
