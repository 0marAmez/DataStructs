/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA5
* ListTest.cpp
* Test for List.cpp
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   // int i, n=11;
   List A,B;
   A.insertAfter(1);
   A.insertAfter(2);
   A.insertAfter(3);
   A.insertAfter(4);
   A.insertAfter(5);
   A.insertAfter(6);
   A.insertAfter(7);
   A.insertAfter(8);
   A.insertAfter(9);
   A.insertAfter(10);


   B.insertBefore(1);
   B.insertBefore(2);
   B.insertBefore(3);
   B.insertBefore(4);
   B.insertBefore(5);
   B.insertBefore(6);
   B.insertBefore(7);
   B.insertBefore(8);
   B.insertBefore(9);
   B.insertBefore(10);



   cout << "B = " << B << endl;
   cout << "B's size " << B.length()<<endl;
   cout << "B front " << B.front()<<endl;
   cout << "B back " << B.back()<<endl;

   cout << "A = " << A << endl;
   cout << "A's size " << A.length()<<endl;
   cout << "A front " << A.front()<<endl;
   cout << "A back " << A.back()<<endl;
  cout << "A FindNext " << A.findNext(5)<<endl;

   A.moveFront();

   for(int i=1; i<=5; i++){
      cout << "A move next:" << A.moveNext() << endl;
   }
   A.insertBefore(45);
   cout << "PeekNext: " << A.peekNext() << endl;
   cout << "PeekPrev: " << A.peekPrev() << endl;
   A.setAfter(213);
   cout << "A = " << A << endl;


   A.moveBack();
   for(int i=1; i<=5; i++){
      cout << "A move next:" << A.movePrev() << endl;
   }
   A.insertAfter(45);
   cout << "PeekNext: " << A.peekNext() << endl;
   cout << "PeekPrev: " << A.peekPrev() << endl;
   A.setBefore(217);
   cout << "A = " << A << endl;

   cout << "POSITION: " << A.position() << endl;
   A.eraseAfter();
   cout << "A = " << A << endl;

   cout << " FindeNext: " <<B.findNext(5) << endl;
   cout << " FindePrev: " <<A.findPrev(7) << endl;

   B.concat(A);
   cout << "B = " << B << endl;

   A.clear();

   cout << "A = " << A << endl;
   cout << "A's size " << A.length()<<endl;



      return( EXIT_SUCCESS );
}