#include <iostream>

using std::cout;
using std::endl;

namespace first
{
  int x = 1; 
  int y = 2;
}

namespace second
{
  double x = 1.1; 
  double y = 2.2;
}

int main() {

  // using first namespace
  using namespace first;
  // no need to scope as using namespace
  cout << "first: " << x << " " << y << endl;

  // must scope or would get "first" objects
  cout << "second: " << second::x << " " << second::y << endl; 
  
  return 0;
}
