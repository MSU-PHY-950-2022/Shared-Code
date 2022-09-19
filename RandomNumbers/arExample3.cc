void arExample3(void){

  gStyle->SetOptStat(0); //turn off the statistics box in the histogram display
  
  //create a histogram to present our results
  TH1D* h1 = new TH1D("h1","Transformed",100,0,15);
  TH1D* h2 = new TH1D("h2","TF1 Generated",100,0,15);

  TDatime time; //date and time class
  
  //Random number generator
  TRandom3 r(time.GetTime());

  //Declare variables outside the loop (to save cpu time)
  double r1, r2, r3, fx;

  //let's make 1 million random trials
  for(int i=0; i<1e6; i++){

    //Our 1st random number in [1e-9,6]
    r1 = (r.Uniform()+1e-9)*6;

    //Evaluate the function...
    fx = fabs(sin(r1)/r1)*sqrt(r1);
    
    //Random number for the rejection, scaled to ymax in this region
    r3 = r.Uniform()*0.852;

    //If we're not rejected, fill the histogram with the 1st RV!
    if(r3 < fx) h1->Fill(r1);


    //Transform our 2nd random number from [0,1] to [6,15]
    r2 = 6.0+1e-9+r.Uniform()*9;    

    //Evaluate the function...
    fx = fabs(sin(r2)/r2)*sqrt(r2);

    //Random number for the rejection, scaled to ymax in this region
    r3 = r.Uniform()*0.358;

    //If we're not rejected, fill the histogram with the 1st RV!
    if(r3 < fx) h1->Fill(r2,6/9.0);
    //    if(r3 < fx) h1->Fill(r2);

  }

  //Scale for ease of presentation
  h1->Scale(30/h1->Integral());

  //Draw it!
  TCanvas* c1 = new TCanvas("c1","c1");
  h1->SetMarkerColor(4); //4 is blue
  h1->SetMinimum(0);
  h1->Draw();

  //Compare to the desired function
  TF1* ff2 = new TF1("f2","abs(sin(x)/x)*sqrt(x)",0,15);
  //color=2 is red
  ff2->SetLineColor(2);
  ff2->Draw("same");

  for(int i=0; i<1e5; i++){
    h2->Fill(ff2->GetRandom(0,15));
  }

  h2->Scale(30/h2->Integral());
  h2->SetLineColor(kGreen+3);
  h2->Draw("samehist");
      
}
