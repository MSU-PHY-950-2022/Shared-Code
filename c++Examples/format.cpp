#include <iostream>
#include <iomanip>
//#include <fstream>

using namespace std;

int main() {
  //ofstream file("test.txt");   // to use this replace cout with file

  int inum = 100;

  cout << left << setw(15) << "Integer" 
       << right<< setw(15) << dec << inum                   // decimal
       << setw(15) << oct << inum                           // octal
       << setw(15) << hex << inum                           // hexidecimal
       << setw(15) << showpos << dec << inum                // with sign
       << endl;  
  cout.unsetf(ios::showpos);

  double fnum = 10.1234567;

  cout << left << setw(15) << "Float"
       << right << setw(15) << fnum                         // default (6 s.f.)
       << setw(15) << setprecision(3) << fnum               // 3 s. f.
       << setw(15) << fixed << setprecision(3) << fnum      // 3 d. p.
       << setw(15) << scientific << setprecision(3) << fnum // scientific
       << endl;
  cout.unsetf(ios::scientific);
  cout.precision(6);

  cout << "\nBack to normal = " << inum << " " << fnum << endl;

  return 0;
}
