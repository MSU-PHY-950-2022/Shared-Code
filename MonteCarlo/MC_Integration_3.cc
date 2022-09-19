void MC_Integration_3(void){
  
  TF1* f1 = new TF1("f1","3*x^3 - x",0,1.0);
  
  TH1D* h0 = new TH1D("Mean","Mean",100,0,1.05);
  TH1D* h1 = new TH1D("StdDev","StdDev",100,0,1.05);
  
  int nTrials = 20;
  double nSamples = 50;
  
  double mean = 0;
  double trials[100];
  TRandom r(1534);

  for(double ss = 0; ss<=1.0001; ss+=0.05){
    mean = 0;
    int ns1 = 25;
    int ns2 = 25;
    
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
    
    cout << "Mean: " << ss << " " << mean << endl;

    double variance = 0;
    for(int t = 0; t<nTrials; t+=1){    
      variance += TMath::Power(trials[t]-mean,2);
    }
    variance /= nTrials;
    variance = sqrt(variance);
    
    cout << "Std Dev: " << ss << " " << variance << endl;

    int bb = h0->FindBin(ss);
    h0->Fill(ss,mean);    
    h0->SetBinError(bb,variance);
    h1->Fill(ss,variance);
    h1->SetBinError(bb,0);
  }
  gStyle->SetOptStat(0);

  TCanvas* c1 = new TCanvas("c1","c1");
  h0->SetMarkerStyle(27);
  h0->SetMarkerSize(1.3);
  h0->SetMarkerColor(2);
  h0->Draw("PE");
  TLine* ll = new TLine(0,0.25,1.05,0.25);
  ll->SetLineColor(2);
  ll->SetLineWidth(2);
  ll->Draw("same");
  h0->Draw("PEsame");

  TCanvas* c2 = new TCanvas("c2","c2");
  h1->SetMarkerStyle(27);
  h1->SetMarkerSize(1.3);
  h1->SetMarkerColor(2);
  h1->Draw("PE");

  }
  
