#include <vector>
#include <sstream>

using namespace std;

template <class N>
//note: there should be an overriden version of
//        ostream& operator<<(ostream &s, const N &n)
//      for any N, in order for the graph to be printable

class Graph {
  public:
  //container classes:
 
  class Node;
 
  //edges are implicitly weighted, directed, by default
  class Edge {
    private:
    Node * start;
    Node * end;
    double weight;

    public:
    Edge(Node * s, Node * e, double w): start(s), end(e), weight(w) {}
  
    ~Edge() {}

    //accessors:
    Node * get_start() {
      return start;
    }
    Node * get_end() {
      return end;
    }
    double get_weight() {
      return weight;
    }

    //mutators:
    void set_weight(double w) {
      weight = w;
    }
  };

  //nodes can have loops, multiple edges, by default
  class Node {
    private:
    vector<Edge *> neighbours; 
    N * datum;
    int colour;

    public:
    //colour constants:
    static const int UNKNOWN = 0;
    static const int SEEN    = 1;
    static const int VISITED = 2;

    Node (N * d): datum(d) {
      neighbours = vector<Edge *>();
      set_colour(UNKNOWN);
    }

    ~Node () {
      //delete all of the Edges starting at this Node
      for(int i = neighbours.size() - 1; i >= 0; i--) {
        delete neighbours[i];
      }
    
      neighbours.clear();
    }

    //accessors:
    vector<Edge *> get_neighbours() {
      return neighbours;
    }
    N * get_datum() {
      return datum;
    }
    int get_colour() {
      return colour;
    }

    //mutators:
    void add_neighbour(Node * neighbour, double weight) {
      //create new Edge between this and neighbour
      Edge * e = new Edge(this, neighbour, weight);

      //and add it to the end of neighbours
      neighbours.push_back(e);
    }
    void set_colour(int c) {
      colour = c;
    }

    //display:
    string to_string() {
      stringstream s;
      
      s << * datum << " : "; //just outputs pointer address now

      int size = neighbours.size();
      for (int i = 0; i < size; i++) {
        N dat = * neighbours[i]->get_end()->get_datum();
        s << "(" << dat << ",";
        s <<         neighbours[i]->get_weight() << ") ";
      }

      s << "\n";

      return s.str();
    }
  };
 

  private:

  //Graph constants
  static const int DATUM_NOT_FOUND = -1;
  
  //Graph fields
  
  vector<Node *> nodes;

  public:

  //Graph functions

  Graph() {
    nodes = vector<Node *>();
  }

  ~Graph() {
    //delete all of the Nodes in this Graph
    for(int i = nodes.size() - 1; i >= 0; i--) {
      delete nodes[i];
    }
    
    nodes.clear();
  }

  //accessors:
  vector<Node *> get_nodes() {
    return nodes;
  }
  int get_index(N * datum) {
    int size = nodes.size(); 
    for (int i = 0; i < size; i++) {
      //check each Node's datum for pointer equality with datum
      if (nodes[i]->get_datum() == datum) {
        return i;
      }
    }
    
    //if we don't find it in the list...
    return DATUM_NOT_FOUND;
  }

  //mutators:
  void add_node(N * datum) {
    //add a new Node containing datum to the end of nodes
    Node * n = new Node(datum);
    nodes.push_back(n);
  }
  void add_edge(int start_index, int end_index, double weight) {
    nodes[start_index]->add_neighbour(nodes[end_index], weight);
  }
  void add_edge(N * start, N * end, double weight) {
    int start_index = get_index(start);
    if (start_index == DATUM_NOT_FOUND) {
      //if the starting datum isn't in the node list, add it
      start_index = nodes.size();
      add_node(start);
    }

    int end_index = get_index(end);
    if (end_index == DATUM_NOT_FOUND) {
      //if the final datum isn't in the node list, add it
      end_index = nodes.size();
      add_node(end);
    }

    add_edge(start_index, end_index, weight);
  }

  //display:
  string to_string() {
    stringstream s;

    int size = nodes.size();
    for (int i = 0; i < size; i++) {
      s << nodes[i]->to_string();
    }

    return s.str();
  } 
};
