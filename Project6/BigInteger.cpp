/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA6
* BigInteger.cpp
* Definition of functions in BigInteger.h
*********************************************************************************/
#include<stdexcept>
#include <math.h>   
#include"BigInteger.h"
// base is from 1,2,3,4,5,6,7,8,9  
unsigned int power = 9;
long base = pow(10,power);

// HELPERS DEFINITION
bool isInteger(std::string s);
List createList(std::string s);
void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
ListElement carry_Count(ListElement x);
int normalizeList(List& L);
void scalarMultList(List& L, ListElement x);
void shiftList(List& L,int p);
List multHelper (List  A, List B);



 // Class Constructors & Destructors ----------------------------------------

  // BigInteger()
  // Constructor that creates a new BigInteger in the zero state:
  // signum=0, digits=().
 BigInteger::BigInteger(){
     signum = 0;
 }
  // BigInteger()
  // Constructor that creates a new BigInteger from the string s.
  // Pre: s is a non-empty string consisting of (at least one) base 10 digit
  // {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
 BigInteger::BigInteger(std::string s){
        if(s.empty()){
            throw std::invalid_argument("**BigInteger: Constructor: empty string");
        }
        else if (isInteger(s) == false){
            throw std::invalid_argument("**BigInteger: Constructor: non-numeric string");
        }
        else if ( s[0] == '-' ){
            digits = createList(s);
            signum = -1;
        }
        else{
            digits = createList(s);
            signum = 1;
        }
 }

   // BigInteger()
  // Constructor that creates a copy of N.
  BigInteger::BigInteger(const BigInteger& N){
     this->signum = N.sign();
     this->digits = N.digits;
  }
 
  // Access functions --------------------------------------------------------
 
  // sign()
  // Returns -1, 1 or 0 according to whether this BigInteger is positive,
  // negative or 0, respectively.
 int BigInteger::sign() const{
     return signum;
 }

  // compare()
 // Returns -1, 1 or 0 according to whether this BigInteger is less than N,
 // greater than N or equal to N, respectively.
 int BigInteger::compare(const BigInteger& N) const{
     BigInteger i1 = *this;
     BigInteger i2 = N;
     std::string s1 = i1.BigInteger::to_string();
     std::string s2 = i2.BigInteger::to_string();
     int x = 0;
     if(s1.compare(s2)>0){
         x = 1;
         return x;
     }
     else if(s1.compare(s2)<0){
         x = -1;
         return x;
     }
     else{
         return x;
     }
 }

  // Manipulation procedures -------------------------------------------------
 
 // makeZero()
 // Re-sets this BigInteger to the zero state.
  void BigInteger::makeZero(){
      digits.clear();
      signum = 0;
  }


// negate()
 // If this BigInteger is zero, does nothing, otherwise reverses the sign of
 // this BigInteger positive <--> negative.
 void BigInteger::negate(){
     if(signum == 1){
         signum = -1;
     }
     else if (signum == -1){
         signum = 1;
     }
     else{
         return;
     }
 }

