#include <iostream>

using namespace std;

// funnction prototype
void swap(int x, int y);

int main() {

  int x = 2, y = 5;
  cout << x << "," << y << endl; // 2,5
  swap(x,y);
  cout << x << "," << y << endl; // still 2,5

  return 0;
}

void swap(int x, int y) {

  int tmp = y;
  y = x;
  x = tmp;
  cout << x << "," << y << endl; // 5,2

  return;
}
