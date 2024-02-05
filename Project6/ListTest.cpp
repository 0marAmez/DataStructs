/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA6
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
   A.insertAfter(111112222);
   A.insertAfter(21213133);
   A.insertAfter(3123213133);
   A.insertAfter(4121331);
   A.insertAfter(512131331);
   A.insertAfter(612131331);
   A.insertAfter(713314235);
   A.insertAfter(88907009);
   A.insertAfter(9078700);
   A.insertAfter(100000000);


   B.insertBefore(112735173315137713);
   B.insertBefore(238439283);
   B.insertBefore(335004368);
   B.insertBefore(4027054270);
   B.insertBefore(54205374032);
   B.insertBefore(61353531);
   B.insertBefore(715331351);
   B.insertBefore(815353153);
   B.insertBefore(9536462);
   B.insertBefore(10353252332);



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

   cout << " FindeNext: " <<B.findNext(9078700) << endl;
   cout << " FindePrev: " <<A.findPrev(7) << endl;

   B.concat(A);
   cout << "B = " << B << endl;

   A.clear();

   cout << "A = " << A << endl;
   cout << "A's size " << A.length()<<endl;



      return( EXIT_SUCCESS );
}
