#include <iostream>
#include <cmath>

using namespace std;

int main() {

  // get a routine to run 
  cout << "\nWhat would you like to do?" << endl;
  cout << "1 - Calculate the mean" << endl;
  cout << "2 - Calculate the standard deviation" << endl;
  cout << "3 - Order the sample lowest first" << endl;
  int request;
  cin >> request;
 
  // get size of sample
  cout << "How big is the sample?" << endl;
  int size;
  cin >> size;

  // get sample values
  int sampleCount = 0;
  float*  sample = new float[size];

  while (++sampleCount <= size) {
    cout << "Sample " << sampleCount << ": ";
    cin >> sample[sampleCount-1];
  }
      
  if (request == 1) {
    
    // calculate sum of sample
    int sampleCount = 0;
    float sum = 0;
    while (++sampleCount <= size) sum += sample[sampleCount-1];
    
    // calculate mean
    float mean = (sum / size);

    cout << "The mean value is " << mean << endl;
  
  } else if  (request == 2) {

    // calculate sum of sample
    int sampleCount = 0;
    float sum = 0;
    while (++sampleCount <= size) sum += sample[sampleCount-1];
    
    // calculate mean
    float mean = (sum / size);
    
    // calculate x_i - mean
    float meanDev = 0; 
    sampleCount = 0;
    while (++sampleCount <= size) 
      meanDev += pow((sample[sampleCount-1] - mean),2);
    
    // calculate standard deviation
    float stdev = sqrt( meanDev / size); 
    
    cout << "The standard deviation is " << stdev << endl; 
    
  } else if  (request == 3) {

    // bubble sort algorithm 
    for (int i = 0; i < (size - 1); i++) {
      for (int j = 0; j < (size - 1); j++) {
        
        if (sample[j] > sample[j+1]) {
          float swap = sample[j];
          sample[j] = sample[j+1];
          sample[j+1] = swap;
        }
      }
    }
    
    cout << "correct order: ";
    for (int i = 0; i < size; i++) cout << sample[i] << " ";
    cout << endl;
    
    
  } else {
    cerr << "Routine number does not exist\n";
    return 1;
  }

  delete [] sample;
  sample = NULL;

  return 0;
}

