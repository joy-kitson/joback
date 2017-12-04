#include <iostream>
#include <string>
#include <math.h>

using namespace std;

template<class T, int num_nodes>
class Graph {
  protected:
  bool is_directed;
  double* distances;
  T* nodes;

  public:
  
  //constructors
  Graph() {
    Graph(false);
  }

  Graph(bool directed) {
    is_directed = directed;
    
    distances = new double[num_nodes * num_nodes];
    init_distances();
    
    nodes = new T[num_nodes];
    init_nodes();
  }

  void init_distances() {
    for (int r = 0; r < num_nodes; r++) {
      for (int c = 0; c < num_nodes; c++) {
        if (r == c) {
          //set diagonal to 0
          //there's never a distance between a node and itself
          distances[r + num_nodes*c] = 0;
        } else {
          //make all other distances infinte
          distances[r + num_nodes*c] = INFINITY;
        }
      }
    }
  }

  void init_nodes() {
    for (int i = 0; i < num_nodes; i++) {
      nodes[i] = new T();
    }
  }

  //destructors
  ~Graph() {
    delete [] distances;
    delete [] nodes;
  }

  //mutators:
  bool toggle_directed() {
    is_directed = !is_directed;
    
    //if graph is to be undirected, make distance matrix symetric,
    //keeping top-right values
    if (!is_directed) {
      for (int r = 0; r < num_nodes - 1; r++) {
        for (int c = r + 1; c < num_nodes; c++) {
          distances[c + r*num_nodes] = distances[r + c*num_nodes];
        }  
      }
    }

    return is_directed;
  }

  void set_distance(int start_node, int end_node, double dist) {
    distances[start_node + num_nodes*end_node] = dist;
    if (!is_directed) {
      distances[end_node + num_nodes*start_node] = dist;
    }
  }

  void set_node(int index, T new_node) {
    nodes[index] = new_node;
  }

  //accessors:
  bool get_is_directed() {
    return is_directed;
  }

  double get_distance(int start_node, int end_node) {
    return distances[start_node + num_nodes*end_node];
  }
  
  T get_node(int index) {
    return nodes[index];
  }
  
  string toString() {
    return "null";
  }
};

int main (int argc, char* argv[]) {
  Graph<int,2> * g;
  delete g;
} 
