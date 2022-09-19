#include <iostream>
using namespace std;

int main() {

  int a; float b; float c;
  float d = 10.2;
  float result;
  
  // get two numbers
  cout << "Enter an integer and real number" << endl;
  cin >> a;
  cin >> b;
  
  c = 2.1;
  result = b * a + c;
  result = (result + 2)/d;
  
  // display the answer
  cout << "Result of calculation: " << result << endl;

  return 0;
}
