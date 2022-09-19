#include <iostream>
#include <sstream>
#include <string>

using namespace std;


int main() {

  stringstream s1;
  s1 << "Wade is " << 27 << " years old";
  cout << s1.str() << endl;

  stringstream s2("28");
  int i; s2 >> i;

  cout << "Next birthday he'll be " << i << endl;

  return 0;
}
