void MC_Integration_7(void){
  
  TF1* f1 = new TF1("f1","3*x^3 - x",0,1.0);
  
  TH1D* h0 = new TH1D("Reso","Reso",100,0,1.0);
  TH1D* hi = new TH1D("Integrals","Integrals",100,0,0.5);

  int nTrials = 2000;
  double nSamples = 50;
  
  double mean = 0;
  double trials[100];
  TRandom r(1534);

  double ss = 0.70;
  int ns1 = 15;
  int ns2 = nSamples - ns1;
  for(int t = 0; t<nTrials; t+=1){    
    double integral = 0;
    
    for(int b = 1; b<=ns1; b+=1){
      double xi = r.Uniform()*ss;
      double xxi = ss-xi;
      double fi = f1->Eval(xi)*ss/ns1;
      integral += fi;
      fi = f1->Eval(xxi)*ss/(ns1);
      integral += fi;
    }
        
    for(int b = 1; b<=ns2; b+=1){
      double xi = ss+r.Uniform()*(1-ss);
      double xxi = ss + 1 - xi;
      double fi = f1->Eval(xi)*(1-ss)/ns2;
      integral += fi;
      fi = f1->Eval(xxi)*(1-ss)/ns2;
      integral += fi;
    }
    integral /= 2;
    hi->Fill(integral);
  }


  TCanvas* c1 = new TCanvas("c1","c1");
  hi->Draw();
}
  
