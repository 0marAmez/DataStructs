/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA8
* DictionaryTest.cpp
* Dictionary testing area
*********************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){

 Dictionary A;
   Dictionary B;
   //SPANISH DICTIONARY
   A.setValue("Flor" ,1);
   A.setValue("Bolsa" ,2);
   A.setValue("Arepa" ,3);
   A.setValue("Durango" ,4);
   A.setValue("Corazon" ,5);
   A.setValue("Elefante" ,6);
   A.setValue("Gato" ,7);
   A.setValue("Inteligente" ,8);
   A.setValue("Hielo" ,9);

   //PORTUGUESE DICTIONARY

   B.setValue("Fabela" ,1);
   B.setValue("Bahia" ,2);
   B.setValue("Amapa" ,3);
   B.setValue("Doce" ,4);
   B.setValue("coracao" ,5);
   B.setValue("Elefante" ,6);
   B.setValue("Gato" ,7);
   B.setValue("Inteligente" ,8);
   B.setValue("Gelo" ,9);

   cout << "Size of Spanish Dictionary: " <<A.size() << endl;
   cout << "In order print: \n";
   cout << A << endl;

   cout << "Size of Portuguse Dictionary: " << B.size() << endl;
   cout << "In order print: \n";
   cout << B << endl;

   cout << "A  preorder print: \n";
   cout << A.pre_string() << endl;

   cout << "B  preorder print: \n";
   cout << A.pre_string() << endl;


   if(A.contains("fala")==false){
      cout << "fala is not part of the Spanish Dictionary" << endl;
   }

   if(B.contains("habla")==false){
      cout << "habla is not part of the Portuguese Dictionary" << endl;
   }

   // Change values
      A.setValue("Gato" ,99);
      B.setValue("Gato" ,99);

      cout << A << endl;
      cout << B << endl;

      B.clear();

      cout << B.size() << endl;
      B = A ;
      cout << B.size() << endl;
      cout << B << endl;
      if(A==B){
         cout << "They are equal!" << endl;
      }
      B.clear();
      
      B.setValue("Gelo" ,9);
      B.setValue("Inteligente" ,8);
      B.setValue("Gato" ,7);
      B.setValue("Elefante" ,6);
      B.setValue("coracao" ,5);
      B.setValue("Doce" ,4);
      B.setValue("Amapa" ,3);
      B.setValue("Bahia" ,2);
      B.setValue("Fabela" ,1);

      cout << B << endl;
      cout << B.pre_string() << endl;


      A.begin();
      B.begin();
      if(A.hasCurrent()&& B.hasCurrent()){
         cout << "Defined " << endl;
      }
      // A.remove("Mexico");
      // B.remove("Brazil");
      A.setValue("Mexico" , 10);
      B.setValue("Brazil",10);

      A.remove("Gato");
      B.remove("Gato");
      A.remove("Elefante");
      B.remove("Elefante");

      cout << A << endl;
      cout << B << endl;

      A.setValue("Pozole" , 11);
      A.setValue("Vallarta" , 11);
      B.setValue("Picanha",10);
      B.setValue("Ipanema",11);


   for(A.begin(); A.hasCurrent(); A.next()){
      A.currentVal()*=10;
      cout << "Key: " << A.currentKey()<< " ---- " << "Value : " << A.currentVal() << endl;
   }

   cout<< endl;

   for(B.end(); B.hasCurrent(); B.prev()){
      B.currentVal()*=10;
      cout << "Key: " << B.currentKey()<< " ---- " << "Value : " << B.currentVal() << endl;
   }

   cout << endl;
   cout << A << endl;
   cout << B << endl;



   return( EXIT_SUCCESS );
}