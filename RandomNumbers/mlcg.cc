#include <iostream>

void mlcg(void){

  //declare the constant variables
  int seed = 123456;
  int mult = 40692;
  int mod = 214748;

  //declare variables
  int n = seed;
  double r = 0;

  //generate some random values!
  for(int i=0; i<15; i++){
    
    //calculate the random variable
    r = n*1.0/mod;
    
    //print to screen
    cout << "Random " << i << ": " << n << " / " << r << endl;

    //set the N+1 seed
    n = (mult * n) % mod;

    
  }

  //all done...
  return;
}
