#include <iostream>
#include <fstream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCanvas.h>
#include "Event.h"
#include <TMVA/Reader.h>

void analyzeData() {

  // Set up an output file and book some histograms
  TFile* histFile = new TFile("analysis.root", "RECREATE");
  static const int nBins = 100;
  TH1D* hFishSig = new TH1D("hFishSig", "Fisher, signal", nBins, -6., 6.);
  TH1D* hFishBkg = new TH1D("hFishBkg", "Fisher, background", nBins, -6., 6.);

  TH1D* hMLPSig = new TH1D("hMLPSig", "MLP, signal", nBins, 0, 1);
  TH1D* hMLPBkg = new TH1D("hMLPBkg", "MLP, background", nBins, 0, 1);
  
  // Set up the TMVA Reader object.
  // The names in AddVariable must be same as in the input (weight) file.
  TMVA::Reader* reader = new TMVA::Reader();
  float x, y, z;                       // TMVA needs float, not double
  reader->AddVariable("x", &x);  
  reader->AddVariable("y", &y);
  reader->AddVariable("z", &z);
  std::string dir    = "dataset/weights/";
  std::string prefix = "TMVAClassification";
  reader->BookMVA("Fisher", dir + prefix + "_Fisher.weights.xml");
  reader->BookMVA("MLP", dir + prefix + "_MLP.weights.xml");
  
  // Open input file, get the TTrees, put into a vector
  TFile* inputFile = new TFile("testData.root");
  inputFile->ls();
  TTree* sig = (TTree*)(inputFile->Get("sig"));
  TTree* bkg = (TTree*)(inputFile->Get("bkg"));
  std::vector<TTree*> treeVec;
  treeVec.push_back(sig);
  treeVec.push_back(bkg);
  
  // Loop over TTrees
  int nSigAccFish = 0;
  int nBkgAccFish = 0;
  int nSig, nBkg;
  const double tCutFisher = 0.0;
  const double tCutMLP = 0.5;
  for (uint i=0; i<treeVec.size(); i++){
    treeVec[i]->Print();
    Event evt;
    treeVec[i]->SetBranchAddress("evt", &evt);
    int numEntries = treeVec[i]->GetEntries();
    if ( i == 0 ) { nSig = numEntries; }
    if ( i == 1 ) { nBkg = numEntries; }
    std::cout << "number of entries = " << numEntries << std::endl;

    // Loop over events.  The test statistic is identified by the first 
    // argument used above in BookMVA (below, e.g., "Fisher").    
    for (int j=0; j<numEntries; j++){
      treeVec[i]->GetEntry(j);                // sets evt
      x = evt.x;                              // set variables of reader
      y = evt.y;
      z = evt.z;
      
      double tFisher = reader->EvaluateMVA("Fisher");
      if ( i == 0 ){                       // signal
        hFishSig->Fill(tFisher);
      }
      else if ( i == 1 ){                  // background
        hFishBkg->Fill(tFisher);
      }


      double tMLP = reader->EvaluateMVA("MLP");
      if ( i == 0 ){                       // signal
        hMLPSig->Fill(tMLP);
      }
      else if ( i == 1 ){                  // background
        hMLPBkg->Fill(tMLP);
      }
      
      // ADD YOUR CODE HERE TO INCLUDE OTHER CLASSIFIERS SUCH AS MLP
      // AND COUNT THE NUMBERS OF SELECTED EVENTS (COMPARE CLASSIFIER
      // VALUE TFISHER, ETC., TO TCUT).      

    }//end loop over events
  }//end loop over trees

  //Now let's make ROC curves for both classifiers and see how well we did
  TH2D* hROC = new TH2D("MLP ROC","MLP ROC",100,0,1,100,0,1);
  hROC->SetXTitle("Signal Efficiency");
  hROC->SetYTitle("Background Rejection");
    
  //Important!  Normalize your distributions to unity before making ROC curves
  hMLPSig->Scale(1.0 / hMLPSig->Integral());
  hMLPBkg->Scale(1.0 / hMLPBkg->Integral());
  hFishSig->Scale(1.0 / hFishSig->Integral());
  hFishBkg->Scale(1.0 / hFishBkg->Integral());

  double mlpSigEff[nBins];
  double mlpBkgEff[nBins];
  double fishSigEff[nBins];
  double fishBkgEff[nBins];

  for(int i=1; i<=nBins; i++){
    mlpSigEff[i-1] =  hMLPSig->Integral(i,hMLPSig->GetNbinsX());
    mlpBkgEff[i-1] = 1-hMLPBkg->Integral(i,hMLPSig->GetNbinsX());
    fishSigEff[i-1] =  hFishSig->Integral(i,hFishSig->GetNbinsX());
    fishBkgEff[i-1] = 1-hFishBkg->Integral(i,hFishSig->GetNbinsX());

  }

  TGraph* rFish = new TGraph(nBins,fishSigEff,fishBkgEff);
  TGraph* rMLP = new TGraph(nBins,mlpSigEff,mlpBkgEff);

  rFish->SetLineColor(4);
  rMLP->SetLineColor(2);
  rFish->SetLineWidth(2);
  rMLP->SetLineWidth(2);
  
  //Draw some comparisons for those interested
  // Rebin for easier viewing
  hMLPSig->Rebin(10);
  hMLPBkg->Rebin(10);
  hFishSig->Rebin(10);
  hFishBkg->Rebin(10);

  hMLPSig->SetLineColor(2);
  hMLPBkg->SetLineColor(4);
  hFishSig->SetLineColor(2);
  hFishBkg->SetLineColor(4);

  gStyle->SetOptStat(0);
  
  TCanvas* c1 = new TCanvas("Fisher Discriminant","Fisher Discriminant");
  hFishSig->Draw();
  hFishBkg->Draw("same");

  TCanvas* c2 = new TCanvas("Multilayer Perceptron","Multilayer Perceptron");
  hMLPSig->Draw();
  hMLPBkg->Draw("same");

  TCanvas* c3 = new TCanvas("ROC Curves","ROC Curves");
  hROC->Draw();
  rMLP->Draw("Lsame");
  rFish->Draw("Lsame");
  hROC->GetXaxis()->SetRangeUser(0.6,1.0);
  hROC->GetYaxis()->SetRangeUser(0.6,1.0);
  TLegend* legend = new TLegend(0.2,0.2,0.5,0.5);
  legend->AddEntry(rMLP,"MultiLayer Perceptron");
  legend->AddEntry(rFish,"Fisher Discriminant");
  legend->Draw("same");
  
  histFile->cd();

  c1->Write();
  c2->Write();
  c3->Write();

  histFile->Write();
  histFile->Close();
  return;

}
