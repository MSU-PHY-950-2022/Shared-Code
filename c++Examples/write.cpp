#include <iostream>
#include <fstream>

using namespace std;

int main() {

  ofstream file("myfile.txt"); 

  if (file.is_open()) { 
    file << "This is a line." << endl;   
    file << "This is another.\n"; 

    int i = 0;
    while (i++ < 10 && !file.bad()) {
      file << "Line of Text " << i << "\n";
    }

    file.close(); 

  } else {
    cout << "Unable to open file";    
  }

  return 0;
}
