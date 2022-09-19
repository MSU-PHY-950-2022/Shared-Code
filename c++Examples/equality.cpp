#include <iostream>

using namespace std;

int main() {

  float a, b, c = 0;

  cout << "Enter two numbers\n";
  cin >> a; cin >> b;

  c = a - b;

  if (a == b) cout << "Two numbers are equal\n";

  if (!c) {
    cout << "Two numbers are equal\n";
    return 0;
  }

  if (a > b) {
    cout << "The first number is greater\n";
  }  else {
    cout << "The second number is greater\n";
  }

  return 0;
}
 
