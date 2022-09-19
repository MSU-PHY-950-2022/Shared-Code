void MC_BeeKeeper(void){
  gStyle->SetOptStat(0);

  int nTrials = 1e4;

  TH2D* hSmall = new TH2D("Small","Small",100,0,3.5,100,0,1.4);

  TH2D* hLarge = new TH2D("Large","Large",100,0,3.5,100,0,1.4);

  TRandom rand(1122);
  double w, l;
  for(int i=0; i<nTrials; i++){
    //Make a random small bee
    w = 0.5*rand.Gaus(1,0.2);
    l = 1.0*rand.Gaus(1,0.2);
    
    //10% of small bees have dwarfism
    if(rand.Uniform()<0.1) { w*= 0.7; l*=0.7;}
    hSmall->Fill(l,w);


    //Make a random big bee
    w = 0.75*rand.Gaus(1,0.25);
    l = 2*rand.Gaus(1,0.25);
    
    //20% of large bees have dwarfism
    if(rand.Uniform()<0.2) { w *= 0.7; l *= 0.7;}
    hLarge->Fill(l,w);
  }

  TCanvas* c1 = new TCanvas("one","c1");
  hSmall->SetMarkerColor(2);
  hLarge->SetMarkerColor(4);
  hLarge->Draw();
  hSmall->Draw("same");



  TH2D* effW = new TH2D("effW","effW",100,0,1.6,100,0,1.05);
  TH2D* purW = new TH2D("purW","purW",100,0,1.6,100,0,1.05);
  TH2D* epW = new TH2D("epW","epW",100,0,1.6,100,0,1.05);

  TH2D* effL = new TH2D("effL","effL",100,0,3.5,100,0,1.05);
  TH2D* purL = new TH2D("purL","purL",100,0,3.5,100,0,1.05);
  TH2D* epL = new TH2D("epL","epL",100,0,3.5,100,0,1.05);

  TH2D* eff2d = new TH2D("eff2d","eff2d",100,0,3.5,100,0,1.4);
  TH2D* pur2d = new TH2D("pur2d","pur2d",100,0,3.5,100,0,1.4);

  double effv = 0;
  double purv = 0;
  double totSmall = hSmall->Integral();
  int tBin = 0;
  //Integrate over bee length
  for(double l=0; l<=3.5001; l+=0.1){
    tBin = 1+hSmall->FindBin(l,0.0)%100;
    effv = hSmall->Integral(1,tBin,1,hSmall->GetNbinsY());
    purv = effv / (effv + hLarge->Integral(1,tBin,1,hSmall->GetNbinsY()));

    effL->Fill(l,effv/totSmall);
    purL->Fill(l,purv);
    epL->Fill(l,effv*purv/totSmall);
  }

  //Integrate over bee width
  for(double w=0; w<=1.5001; w+=0.1){
    tBin = (int)(hSmall->FindBin(0.0,w)/100.0);
    effv = hSmall->Integral(1,hSmall->GetNbinsX(),1,tBin);
    purv = effv / (effv + hLarge->Integral(1,hSmall->GetNbinsX(),1,tBin));

    effW->Fill(w,effv/totSmall);
    purW->Fill(w,purv);
    epW->Fill(w,effv*purv/totSmall);
  }

  for(int x=1; x<=eff2d->GetNbinsX(); x++){
    for(int y=1; y<=eff2d->GetNbinsY(); y++){

      effv = hSmall->Integral(1,x,1,y);
      purv = effv / (1 + effv + hLarge->Integral(1,x,1,y));

      eff2d->SetBinContent(x,y,effv/totSmall);
      pur2d->SetBinContent(x,y,purv);
    }
  }

  TCanvas* c2 = new TCanvas("c2","c2");
  effL->SetMarkerStyle(20);
  effL->SetMarkerSize(0.9);
  effL->SetMarkerColor(4);
  effL->Draw();

  purL->SetMarkerStyle(22);
  purL->SetMarkerSize(0.9);
  purL->SetMarkerColor(2);
  purL->Draw("same");

  epL->SetMarkerStyle(29);
  epL->SetMarkerSize(1.3);
  //  epL->SetMarkerColor(2);
  //  epL->Draw("same");

  TCanvas* c3 = new TCanvas("c3","c3");
  effW->SetMarkerStyle(20);
  effW->SetMarkerSize(0.9);
  effW->SetMarkerColor(4);
  effW->Draw();

  purW->SetMarkerStyle(22);
  purW->SetMarkerSize(0.9);
  purW->SetMarkerColor(2);
  purW->Draw("same");

  epW->SetMarkerStyle(29);
  epW->SetMarkerSize(1.3);
  //  epL->SetMarkerColor(2);
  //  epW->Draw("same");

  TCanvas* c4 = new TCanvas("c4","c4");
  eff2d->Draw("colz");

  TCanvas* c5 = new TCanvas("c5","c5");
  pur2d->Draw("colz");
   
}
