#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  ifstream file("mytable.txt"); 
  string name;
  float mass, charge;
  
  if (file.is_open()) { 

    file.seekg(0);

    while (!file.eof()) {
      file >> name >> mass >> charge;
      cout << name << "\t" << mass << "\t" << charge << endl;
    }

    file.close(); 

  } else {
    cout << "Unable to open file";    
  }

  return 0;
}
