#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  ifstream file("myfile.txt"); 
  string line;
  
  if (file.is_open()) { 

    file.seekg(0);

    while (!file.eof()) {
      getline(file, line);
      cout << line << endl;
    }

    file.close(); 

  } else {
    cout << "Unable to open file";    
  }

  return 0;
}
