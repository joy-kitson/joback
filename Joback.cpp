#include "ReadCSV.cpp"
#include <math.h>

using namespace std;

typedef unordered_map<std::string, double> RowTable;
typedef unordered_map<FunctGroup, RowTable *> JobackTable;
typedef Graph<FunctGroup>::Node Node;

string TABLE_FILE = "CC_joback_contributions.csv";

/* calculates normal boiling point temperature based on
 * summed contributions of functional groups
*/
double normal_boiling_point(double cont_Tb){
  return 198 + cont_Tb;
}

/* calculates critical point temperature based on
 * summed contributions of functional groups
*/
double critical_temperature(double cont_Tc, double Tnbp){
  return Tnbp/(0.584 + 0.965 * cont_Tc - (cont_Tc*cont_Tc));
}

/* calculates critical point pressure based on
 * summed contributions of functional groups
*/
double critical_pressure(double cont_Pc, int Na){
  return pow(0.113 + 0.0032*Na -cont_Pc,-2);
}

/* calculates critical point molar volume based on
 * summed contributions of functional groups
*/
double critical_mvolume(double cont_Vc){
  return 17.5 + cont_Vc;
}

/* calculates critical point molar volume based on
 * summed contributions of functional groups
*/
double normal_freezing_point(double cont_Tf){
  return 122.5 + cont_Tf;
}

/* calculates constant pressure heat capacity at the 0 pressure 
 * limit (ideal behavior)based on summed contributions of functional groups
 * for a, b, c, and d constants for modified shomate equation
*/
string heat_capacity(double cont_A, double cont_B, double cont_C, double cont_D){
  stringstream s;
  double A = cont_A - 37.93;
  double B = cont_B + 0.210;
  double C = cont_C - 3.91e-4;
  double D = cont_D + 2.06e-7;
  s << A << " + " << B << " * T + " << C << " * T^2 + " << D << " * T^3";
  return s.str();
}

int main (int argc, char * argv[]) {
  if (argc > 1) {
    //read in the Joback contributions table
    JobackTable * table = read_joback(TABLE_FILE);

    for (int i = 1; i < argc; i++) {
      //read in the compound's file and construct a Graph
      string filename = argv[i];
      cout << "------------------------------------------------" << endl
           << "Computing contributions in " << filename << endl;
      Graph<FunctGroup> * graph = read_graph(filename);

      //update FunctGroups to account for the information in the Graph
      find_cycles(graph);
      find_bonds(graph);

      //set up the contributions table by inputing all the headers
      //from the Joback contributions table as key with a value of 0 
      RowTable contributions;
      for (auto el: HEADERS) {
        if (el.second >= CONTRIB_START) {
          contributions[el.first] = 0;
        }
      }

      //sum up contributions
      for (Node * node : graph->get_nodes()) {
        
        RowTable * row = (* table)[*node->get_datum()];
        //cout << "Key:" << *node->get_datum() << " Values:" << row << endl;

        for (auto el: *row) {
          //cout << el.first << endl;
          contributions[el.first] += el.second;
        }
      }

      //print out results
      double nbp = normal_boiling_point(contributions[dTb]); 
      cout << "Results:" << endl
           << "Normal Boiling Point Tb=" 
           << nbp << endl
           << "Normal Freezing Point Tf="
           << normal_freezing_point(contributions[dTf]) << endl
           << "Critical Temperature Tc="
           << critical_temperature(contributions[dTc], nbp) << endl
           << "Critical Pressure Pc="
           << critical_pressure(contributions[dPc],contributions[Na]) << endl
           << "Critical Molar Volume Vm="
           << critical_mvolume(contributions[dVc]) << endl
           << "Constant Pressure Heat Capacity Cp(T)="
           << heat_capacity(contributions[dA], 
                            contributions[dB], 
                            contributions[dC], 
                            contributions[dD]) 
           << endl;
    }

  } else {
    cout << "Pass in the names of csv files representing chemical compoundsas positional arguements in order to run" << endl;
  }
}
