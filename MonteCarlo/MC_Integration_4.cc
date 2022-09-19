void MC_Integration_4(void){
  
  TF1* f1 = new TF1("f1","3*x^3 - x",0,1.0);
  
  TH1D* h0 = new TH1D("Reso","Reso",100,0,1.0);
  
  int nTrials = 20;
  double nSamples = 50;
  
  double mean = 0;
  double trials[100];
  TRandom r(1534);

  double ss = 0.70;
  for(double nn = 5; nn<50; nn += 5){
    mean = 0;
    int ns1 = nn;
    int ns2 = 50-nn;
    
    for(int t = 0; t<nTrials; t+=1){    
      double integral = 0;
      
      for(int b = 1; b<=ns1; b+=1){
	double xi = r.Uniform()*ss;
	double fi = f1->Eval(xi)*ss/ns1;
	integral += fi;
      }
 

      for(int b = 1; b<=ns2; b+=1){
	double xi = ss+r.Uniform()*(1-ss);
	double fi = f1->Eval(xi)*(1-ss)/ns2;
	integral += fi;
      }

      trials[t] = integral;
      mean += integral;
    }
    mean /= nTrials;

    double f = nn/50.0;
    
    cout << "Mean: " << f << " " << mean << endl;
    
    double variance = 0;
    for(int t = 0; t<nTrials; t+=1){    
      variance += TMath::Power(trials[t]-mean,2);
    }
    variance /= nTrials;
    variance = sqrt(variance);
    
    cout << "Std Dev: " << f << " " << variance << endl;

    h0->Fill(f,variance);
    int bb = h0->FindBin(f);
    h0->SetBinError(bb,0);
  }
  gStyle->SetOptStat(0);
  h0->SetMarkerStyle(27);
  h0->SetMarkerSize(1.3);
  h0->SetMaximum(0.07);
  h0->SetMinimum(0.01);
  h0->SetMarkerColor(2);
  h0->Draw("PE");


  }
  
