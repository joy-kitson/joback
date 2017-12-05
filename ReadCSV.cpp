#include <iostream>

read_csv(string filename) {
  ifstream file (filename);
  string value;

  while(file.good()) {
    getline(file, value, ',');
    cout << value << endl;
  }
}
