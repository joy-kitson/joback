#include <iostream>
#include <functional>
#include "Graph.cpp"
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
  bool set_in_cycle(bool new_val) {
    in_cycle = new_val;
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

typedef Graph<FunctGroup>::Node Node; 
typedef Graph<FunctGroup>::Edge Edge;

//for updating the in_cycle fields of FunctGroups in a Graph
Node * find_cycles(Node * node, Node * last){
  //std::cout << *node->get_datum() << ":" << endl;

  Node * found_cycle = NULL;
  node->set_colour(Node::VISITED);
  for (Edge * e: node->get_neighbours()){
    //it doesn't matter what Node we hold onto, as long as
    //it's been visted before and isn't this node

    if (e->get_end()->get_colour() != Node::VISITED){
      Node * temp = find_cycles(e->get_end(), node);
      if (temp != node && temp!= NULL){
        found_cycle = temp;
      }
    } else if (e->get_end() != last) {
      found_cycle = e->get_end();
    }
  }
  
  node->get_datum()->set_in_cycle(found_cycle != NULL);
  //std::cout << "ret " << *found_cycle->get_datum() << endl;
  return found_cycle;  
}

void find_cycles(Graph<FunctGroup> * graph){
  find_cycles(graph->get_node(0), NULL);  
  
  for(Node * node: graph->get_nodes()) {
    node->set_colour(Node::UNKNOWN);
  }
   
  //std::cout << endl;
}

void find_bonds(Graph<FunctGroup> * graph) {
  for (Node * node: graph->get_nodes()) {
     FunctGroup * fg = node->get_datum();
     string bonds;     

     for (double i = 1; i <= 3; i++) {
       for (Edge * edge: node->get_neighbours()) {
         if (edge->get_weight() == i) {
           bonds += to_string((int) i);
         }
       }
     }

     fg->set_bonds(bonds);
  }
}
