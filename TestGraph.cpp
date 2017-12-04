#include <iostream>
#include "Graph.cpp"
#include "FunctGroup.cpp"

int main (int argc, char * argv[]) {
  Graph<FunctGroup> g;

  const int size = 3;
  FunctGroup * nodes[size] = {
    new FunctGroup("H"),
    new FunctGroup("O"),
    new FunctGroup("O")                 
  };

  for (int i = 0; i < size; i++) {
    g.add_node(nodes[i]);
  }

  g.add_edge(nodes[0], nodes[1], 1);
  g.add_edge(nodes[1], nodes[0], 1);
  g.add_edge(nodes[2], nodes[0], 2);
  g.add_edge(nodes[2], nodes[0], 1);

  cout << g.to_string();
}
