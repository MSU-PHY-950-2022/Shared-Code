int randDice(TRandom* rr){

  double rv = rr->Uniform();
  if(rv < 1.0/6) return 1;
  else if(rv < 2.0/6) return 2;
  else if(rv < 3.0/6) return 3;
  else if(rv < 4.0/6) return 4;
  else if(rv < 5.0/6) return 5;
  else return 6;
}


// In this problem, we need to work out two chacteristics of the multinomial distribution.
// When we roll two dice, the sum of the two dice can take values between 2 and 12.  However
// each number has a different probability to occur, given that each number occurs just once
// on each die.
//
// We can first calculate the probability to roll a sum of 8, which can occur for 5 of the 36
// possible outcomes in the two-dice roll.  So P(8) = 5/36.  IE, in M rolls of dice, we expect
// N(8) = M*5/36 8's on average.
//
// For the variance, we need to work out the distribution of 8's that we would expect to get
// in N experiments of M rolls.  In this case, we can collapse the multinomial to a binomial
// where we either get an 8 with probability P(8) or not.  The variance of a binomial distribution
// is V = N*p*(1-p).  Thus, if we were to define our experiment as 100 rolls of the dice, we
// should expect a variance in the number of 8's observed to be V=100*P(8)*(1-P(8))=11.96
//
// The following function demonstrates how to calculate the mean and variance for this problem.

void problem1(){

  TH1D* fairDice = new TH1D("test for fair dice","test for fair dice",10,1,10);
  
  TRandom* rr = new TRandom(1223344);

  ///Do a sanity check that the dice are truly fair!
  for(int i=0; i<1e6; i++){
    fairDice->Fill(randDice(rr));
  }
  //Expect the same probability in each bin
  TCanvas* c1 = new TCanvas("c1","c1");
  fairDice->Draw("hist");


  //Study the mean values from multiple trials
  TH1D* meanValues = new TH1D("Mean","Mean Values",100,0.5,6.5);

  for(int z=1; z<=6; z++){
    int nTrials = TMath::Power(10,z);
    double iMean = 0;
    double iVar = 0;

    double nEights = 0;
    int r1 = 0;
    //For each sample of 20 experiments, roll dice N times and work out the mean of the probability to get 8
    //    and the variance on that probability for that trial of 20 experiments
    //Be careful about how you divide your numbers!!  IE, keep track of units.
    for(int tt=0; tt<20; tt++){
      nEights = 0;
      for(int i=0; i<nTrials; i++){
	r1 = randDice(rr) + randDice(rr);
	if(r1==8) nEights++;
      }
      //Print some values for a sanity check
      //      cout << "Calculated " << nEights/nTrials << " for " << z << endl;

      //Calculate mean x
      iMean += nEights;

      //Calculate mean x*x
      iVar += TMath::Power(nEights,2);
    }
    //Take average for each
    iMean /= 20;
    iVar /= 20;

    //Calculate the variance = <x*x> - <x>*<x>
    iVar -= iMean*iMean;

    //Fill mean value histogram
    meanValues->Fill(z,iMean/nTrials);

    //Set mean value bin error to the std deviation
    meanValues->SetBinError(meanValues->FindBin(z),sqrt(iVar)/nTrials);
    
    cout<< "Found mean: " << iMean/nTrials << " +/- " << sqrt(iVar)/nTrials << endl;
  }


  //Now study the variance as a function of # trials
  TH1D* varValuesE = new TH1D("VarExp","Variance Values Exp",110,0,1100);
  TH1D* varValuesO = new TH1D("VarObs","Variance Values Obs",110,0,1100);
  
  int nTrials = 100;
  double nEights = 0;
  int r1 = 0;
  //Now, always roll the dice 100 times to work out the probability, but now integrate over a variable number of experiments.
  for(int nt = 5; nt <=1006; nt+=50){
    double iMean = 0;
    double iVar = 0;
    for(int tt=0; tt<nt; tt++){
      nEights = 0;
      for(int i=0; i<nTrials; i++){
	r1 = randDice(rr) + randDice(rr);
	if(r1==8) nEights++;
      }
      //Print some values for a sanity check
      //      cout << "Calculated " << nEights/nTrials << " for " << nTrials << endl;
      
      //Calculate mean x
      iMean += nEights;
      
      //Calculate mean x*x
      iVar += TMath::Power(nEights,2);
    }
    //Take average for each
    iMean /= nt;
    iVar /= nt;
    
    //Calculate the variance = <x*x> - <x>*<x>
    iVar -= iMean*iMean;

    //Variance Histogram filling
    varValuesO->Fill(nt,iVar);
  
    varValuesE->Fill(nt,nTrials*(5.0/36)*(1-5.0/36));
    cout << "Comparing variances " << iVar << " with " << nTrials*(5.0/36)*(1-5.0/36) << endl;
  }

  //Get Rid of the statistics box in the histogram
  gStyle->SetOptStat(0);


  //Draw the mean value histogram, setting some drawing preferences first
  TCanvas* c2 = new TCanvas("c2","c2");
  meanValues->SetMarkerStyle(2);
  meanValues->SetMarkerSize(1.1);
  meanValues->SetMarkerColor(4);
  meanValues->GetXaxis()->SetTitle("Trials Exponent (10^{n})");
  meanValues->Draw("");
  TLine* ll = new TLine(0.5,5.0/36,6.5,5.0/36);
  ll->SetLineColor(2);
  ll->SetLineWidth(2);
  ll->Draw("same");


  //Draw the variance histogram, setting some drawing preferences first
  TCanvas* c3 = new TCanvas("c3","c3");
  varValuesE->SetMarkerStyle(2);
  varValuesE->SetMarkerSize(1.1);
  varValuesE->SetMarkerColor(4);

  varValuesO->GetXaxis()->SetTitle("# Experiments");
  varValuesO->SetMarkerStyle(22);
  varValuesO->SetMarkerSize(1.1);
  varValuesO->SetMarkerColor(2);

  varValuesO->Draw("P");
  varValuesE->Draw("Psame");
  return;
}

void HW3(void){

  //HW3, problem 1
  cout<< "This is problem 1" << endl;
  problem1();

}
