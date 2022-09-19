#include <iostream>
#include <cmath>

using namespace std;

// conversion prototypes
int conversion(int celsius);
float conversion(float celsius);

int main() {
  
  // get precision
  int precis;
  cout << "Approx (default) or accurate? (1 or 2)\n";
  cin >> precis;

  // convert
  if (precis == 2) {
    float celsius;
    cout << "Temperature (C)?\n";
    cin >> celsius;
    cout << "Temperature is " << conversion(celsius) << " F\n";
  } else {
    int celsius;
    cout << "Temperature (C)?\n";
    cin >> celsius;
    cout << "Temperature is " << conversion(celsius) << " F\n";
  }
    
  return 0;
}

// function converts celsius into fahrenheit
int conversion(int celsius) {
  return (int) (((9.0/5.0) * celsius) + 32); 
} 

// function converts celsius into fahrenheit
float conversion(float celsius) {
  return (((9.0/5.0) * celsius) + 32);
}


