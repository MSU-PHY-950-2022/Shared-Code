#include <iostream>

using std::cout;
using std::endl;

void func(char* temp) {

  int i = 0;
  temp[3] = 'F';

  for (i =0 ; i < 5 ; i++ ) {
    cout << temp[i];
  }
}

int main(){
  char *temp = "Paras";
  func(temp);
  return 1;
}  