// to_string()
 // Returns a string representation of this BigInteger consisting of its
 // base 10 digits. If this BigInteger is negative, the returned string
 // will begin with a negative sign '-'. If this BigInteger is zero, the
 // returned string will consist of the character '0' only.
 std::string BigInteger::to_string(){
      std::string temp;
      std::string str;
      ListElement x;
      if(signum == -1){
          str+="-";
          digits.moveFront();
          x = digits.moveNext();
          temp = std::to_string(x);
          str+=temp;
          temp.clear();
          while(digits.position() < digits.length()){
              x = digits.moveNext();
              temp = std::to_string(x);
              while(temp.length()<power){
                  temp.insert (0,1,'0');
              }
              str+=temp;
              temp.clear();
          }
        return str;
      }
      else if (signum == 0){
          str+="0";
          return str;
      }
      else{
          digits.moveFront();
          x = digits.moveNext();
          temp = std::to_string(x);
          str+=temp;
          temp.clear();
          while(digits.position() < digits.length()){
              x = digits.moveNext();
              temp = std::to_string(x);
              while(temp.size()<power){
                  temp.insert (0,1,'0');
              }
              str+=temp;
              temp.clear();
          }
        return str;
      }
 }

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger temp;
    if(this->sign() == 0 && N.sign() != 0){
        temp.signum = N.sign();
        temp.digits = N.digits;
    }
    else if (this->sign() != 0 && N.sign() == 0){
        temp.signum = this->sign();
        temp.digits = this->digits;
    }
    else if (this->sign() == -1 && N.sign() == 1){
        if(this->digits == N.digits){
            temp.signum = 0;
        }
        else{
            sumList(temp.digits, N.digits, this->digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    }
    else if (this->sign() == -1 && N.sign() == 1){
        if(this->digits == N.digits){
            temp.signum = 0;
        }
        else{
            sumList(temp.digits, N.digits, this->digits, -1);
            temp.signum = normalizeList(temp.digits);
        }
    }
    else if(this->sign() == 1 && N.sign() == -1){
        if(this->digits == N.digits){
            temp.signum = 0;
        }
        else{
            sumList(temp.digits,this->digits, N.digits ,-1);
            temp.signum = normalizeList(temp.digits);
        }
    }
    else if (this->sign() == 0 && N.sign() == 0){
        temp.signum = 0;
    }
    else if ((this->sign() == -1 && N.sign() == -1)){
        sumList(temp.digits,this->digits, N.digits ,1);
        normalizeList(temp.digits);
        temp.signum = -1;
    }
    else{
        sumList(temp.digits,this->digits, N.digits ,1);
        temp.signum = normalizeList(temp.digits);
    }
    return temp;
}

// sub()
  // Returns a BigInteger representing the difference of this and N.
  BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger temp;
    if(this->sign() == 0 && N.sign() != 0){
        temp.signum = -1;
        temp.digits = N.digits;
    }
    else if (this->sign() != 0 && N.sign() == 0){
        temp.signum = this->sign();
        temp.digits = this->digits;
    }
    else if (this->sign() == 0 && N.sign() == 0){
        temp.signum = 0;
    }
    else if (this->sign() == -1 && N.sign() == 1){
            sumList(temp.digits,this->digits, N.digits ,1);
            normalizeList(temp.digits);
            temp.signum = -1;
    }
    else if (this->sign() == 1 && N.sign() == -1){
        sumList(temp.digits,this->digits, N.digits ,1);
        normalizeList(temp.digits);
        temp.signum = 1;
    }
    else if (this->sign() == -1 && N.sign() == -1){
      if(this->digits == N.digits){
            temp.signum = 0;
      } 
      else{
        sumList(temp.digits,this->digits, N.digits ,-1);
        temp.signum = normalizeList(temp.digits)*-1;
      }
    }
    else {
        if(this->digits == N.digits){
            temp.signum = 0;
        }
        else if (this->digits.length() > N.digits.length()){
            sumList(temp.digits,this->digits, N.digits ,-1);
            normalizeList(temp.digits);
            temp.signum = 1;
        }
        else if (this->digits.length() < N.digits.length()){
            sumList(temp.digits,N.digits, this->digits ,-1);
            normalizeList(temp.digits);
            temp.signum = -1;
        }
        else if (this->digits.length() == N.digits.length() && this->digits.front()>N.digits.front()) {
            sumList(temp.digits,N.digits, this->digits ,-1);
            normalizeList(temp.digits);
            temp.signum = 1;
        }
        else if (this->digits.length() == N.digits.length() && this->digits.front()<N.digits.front()) {
            sumList(temp.digits,N.digits, this->digits ,-1);
            normalizeList(temp.digits);
            temp.signum = -1;
        }
        else{
            sumList(temp.digits,this->digits, N.digits ,-1);
            temp.signum = normalizeList(temp.digits);
        }
    }
    return temp;
  }

    // mult()
  // Returns a BigInteger representing the product of this and N.
  BigInteger BigInteger::mult(const BigInteger& N) const{
       BigInteger temp;        
       if((this->sign() == 0 && N.sign()!=0) || (this->sign() != 0 &&N.sign()==0) || (this->signum == 0 && N.sign()==0)){
           temp.signum = 0;
       }
       else if((this->signum == 1 && N.sign()== -1) || (this->signum == -1 && N.sign()== 1)){
                temp.signum = -1;
                if(this->digits.length() > N.digits.length()){
                   temp.digits = multHelper(this->digits, N.digits);
                }
                else if (this->digits.length() < N.digits.length()){
                    temp.digits = multHelper(N.digits,this->digits);
                }
                else{
                    temp.digits = multHelper(this->digits, N.digits);
                }
       }
       else{
                temp.signum = 1;
                if(this->digits.length() > N.digits.length()){
                   temp.digits = multHelper(this->digits, N.digits);
                }
                else if (this->digits.length() < N.digits.length()){
                    temp.digits = multHelper(N.digits,this->digits);
                }
                else if (this->digits.length() == N.digits.length() && this->digits.front() < N.digits.front() ) {
                    temp.digits = multHelper( N.digits, this->digits);
                }
                else{
                    temp.digits = multHelper(this->digits, N.digits);
                }                
       }
        return temp;
  }


