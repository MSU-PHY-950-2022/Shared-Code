#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

// Main function must always return type int!
int main(){

  // this sets the seed for the random number generator
  // why is that important?
  srand(time(NULL));

  //generate 100 outcomes
  for(int i=0; i<1E2; i++){

    // First, let's just see the raw output
    // We get random numbers in the range [0, RAND_MAX]
    cout << "Iteration " << i << " , Random 1: " << rand();

    // Divide by RAND_MAX
    cout << ", Random 2: " << rand()/RAND_MAX;

    // Divide by RAND_MAX*1.0
    cout << ", Random 3 " << rand()/(RAND_MAX*1.0) << endl;

    // Add another carriage return for readability
    cout << endl;
  }
  // exit
  return 1;
}

