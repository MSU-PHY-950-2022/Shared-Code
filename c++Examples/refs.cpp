#include <iostream>

using namespace std;

int main() {

  // intialise name with age
  int wade = 27; 
  int& lecturer = wade;

  wade++; // Birthday
  
  // show age
  cout << "Wade is " << wade << endl; // Wade is 28
  cout << "Lecturer is " << lecturer << endl; // Lecturer is 28
  
  return 0;
}
