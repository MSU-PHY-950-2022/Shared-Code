#include <iostream>
#include <cmath>

using namespace std;

typedef long double Number;

// function prototypes
Number factorial(int n);
float probdist(float prob, int wins, int tries);
float probdist(int r, float mean);

int main() {

  // get probality, successes and tries
  int wins, tries;
  float prob;
  cout << "Enter probability" << endl; 
  cin >> prob;
  cout << "Enter successes" << endl; 
  cin >> wins;
  cout << "Enter tries" << endl; 
  cin >> tries;
 
  // get binomial
  float binom = probdist(prob,wins,tries);
  cout << "Binomial probability:  " << binom << endl;
  
   // get r and mean
  int r;
  float mean;
  cout << "Enter mean" << endl; 
  cin >> mean;
  cout << "Enter r" << endl; 
  cin >> r;
    
  // get poisson 
  cout << "Poisson probability:  " << probdist(r,mean) << endl;
 
  return 0;
}

// now factorial function is recursive
Number factorial(int n) {

  if (n > 1) {
    return (n * factorial(n-1));
  } else {
    return 1;
  }
}

float probdist(float prob, int wins, int tries) {

  // calculate combinations
  Number triesfct = factorial(tries);
  Number winsfct = factorial(wins);
  Number lossesfct = factorial(tries-wins);
  float comb = triesfct / (winsfct * lossesfct);

  // calculate binomial
  float binom = pow(prob,wins) * pow(1-prob,tries-wins) * comb;

  return binom;
}

float probdist(int r, float mean) {
  return (exp(-mean) * pow(mean,r))/factorial(r);
}