std::ostream& operator<<( std::ostream& stream, BigInteger N ){
      return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ){
      if(A.compare(B)==0){
           return true;
      }
      else{
          return false;
      }
}
 
  bool operator<( const BigInteger& A, const BigInteger& B ){
      if(A.compare(B)==-1){
          return true;
      }
      else{
          return false;
      }
  }
 
  bool operator<=( const BigInteger& A, const BigInteger& B ){
       if(A.compare(B)== -1 || A.compare(B) == 0){
          return true;
      }
      else{
          return 0;
      }
  }
 
   bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B)== 1){
          return true;
      }
      else{
          return false;
      }
   }
 
   bool operator>=( const BigInteger& A, const BigInteger& B ){
       if(A.compare(B) == 1 && A.compare(B)==0){
          return true;
      }
      else{
          return false;
      }
   }
 
  BigInteger operator+( const BigInteger& A, const BigInteger& B ){
      BigInteger c = A.add(B);
      return c;
  }

  BigInteger operator+=( BigInteger& A, const BigInteger& B ){
      BigInteger c = A.add(B);
      A.signum = c.signum;
      A.digits = c. digits;
      return  A;
  }

 BigInteger operator-( const BigInteger& A, const BigInteger& B ){
       BigInteger c = A.sub(B);
      return c;
  }
  BigInteger operator-=( BigInteger& A, const BigInteger& B ){
       BigInteger c = A.sub(B);
      A.signum = c.signum;
      A.digits = c. digits;
      return  A;
  }

 BigInteger operator*( const BigInteger& A, const BigInteger& B ){
       BigInteger c =A.mult(B);
       return c;
   }
   BigInteger operator*=( BigInteger& A, const BigInteger& B ){
       BigInteger c =A.mult(B);
       A.signum = c.signum;
      A.digits = c. digits;
      return  A;
 
   }

 // HELPER FUNCTIONS DEFINITIONS
 bool isInteger(std::string s){
  if(s.length()== 1 && isdigit(s[0])==false){
       return false;
   } 
   else if(s[0]!= '+' && s[0] != '-' && isdigit(s[0])==false){
           return false;        
   }
   else{
        for(unsigned int i = 1;i<s.length();i++){ 
            if(isdigit(s[i])== false){
                return false;
            }
        }
      return true;
   }
}

