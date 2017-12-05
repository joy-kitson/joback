#include <iostream>
#include <functional>

//using namespace std;

class FunctGroup {
  private:
  std::string name;
  bool in_cycle;

  public:
  friend struct std::hash<FunctGroup>;
  friend ostream& operator<<(std::ostream& out, const FunctGroup& fg) {
    out << fg.name;
    return out;
  }
  bool operator==(const FunctGroup &other) const {
    return name == other.name
           && in_cycle == other.in_cycle;
  }

  FunctGroup(std::string n) {
    //cout << n << endl;

    name = n;
    in_cycle = false;
  }
  FunctGroup(std::string n, bool c) {
    //cout << n << endl;

    name = n;
    in_cycle = c;
  }

  ~FunctGroup() {}

  //accessors:
  std::string get_name() {
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

//inject this into std to allow FunctGroup to be hashed
namespace std {
  template<>
  struct hash<FunctGroup> {
    std::size_t operator()(const FunctGroup& key) const noexcept {
      //let in_cycle give the most signifcant bit of the hash and
      //just bit shift the std::hash of the name
      return (key.in_cycle & 1)
             | (std::hash<std::string>{}(key.name) << 1);
    }
  };
}
