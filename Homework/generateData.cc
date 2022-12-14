// Generate simple multivariate data according to a specified
// hypothesis (signal or backround) or as a mixture.

#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TMath.h>
#include <TFile.h>
#include <TRandom3.h>
#include <TTree.h>
#include "Event.h"

using namespace std;

void generateData(){

  // create output files
  const int numFiles = 2;           // one for training, one for testing
  string fileName[numFiles];
  fileName[0] = "testData.root";
  fileName[1] = "trainingData.root";

  // Set up to generate random values

  TRandom3* ran = new TRandom3(112233);
  const int numEvents = 10000;
  const double r0 = 2.0;
  const double sigma = 0.5;
  const double a = 0.7;

  for (int j=0; j<numFiles; j++){      // j = 0 test, j = 1 train

    // Book single branch n-tuples (TTrees), 3 double-valued entries per event.
    TFile* file = new TFile(fileName[j].c_str(), "recreate");
    TTree* sig = new TTree("sig", "Tree for signal events");
    TTree* bkg = new TTree("bkg", "Tree for background events");
    Event evt;
    sig->Branch("evt", &evt, "x/d:y/d:z/d");
    bkg->Branch("evt", &evt, "x/d:y/d:z/d");

    // generate signal events
    for (int i=0; i<numEvents; ++i){
      double x = sigma*ran->Gaus();
      double y = sigma*ran->Gaus();
      double r = ran->Rndm();
      double z = ran->Rndm();
      evt.x = x;
      evt.y = y;
      evt.z = z;
      sig->Fill();
    }

    // and background events    
    for (int i=0; i<numEvents; ++i){
      double r = ran->Rndm();
      double theta = r*a*TMath::Pi();
      double x0 = r0*cos(theta);
      double y0 = r0*sin(theta);
      double x = x0 + sigma*ran->Gaus();
      double y = y0 + sigma*ran->Gaus();
      double u = ran->Rndm();
      double z = pow(u, 1./(1.+2.*theta));
      evt.x = x;
      evt.y = y;
      evt.z = z;
      bkg->Fill();
    }
    
    // Store trees and close up    
    file->Write();
    file->Close();
    
  }           // loop over j = 0, 1  (training, test)

  return;
}