List createList(std::string s){
    List hold;
    ListElement x;
    std::string temp;
    int condition;
    if(s[0] == '+' || s[0] == '-'){
          condition = 1;
    }
    else{
         condition = 0;
    }
    for (int i = s.size() - 1; i >= condition; i--) {
         if(temp.length() != power){
            temp.insert (0,1,s[i]);
          }
          else{
             x = std:: stol(temp);
             hold.insertAfter(x);
             temp.clear();
              temp.insert (0,1,s[i]);
          }
    }
     x = std:: stol(temp);
    hold.insertBefore(x);
    hold.moveFront();
    while(true){
        if(hold.front()==0 && hold.peekNext()==0){
              hold.eraseAfter();
        }
        else{
            break;
        }
    }
     if(hold.front()==0){
          hold.moveFront();
          hold.eraseAfter();
      }
    return hold;   
}
void negateList(List& L){
   List temp;
   L.moveBack();
   while(L.position()>0){
       temp.insertAfter(L.movePrev()*-1);
   }
   L = temp;
}
void sumList(List& S, List A, List B, int sgn){
   ListElement x;
   List temp;
   A.moveBack();
   B.moveBack();
    while(A.position()>0 || B.position()>0){
      if(B.position()==0 && A.position()!=0){
          x = A.movePrev();
          temp.insertAfter(x);
      }
      else if (B.position()!=0 && A.position()==0){
          x = (B.movePrev())*sgn;
          temp.insertAfter(x);
      }
      else{
          x = (A.movePrev())+((B.movePrev()*sgn));
          temp.insertAfter(x);
      }
    }
    while(true){
        if(temp.front()==0 && temp.peekNext()==0){temp.eraseAfter();}
        else{break;}
    }
    if(temp.front()==0){
        temp.moveFront();
        temp.eraseAfter();
     }
    S = temp;
}
ListElement carry_Count(ListElement x){
    ListElement c = x/base;
    if(x%base == 0 ){
        return c;
    }
    else if (x%base != 0 && c>0){
        return c;
    }
    else if (x%base != 0 && c<0){
         return (c-1);
    }
    else if (x%base == x && x>0){
        return 1;
    }
    else if (x%base == x && x<0){
        return -1;
    }
    else{
        return c;
    }

}
int normalizeList(List& L){
   ListElement x;
   List temp;
   bool carry  = false;
   bool borrow = false;
   int sign = 0;
   int c = 0;
   if(L.front()>0){sign = 1;}
   else{
       sign = -1;
       negateList(L);
   }
   L.moveBack();
   while(L.position()>0){
       x = L.movePrev();
       //ADDITION
       if(x>=base  && carry == true){
            x+=c;
            c = carry_Count(x);
            x-=((c)*(base));
            temp.insertAfter(x);
            carry = true;
       }
       else if (x>= base && carry ==  false){
            c = carry_Count(x);
            x -=((c)*(base));
            temp.insertAfter(x);
            carry = true;
       }
       else if (x< base && x>=0 && carry == true){
            x+= c;
           if(x>= base){
                c = carry_Count(x);
                x-= ((c)*(base));
                temp.insertAfter(x);
                carry = true;
           }
           else if(x<0){
                c = carry_Count(x);
                x+= ((c*-1)*(base));
                temp.insertAfter(x);
                carry = true;
           }
            else{
                  c = 0;
                  temp.insertAfter(x);
                  carry = false;
            }
       }
       //SUBTRACTION
       else if( x < 0  && borrow == true){
            x+= c;
            c =  carry_Count(x);
            x+= ((c*-1)*(base));
            temp.insertAfter(x);
            borrow = true;
       }
       else if (x < 0 && borrow == false){
           c =  carry_Count(x);
           x+= ((c*-1)*(base));
           temp.insertAfter(x);
           borrow = true;
       }
       else if ( x>= 0  && x<base && borrow == true){
           x+=c;
            if(x<0){
               c =  carry_Count(x);
               x+= ((c*-1)*(base));
               temp.insertAfter(x);
               borrow = true;
            }
            else if(x>=base){
                c = carry_Count(x);
                x-= ((c)*(base));
                temp.insertAfter(x);
                borrow = true;
            }
            else{
                 c = 0;
                 temp.insertAfter(x);
                 borrow = false;
            }
       }
       else{
            temp.insertAfter(x);
            carry = false;
            borrow = false;
            c = 0;
       }
   }
    while(true){
        if(temp.front()==0 && temp.peekNext()==0){temp.eraseAfter();}
        else{break;}
    }
    if(temp.front()==0){
        temp.moveFront();
        temp.eraseAfter();
     }
    if( (carry == true || borrow == true) && c!=0 ){temp.insertAfter(c);}
   L = temp;
  return sign;
}

void scalarMultList(List& L, ListElement x){
  List temp;
  ListElement y;
  L.moveBack();
  while(L.position()>0){
      y = x*L.movePrev();
      temp.insertAfter(y);

  }
   L = temp;
}
void shiftList(List& L,int p){
   int c = 0;
   L.moveBack();
   while(c<p){
       L.insertAfter(0);
       c++;
   }
}
List multHelper (List  A, List B){
   List temp = A;
   List product;
   int shift = 0;
   B.moveBack();
   while(B.position()>0){
       scalarMultList(temp, B.movePrev());
       shiftList(temp,shift);
       shift++;
       sumList(product,product,temp,1);
       normalizeList(product);
       temp = A;
   }
   return product;
}