void MC_CoinFlip(void){
  int nTrials = 1e6;
  double nSamples = 20;

  TH1D* h0 = new TH1D("h0","h0",25,0,25);

  TRandom rand(1122);

  for(int i=0; i<nTrials; i++){
    double prob = 0;
    for(int s=0; s<nSamples; s++){
      double flip = 0.0;
      if(rand.Uniform()<0.50) flip = 1.0;
      prob += flip;
    }

    h0->Fill(prob);
  }
  
  h0->Draw();
}
