#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TList.h>
#include <TKey.h>
#include "Event.h"

void readData(){

  // Open input file, get the TTrees, put into a vector
  TFile* inputFile = new TFile("testData.root");
  inputFile->ls();
  TTree* sig = (TTree*)(inputFile->Get("sig"));
  TTree* bkg = (TTree*)(inputFile->Get("bkg"));
  vector<TTree*> treeVec;
  treeVec.push_back(sig);
  treeVec.push_back(bkg);
  
  // Loop over TTrees  
  for (uint i=0; i<treeVec.size(); i++){
    
    treeVec[i]->Print();

    Event evt;
    treeVec[i]->SetBranchAddress("evt", &evt);

    int numEntries = treeVec[i]->GetEntries();
    cout << "number of entries = " << numEntries << endl;
    
    // Loop over first 5 events
    for (int j=0; j<5; j++){
      treeVec[i]->GetEntry(j);                // sets the new evt
      cout << evt.x << "  " << evt.y << "  " << evt.z << std::endl;
    }
    
  }

  return;
}
