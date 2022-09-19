void transformExample2(void){

  //Random number generator
  TRandom rand(1122);

  //Histogram for output
  TH1D* h_ax = new TH1D("a(x)","a(x)",100,0,1);

  for(int i = 0; i<1e5; i++){
    //random number in [0,1]
    double r = 1e-9+rand.Uniform();

    //fill a(x) = sqrt(r) for PDF = x
    h_ax->Fill(sqrt(r));    
  }

  //Normalize to unity for ease of graphing
  h_ax->Scale(50/h_ax->Integral());

  //Let's make the function we expect to get
  TF1* f1 = new TF1("f1","x",0,1);

  //Draw it!
  TCanvas* c1 = new TCanvas("c1","canvas 1");
  h_ax->Draw();
  f1->Draw("same");

  ///all done...
  return;
}
