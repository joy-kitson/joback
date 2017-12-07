#include <iostream>
#include <fstream>
#include <unordered_map>
#include "FunctGroup.cpp"
#include <string>
#include <vector>

//constants for headers of contributions
const std::string NAME = "group";
const std::string IN_CYCLE = "aromatic";
const std::string BONDS = "bonds";
const std::string dTc = "dTc";
const std::string dPc = "dPc";
const std::string dVc = "dVc";
const std::string dTb = "dTb";
const std::string dTf = "dTf";
const std::string dA = "dA";
const std::string dB = "dB";
const std::string dC = "dC";
const std::string dD = "dD";
std::unordered_map<string, int> HEADERS = {
  {NAME, 0},
  {IN_CYCLE, 1},
  {BONDS, 2},
  {dTc, 3},
  {dPc, 4},
  {dVc, 5},
  {dTb, 6},
  {dTf, 7},
  {dA,  8},
  {dB,  9},
  {dC, 10},
  {dD, 11}
};
//records the column number in which the values which should 
//be stored in the contribution table for the row start
const int CONTRIB_START = 3;

//boolean constants
const string TRUE = "TRUE";
const string EITHER = "EITHER";

//define shorter names for the unordered_maps we'll be using
typedef unordered_map<std::string, double> RowTable; 
typedef unordered_map<FunctGroup *, RowTable *> JobackTable; 

std::vector<std::string> split_by_col(const std::string& str, char delimiter) {
  std::vector<std::string> cols;
  std::string token;
  std::istringstream tokenStream(str);
  while (std::getline(tokenStream, token, delimiter)) {
    cols.push_back(token);
  }
  
  return cols;
}

RowTable * copy_RowTable(RowTable * orig) {
  RowTable * copy = new RowTable();
  
  //iterate over all (key, value) pairs in orig and put them in copy
  for (auto el: *orig) {
    (*copy)[el.first] = el.second;
  }

  return copy;
}

JobackTable * read_joback(std::string filename) {
  ifstream file (filename);
  JobackTable * joback_table = new JobackTable();
 
  //make sure the file opened properly 
  if (file.is_open()) {
    cout << "file opened" << endl;
  } else {
    cout << "file not opened" << endl;
    return NULL;
  }
  
  int i = -1;
  std::string line;
  for(; std::getline(file, line); i++) {
    //cout << line << endl;
    if (i!= -1){
      //split the row up
      std::vector<std::string> cols = split_by_col(line, ',');

      //check to make sure it split it right
      for (std::string str: cols) {
        //std::cout <<"\"" << str << "\" ";
      }
      //std::cout << endl;
      
      //then set up all of the contributions
      RowTable * contributions = new RowTable();
      for (auto el : HEADERS) {
        if (el.second >= CONTRIB_START) {
          //std::cout << "{" << el.first 
          //          << ", " << cols[el.second] 
          //          << "}" << endl;
          (* contributions)[el.first] = std::stod(cols[el.second]);
        }
      }
      
      //if the functional group behaves the same
      // whether or not it's in a ring...
      if (cols[HEADERS[IN_CYCLE]] == EITHER) {
        //...then create entries for both ring and non-ring versions
        FunctGroup * fgt = new FunctGroup(cols[HEADERS[NAME]],
                                          true,
                                          cols[HEADERS[BONDS]]);
        FunctGroup * fgf = new FunctGroup(cols[HEADERS[NAME]],
                                          false, 
                                          cols[HEADERS[BONDS]]);

        //assign values
        (* joback_table)[fgt] = contributions;  
        //store a copy of contributions in order to avoid double freeing later
        (* joback_table)[fgf] = copy_RowTable(contributions);

        //cout << *fgt << endl;
        //cout << *fgf << endl;
      } else {
        //...otherwise just make one entries
        FunctGroup * fg = new FunctGroup(cols[HEADERS[NAME]],
                                         cols[HEADERS[IN_CYCLE]] == TRUE,
                                         cols[HEADERS[BONDS]]);
        
        (* joback_table)[fg] = contributions;

        //cout << *fg << endl;
      }
    }
  }
  
  //cout << i << endl;  

  return joback_table;
}
