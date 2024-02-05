/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA8
* Order.cpp
* File reading and output
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include "Dictionary.h"
using namespace std;

#define MAX_LEN 800

int main(int argc, char * argv[]){

   int line_count;
   ifstream in;
   ofstream out;
   string line;


   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
   Dictionary A;
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;      
      A.setValue(line, line_count);
   }

    out << A << endl;
    out << A.pre_string() ;
    cout << A.pre_string();
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
