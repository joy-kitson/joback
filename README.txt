+--------------+
|  Executable  |
+--------------+

 joback

 * run with:

   ./joback $compound_file1 $compound_file2 ...

 * takes in a list of csv files, in which each row contains:
   
   (0) the chemical formula of a functional group (first value)
   (1) a series of pairs in the form $index-$bond_type, 
       each representing a single bond where:
       (   ) index     = the row number (starting at 0) in which the
                         functional group at the other end of the
                         bond is located
       ( i ) bond_type = { 1 : the bond is a single bond
                         { 2 : the bond is a double bond
                         { 3 : the bond is a triple bond
   (2) no extra 'blank' entries (i.e. commas without values between them)

 * outputs (for each file's compound):
   
   (0) normal boiling point  : double, in Kelvin
   (1) normal freezing point : double, in Kelvin
   (2) critical temperature  : double, in Kelvin
   (3) critical pressure     : double, in bars
   (4) critical molar volume : double, in cm^3/mol
   (5) constant pressure heat capacity function :
         function(double temp, in Kelvin) -> double, in J/mol

+----------+
|  Source  |
+----------+

 Joback.cpp
 
  * compiles to joback
  * compile with:
    
    g++ -std=c++11 -o joback

  * contains:

    (0) main method
    (1) control for calling auxillary functions (manages overall
        programme control/flow)
    (2) code for calculating chemically meaningful information
        from summed contributions

 ReadCSV.cpp

  * contains:

    (0) code for parsing CC_joback_contributions.csv to create the 
        lookup table for contributions
    (1) code for parsing compound csv files and building a graph

 FunctGroup.cpp

  * contains:
    
    (0) definition of FunctGroup class
    (1) hashing function for FunctGroups (allows FunctGroups 
        to be used as keys in lookup table)
    (2) cycle identification/graph traversal algorithm

 Graph.cpp
  
  * contains:
    
    (0) definition of Graph class
        (   ) template which takes data type to store at nodes
        ( i ) adjacency list representation with weighted edges
        (i i) includes Node and Edge member classes
        (iii) can print out Graph to screen (in adjacency list format)

 TestGraph.cpp
 
 * contains:
   
   (0) proof of functionality test for each of the 
       components of the project

+--------+
|  Data  |
+--------+

 compound0.csv
 compound_napth.csv

 * example compounds, which you can test joback on

 CC_joback_contributions.csv
 
 * the csv file read in to produce the lookup table
 * contains information on the contributions of various
   functional groups commonly found in organic compounds

+----------------+
|  Documenation  |
+----------------+

 README.txt

  * you're here; you've done it
  * contains:
    
    (0) information on all of the other files
    (1) really, that's about it

