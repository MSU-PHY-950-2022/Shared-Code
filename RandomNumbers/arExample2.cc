void arExample2(void){

  //create a histogram to present our results
  TH1D* h1 = new TH1D("h1","h1",100,0,2);

  //Random number generator
  TRandom r(11243);

  //Declare variables outside the loop (to save cpu time)
  double r1, r2, r3, fx;

  //let's make 1 million random trials
  for(int i=0; i<1e5; i++){

    //Our 1st random number in [0,1]
    r1 = r.Uniform();

    //Evaluate the function...
    fx = r1*r1*r1 - 0.5*r1*r1*r1*r1;
    
    //Random number for the rejection, scaled to ymax in this region
    r3 = r.Uniform()*0.5;
    //If we're not rejected, fill the histogram with the 1st RV!
    if(r3 < fx) h1->Fill(r1,6);


    //Transform our 2nd random number from [0,1] to [1,2]
    r2 = 1.0+r.Uniform();    
    //Evaluate the function...
    fx = r2*r2*r2 - 0.5*r2*r2*r2*r2;
    //Random number for the rejection, scaled to ymax in this region
    r3 = r.Uniform()*0.84375;
    //If we're not rejected, fill the histogram with the 1st RV!
    if(r3 < fx) h1->Fill(r2,10);

  }

  //Scale for ease of presentation
  h1->Scale(40/h1->Integral());

  //Draw it!
  TCanvas* c1 = new TCanvas("c1","c1");
  h1->SetMinimum(0);
  h1->Draw();

  //Compare to the desired function
  TF1* ff2 = new TF1("f2","x^3 - 0.5*x^4",0,2);
  ff2->SetLineColor(2);
  ff2->Draw("same");

}
