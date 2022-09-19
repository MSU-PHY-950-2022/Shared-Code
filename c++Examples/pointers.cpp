#include <iostream>

using namespace std;

int main() {

  // intialise name with age
  int wade = 75; 
  int* professor = &wade;

  wade++; // I grew!
  
  // show height
  cout << "Wade is " << wade << endl; // Wade is 76
  cout << "Professor is " << professor << endl; // professor is 0xbffffbb4
  cout << "Professor is " << *professor << endl; // professor is 76
  
  // change professor to paul
  int paul = 67;
  professor = &paul;
  
  (*professor)++; // more growth
  
  // show height
  cout << "Wade is " << wade << endl; // Wade is still 76
  cout << "Professor is " << *professor << endl; // professor is 

  return 0;
}
