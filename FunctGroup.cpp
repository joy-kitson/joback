#include <iostream>

using namespace std;

class FunctGroup {
  private:
  string name;
  bool in_cycle;

  public:
  friend ostream& operator<<(std::ostream& out, const FunctGroup& fg) {
    out << fg.name;
    return out;
  }
  FunctGroup(string n) {
    //cout << n << endl;

    name = n;
    in_cycle = false;
  }
  FunctGroup(string n, bool c) {
    //cout << n << endl;

    name = n;
    in_cycle = c;
}

  ~FunctGroup() {}

  //accessors:
  string get_name() {
    return name;
  }
  bool is_in_cycle() {
    return in_cycle;
  }

  //mutators:
  bool toggle_in_cycle() {
    in_cycle = !in_cycle;
    return in_cycle;
  }
};
