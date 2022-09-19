#include <iostream>

using namespace std;

void swap(int* x, int* y);

int main() {

  int x = 2, y = 5;
  cout << x << "," << y << endl; // 2,5
  swap(&x,&y);
  cout << x << "," << y << endl; // now 5,2

  return 0;
}

void swap(int* a, int* b) {

  int tmp = *b;
  *b = *a; // what is going on here? 
  *a = tmp;
  cout << *a << "," << *b << endl; // 5,2

  return;
}
