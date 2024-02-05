/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA5
* Shuffle.cpp
* Shuffle main 
*********************************************************************************/
#include<iostream>
#include<fstream>
#include<string>
#include"List.h"
using namespace std;

#define MAX_LEN 300

void shuffle(List& D);
int main(int argc, char * argv[]){


   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " NUMBERS " << endl;
      return(EXIT_FAILURE);
   }
    int x =  atoi(argv[1]);
    int count = 0;
   List D, E;
   cout << endl;
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
   for(int i = 1;i<=x;i++){
      D.insertBefore(i);
      E = D;
      shuffle(D);
      count++;
      while(!(E==D)){
         shuffle(D);
         count++;
      }
      cout << i <<"            "<<count << endl;
      count = 0; 
   } 



    return 0;
}

void shuffle(List& D){
   int n_half;
   List helper;
   if(D.length()%2 == 0){
      n_half = D.length()/2;

      D.moveFront();
      while(D.position() < D.length()){
            if (D.position()>=n_half){
               helper.insertBefore(D.peekNext());
               D.eraseAfter();
               D.moveFront();
            }
            else{
               D.moveNext();
            }
      }

      D.moveFront();
      helper.moveFront();
      while(D.position() < D.length()){
            D.insertBefore(helper.peekNext());
            helper.moveNext();
            D.moveNext();
      }
      // cout << D << endl;
   }
   else{
      n_half = (D.length()/2);

      D.moveFront();
      while(D.position() < D.length()){
            if (D.position()>=n_half){
               helper.insertBefore(D.peekNext());
               D.eraseAfter();
               D.moveFront();
            }
            else{
               D.moveNext();
            }
      }

      D.moveFront();
      helper.moveFront();
      while(D.position() < D.length()){
            D.insertBefore(helper.peekNext());
            helper.moveNext() ;
            D.moveNext();
      }
      D.moveBack();
      D.insertAfter(helper.peekNext());
      // cout << D << endl;
 
   }
}