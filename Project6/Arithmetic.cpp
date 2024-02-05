/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA6
* Arithmetic.cpp
* File I/O reading and output
*********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include "BigInteger.h"
using namespace std;

#define MAX_LEN 800

int main(int argc, char * argv[]){

   int token_count, line_count;
   size_t begin, end, line_length;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   BigInteger A;
   BigInteger B;
   BigInteger C;
   BigInteger D;
   BigInteger three = BigInteger("3");
   BigInteger two = BigInteger("2");
   BigInteger nine = BigInteger("9");
   BigInteger sixTeen = BigInteger("16");
   BigInteger E;
   BigInteger F;
   BigInteger S;
   BigInteger T;
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

   // read each line of input file, then count and print tokens 
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      line_length = line.length();
      
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
         tokenBuffer += "   "+token+"\n";
         token_count++;

         // get next token
         begin = min(line.find_first_not_of(" ", end+1), line_length);
         end = min(line.find_first_of(" ", begin), line_length);
         token = line.substr(begin, end-begin);
      }
      if(line.empty()== false && line_count == 1){
            // cout << line << endl;
            A = BigInteger(line);
      }
      if (line.empty()== false && line_count != 1){
            B = BigInteger(line);
                    //   cout << line << endl;
      }
   }

//   3A-2B 
   C= A*three;
   D = B*two;
   // A^4
   E = A;
   E *= A; 
   E *= A;
   E *= A;
   //B^5
   F = B;
   F *= B;
   F *= B;
   F *= B;
   F *= B;

   // 9A^4
   S = E*nine;
   //16B^5
   T = sixTeen*F;



   // A
   out << A<< endl;
   out << endl;
   //B
   out << B <<endl;
   out << endl;
   out << A+B<<endl;
   out << endl;
   out<< A-B <<endl;
   out << endl;
   out<< A-A <<endl;
   out << endl;
   out<< C-D <<endl;
   out << endl;
   out << A*B << endl;
   out << endl;
   out << A*A << endl;
   out << endl;
   out << B*B << endl;
   out << endl;
   out << S+T << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}