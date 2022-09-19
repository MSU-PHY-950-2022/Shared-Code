void arExample(void){

  //create a histogram to present our results
  TH1D* h1 = new TH1D("h1","h1",100,-1,1);

  //Random number generator
  TRandom r(112233);

  //Declare variables outside the loop (to save cpu time)
  double r1, r2, fx;

  //let's make 1 million random trials
  for(int i=0; i<1e6; i++){

    //Transform our 1st random number from [0,1] to [-1,1]
    r1 = -1+2*r.Uniform();
    
    //Random number for the rejection, scaled to ymax
    r2 = r.Uniform()*6/8.;

    //Evaluate the function...
    fx = 3/8.0*(1 + r1*r1);
    
    //If we're not rejected, fill the histogram with the 1st RV!
    if(r2 < fx) h1->Fill(r1);
  }

  //Scale for ease of presentation
  h1->Scale(50/h1->Integral());

  //Draw it!
  TCanvas* c1 = new TCanvas("c1","c1");
  h1->SetMinimum(0);
  h1->Draw();

  //Compare to the desired function
  TF1* ff2 = new TF1("f2","3.0/8.0*(1+x^2)",-1,1);
  ff2->SetLineColor(2);
  ff2->Draw("same");

}
