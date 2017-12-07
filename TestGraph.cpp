#include <iostream>
#include <unordered_map>
#include "Graph.cpp"
//#include "FunctGroup.cpp"
#include "ReadCSV.cpp"

int main (int argc, char * argv[]) {
  Graph<FunctGroup> g;

  const int size = 3;
  FunctGroup * nodes[size] = {
    new FunctGroup("H", false, "12"),
    new FunctGroup("O", false, "1"),
    new FunctGroup("O", false, "2")                 
  };

  for (int i = 0; i < size; i++) {
    g.add_node(nodes[i]);
  }

  g.add_edge(nodes[0], nodes[1], 1);
  g.add_edge(nodes[1], nodes[0], 1);
  g.add_edge(nodes[2], nodes[0], 2);
  g.add_edge(nodes[2], nodes[0], 1);

  cout << g.to_string();

  /*
  unordered_map<string, int> m = {
    {"one", 1},
    {"two", 2},
    {"three", 3}
  };
  */

  unordered_map<FunctGroup, int> m = {
    {*nodes[0], 0},
    {*nodes[1], 1},
    {*nodes[2], 2}
  };  

  for (const auto& p: m) {
    cout << "Key:[" << p.first << "] Value[" << p.second << "]" << endl;
  }

  //if we have some positional commandline args...
  if (argc > 1) {
    //...use the first one as the filename for the table of Joback contributions
    string filename = argv[1];
    auto * table = read_joback(filename);    
    
    //print out the table
    for (auto row: *table) {
      cout << "Key:[" << *row.first 
           << "] Values:" << endl;
      for (auto contrib: *row.second) {
        cout << "  Key:[" << contrib.first 
             << "] Value[" << contrib.second << "]" << endl;
      }
    }

    //clean up memory
    for (auto row: *table) {
      //cout << *row.first << endl;
      delete row.first;
      delete row.second;
    }
    delete table;
  }

  //clean up all allocated memory
  
  //FunctGroups from nodes
  for (int i = 0; i < size; i++) {
    delete nodes[i];
  }
}
