void transformExample(void){

  //Random number generator
  TRandom rand(1122);

  //Histogram for output
  TH1D* h_ax = new TH1D("a(x)","a(x)",100,0,2);

  for(int i = 0; i<1e4; i++){

    //Uniformly distributed random number in [0,1]
    double r = rand.Uniform();

    //fill a(x) = r*r for PDF = 1/sqrt(x)
    h_ax->Fill(r*r);    
    //h_ax->Fill(sqrt(r));    

  }

  //Normalize to unity for ease of graphing
  h_ax->Scale(1.0/h_ax->Integral());

  //Let's make the function we expect to get
  TF1* f1 = new TF1("f1","0.01/sqrt(x)",1e-6,1);

  //Draw it!
  TCanvas* c1 = new TCanvas("c1","canvas 1");
  h_ax->Draw();
  f1->Draw("same");

  ///all done...
  return;
}
