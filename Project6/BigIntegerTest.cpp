/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA6
* BigIntegerTest.cpp
* Test for BigInteger.cpp
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    BigInteger A = BigInteger("99999");
    BigInteger B = BigInteger("1");
    BigInteger C = BigInteger("100000");
    BigInteger E = BigInteger("-1");
    BigInteger D;
    cout << A << endl;
    cout << B << endl;
    cout << C << endl;
    D = A+B;
    cout << D << endl;

    if(D==C){
        cout << "They are equal!" << endl;
    }
    
    A-= C ;
    cout << A  << endl;
    cout << A.sign() << endl;
    A.makeZero();
    cout << A << endl;
    A+= C;
    cout << A << endl;
    if (A>B){
      cout << "A IS GREATER!" << endl;
    }

    cout << A<< endl;
     A = BigInteger("00000010112199999");
    cout << A << endl;
     B =  BigInteger ("-111111111111111");

     C = A+B;

     cout << C << endl;

     C =  A-B;

     cout << C << endl;

     C*=E;
      cout << C << endl;

    A = BigInteger("100000");
    B = BigInteger ("22345");

    cout << A+B << endl;

    A.negate();
    cout << A.sign() << endl;

      A-= B;
     cout <<  A << endl;


     E = A*B*D;

     cout << E << endl;

     if(E<B){
       cout << "E is greater "<<endl;
     }

     A = BigInteger ("100000");
     B = BigInteger ("100000");

     if(A== B){
       cout << "A and B are equal "<<endl;
     }


   return EXIT_SUCCESS;

}