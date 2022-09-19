#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TFile.h>
#include <TString.h>
#include <TMVA/Factory.h>
#include "TMVA/DataLoader.h"

void tmvaTrain() {  

  // Create ouput file, factory object and open the input files
  TFile* outputFile = TFile::Open( "TMVA_NotEqual.root", "RECREATE" );
  
  // Create the factory object. Later you can choose the methods
  // whose performance you'd like to investigate. The factory is
  // the only TMVA object you have to interact with
  //
  // The first argument is the base of the name of all the
  // weightfiles in the directory weight/
  //
  // The second argument is the output file for the training results
  // All TMVA output can be suppressed by removing the "!" (not) in
  // front of the "Silent" argument in the option string
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
					      "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

  TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
  
  TFile* trainingFile = new TFile("trainingData.root");
  TFile* testFile = new TFile("testData.root");

  // get the TTree objects from the input files
  // one set for training
  TTree* sigTrain = (TTree*)trainingFile->Get("sig");
  TTree* bkgTrain = (TTree*)trainingFile->Get("bkg");
  int nSigTrain = sigTrain->GetEntries();
  int nBkgTrain = bkgTrain->GetEntries();
  
  // one set for testing
  TTree* sigTest = (TTree*)testFile->Get("sig");
  TTree* bkgTest = (TTree*)testFile->Get("bkg");
  int nSigTest = sigTest->GetEntries();
  int nBkgTest = bkgTest->GetEntries();

  // global event weights (see below for setting event-wise weights)
  // let the signal and background have equal rates.  basically assumes
  // they have equal probabilities.  One can always change this as needed.
  double sigWeight = 1;
  double bkgWeight = 1;
  //At this time, we also pass in the testing and training trees
  dataloader->AddSignalTree(sigTrain, sigWeight, TMVA::Types::kTraining);
  dataloader->AddBackgroundTree(bkgTrain, bkgWeight, TMVA::Types::kTraining);
  dataloader->AddSignalTree(sigTest, sigWeight, TMVA::Types::kTesting);
  dataloader->AddBackgroundTree(bkgTest, bkgWeight, TMVA::Types::kTesting);
   
  // Define the input variables that shall be used for the MVA training
  // (the variables used in the expression must exist in the original TTree).
  dataloader->AddVariable("x", 'F');
  dataloader->AddVariable("y", 'F');
  dataloader->AddVariable("z", 'F');

  TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";
  //Tell the TMVA factory how to use the events:
  // ntrain = 0 means use all training/testing events
  // NormMode determines the relative signal/background normalizations.  Default = EqualNumEvents (ie, equal number of signal and bkgd events)
  // Setting NormMode = None allows the tree to preserve your signal/bkgd weights set above.
  dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,
				       "nTrain_Signal=0:nTrain_Background=0:NormMode=None:!V" );
  

  // Create MVA methods (see TMVA manual).  
  // Create a Fisher Discriminant first
  factory->BookMethod(dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher");  
  //Next create a Neural Network (Multilayer Perceptron)
  factory->BookMethod(dataloader, TMVA::Types::kMLP, "MLP", "H:!V:HiddenLayers=3");
  
  // Train, test and evaluate all methods
  factory->TrainAllMethods();
  factory->TestAllMethods();
  factory->EvaluateAllMethods();    

  // Save the output and finish up
  outputFile->Close();
  std::cout << "==> wrote root file TMVA.root" << std::endl;
  std::cout << "==> TMVAnalysis is done!" << std::endl; 

  delete factory;

  return;
}
