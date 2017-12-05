#include <iostream>
#include <fstream>

void read_joback(string filename) {
  ifstream file (filename);
  string value;

  while(file.good()) {
    getline(file, value, ',');
    cout << value << endl;
  }
}
