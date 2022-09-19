void transformExample3(void){

  //Random number generator
  TRandom3 rand(1122);

  //Histogram for output
  TH1D* h_ax = new TH1D("a(x)","a(x)",100,-1.1,1.1);

  double r = 0; //random variable
  
  for(int i = 0; i<1e5; i++){
    //random number in [-1,1]
    r = rand.Rndm();
    
    //fill a(x) = asin(r) for cos(x) PDF
    h_ax->Fill(acos(1-2*r)/TMath::Pi());    
  }

  //Normalize to unity for ease of graphing
  h_ax->Scale(45/h_ax->Integral());

  //Let's make the function we expect to get
  TF1* f1 = new TF1("f1","TMath::Pi()*0.5*sin(TMath::Pi()*x)",0,1);

  cout << f1->Integral(0,1)<< endl;
  
  //Draw it!
  TCanvas* c1 = new TCanvas("c1","canvas 1");
  h_ax->Draw();
  f1->Draw("same");

  ///all done...
  return;
}
