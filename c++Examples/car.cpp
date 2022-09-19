#include <iostream>

using namespace std;

// car declaration
class Car {
public:
  void setAge(int age);
  int getAge();
  void setPrice(int price);
  int getPrice();
  void brake();
  void accelerate();
private:
  int ageInYears;
  int priceInGBP;
};

// set age accessor function
void Car::setAge(int age) {
  ageInYears = age; 
}

// get age accessor function
int Car::getAge() {
  return ageInYears; 
}

// set price accessor function
void Car::setPrice(int price) {
  priceInGBP = price; 
}

// set price accessor function
int Car::getPrice() {
  return priceInGBP; 
}

// brake member function
void Car::brake() {
  cout << "Slowing down\n";
}

// accelerate member function
void Car::accelerate() {
  cout << "Speeding up\n";
}

int main() {

  // declare two cars
  Car myFiesta;

  // set age and price 
  myFiesta.setAge(10);
  myFiesta.setPrice(6500);

  // display age and price
  cout << "Age: " << myFiesta.getAge() << " years\n";
  cout << "Price: " << myFiesta.getPrice() << " pounds\n";

  return 0;
}
