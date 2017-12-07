#include <iostream>
#include <functional>

//using namespace std;

class FunctGroup {
  private:
  std::string name;
  bool in_cycle;
  std::string bonds;

  public:
  friend struct std::hash<FunctGroup>;
  friend ostream& operator<<(std::ostream& out, const FunctGroup& fg) {
    out << fg.name
        << "<bonds:" << fg.bonds << ",";
    
    if (fg.in_cycle) {
      out << "ring";
    } else {
      out << "non-ring";
    }
    
    out << ">";  
    return out;
  }
  bool operator==(const FunctGroup &other) const {
    return name == other.name
           && in_cycle == other.in_cycle
           && bonds == other.bonds;
  }

  //constructors:
  FunctGroup(std::string n) {
    //cout << n << endl;

    name = n;
    in_cycle = false;
    bonds = "";
  }
  FunctGroup(std::string n, bool c) {
    //cout << n << endl;

    name = n;
    in_cycle = c;
    bonds = "";
  }
  FunctGroup(std::string n, bool c, std::string b) {
    //cout << n << endl;

    name = n;
    in_cycle = c;
    bonds = b;
  }

  //destructor:
  ~FunctGroup() {}

  //accessors:
  std::string get_name() {
    return name;
  }
  bool is_in_cycle() {
    return in_cycle;
  }
  std::string get_bonds(){
    return bonds;
  }
  //mutators:
  bool toggle_in_cycle() {
    in_cycle = !in_cycle;
    return in_cycle;
  }
  void set_bonds(std::string newBonds){
    bonds = newBonds;
  }
};

//inject this into std to allow FunctGroup to be hashed
namespace std {
  template<>
  struct hash<FunctGroup> {
    std::size_t operator()(const FunctGroup& key) const noexcept {
      //let in_cycle give the most signifcant bit of the hash and
      //combine the std::hashes of name and bonds to get the other bits
      return (key.in_cycle & 1)
             | ((std::hash<std::string>{}(key.name)
                ^ (std::hash<std::string>{}(key.bonds) << 1)
               ) << 1);
    }
  };
}
