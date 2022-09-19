#include <iostream>
#include "point_v6.h"

using namespace std;

int main() {

  // declare two points, one at the origin
  Point a(1,2,3), b(2,5,4);
  
  // display distance of points from origin and from each other
  cout << "distance of a from origin: " << a.distance() << endl;
  cout << "distance of b from origin: " << b.distance() << endl;
  cout << "distance between a and b: " << a.distance(b) << endl;
  
  return 0;
}
