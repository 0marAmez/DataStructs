/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA6
* List.cpp
* Definition of functions in List.h
*********************************************************************************/
#include<iostream>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------
List::List(){
      Node*f = new Node(10000);
      Node*b = new Node(-1000);
      frontDummy = f;
      backDummy = b;
      frontDummy->next = backDummy;
      backDummy->prev = frontDummy;
      beforeCursor = nullptr;
      afterCursor = nullptr;
      pos_cursor = 0;
      num_elements = 0;
}

List::List(const List& L){
      Node*f = new Node(1000);
      Node*b = new Node(-1000);
      frontDummy = f;
      backDummy = b;
      frontDummy->next = backDummy;
      backDummy->prev = frontDummy;
      beforeCursor = nullptr;
      afterCursor = nullptr;
      pos_cursor = 0;
      num_elements = 0;
      Node*N = L.backDummy->prev;
      while(N->prev!=nullptr){
        this->insertAfter(N->data);
        N = N->prev;
      }

} 
List::~List(){
  moveFront();
  while(this->position() < this->length()){
    this->eraseAfter();
  }

  frontDummy->next = nullptr;
  frontDummy->prev = nullptr;
  backDummy->next = nullptr;
  backDummy->prev = nullptr;
  delete frontDummy;
  delete backDummy;

}


   // Access functions --------------------------------------------------------
int List::length() const{
    return(this->num_elements);
}

ListElement List::front() const{
    if(this->num_elements == 0){
      throw std::length_error("**List error: front() empty List");
    }
    else{
        return this->frontDummy->next->data;
    }
}

ListElement List::back() const{
    if(this->num_elements == 0){
      throw std::length_error("**List error: back() empty List");
    }
    else{
        return this->backDummy->prev->data;
    }
}

int List::position() const{
    if(pos_cursor<0 && pos_cursor>num_elements){
      throw std::range_error("**List error: position() List");
    }
    else{
            return(this->pos_cursor);
    }
}

ListElement List::peekNext() const{
    if(pos_cursor<num_elements){
          return afterCursor->data;
    }
    else{
      throw std::range_error("**List error: peekNext() List");
    }
}

ListElement List::peekPrev() const{
    if(pos_cursor>0){
          return beforeCursor->data; 
    }
    else{
      throw std::range_error("**List error: peekPrev() List");
    }
}

void List::clear(){
  Node*temp;
  Node*head = frontDummy->next;
    while(head->next != nullptr){
      temp = head;
      head = head->next;
      temp->next =nullptr;
      temp->prev=nullptr;
      delete temp;
    }
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront(){
  beforeCursor = frontDummy;
  afterCursor = beforeCursor->next;
  pos_cursor = 0;
}

void List::moveBack(){
  beforeCursor = backDummy->prev;
  afterCursor = backDummy;
  pos_cursor = num_elements;
}

ListElement List::moveNext(){
  ListElement x;
  if(this->position()<this->length()){
      x = afterCursor->data;
      afterCursor = afterCursor->next;
      beforeCursor = beforeCursor->next; 
      pos_cursor++;
      return x;
  }
  else{
    throw std::range_error("**List error: moveNext() List");
  }
}

ListElement List::movePrev(){
  ListElement x;
  if(pos_cursor>0){
    x = beforeCursor->data;
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return x;
  }
  else{
    throw std::range_error("**List error: movePrev() List");
  }
}

void List::insertAfter(ListElement x){
  Node*N = new Node(x);
  if(num_elements==0){
      frontDummy->next = N;
      N->prev = frontDummy;
      N->next = backDummy;
      backDummy->prev = N;
      beforeCursor = frontDummy;
      afterCursor = N;
      num_elements++;
  }
  else if(num_elements!=0 && afterCursor == backDummy){
      beforeCursor->next = N;
      N->prev = beforeCursor;
      backDummy->prev = N;
       N->next = backDummy;
      afterCursor = N;
      num_elements++; 
  }
  else {
          afterCursor->prev = N;
          N->next = afterCursor;
          beforeCursor->next = N;
          N->prev = beforeCursor;
          afterCursor = N;
          num_elements++; 
  }
}

void List::insertBefore(ListElement x){
    Node*N = new Node(x);
    if(num_elements==0){
        frontDummy->next = N;
        frontDummy->next->prev = frontDummy;
        frontDummy->next->next = backDummy;
        backDummy->prev = N;
        beforeCursor = N;
        afterCursor = backDummy;
        num_elements++;
        pos_cursor++;
    }
    else if (num_elements!=0 && beforeCursor == frontDummy){
        afterCursor->prev = N;
        N->next = afterCursor;
        frontDummy->next = N;
        N->prev = frontDummy;
        beforeCursor = N;
        num_elements++;
        pos_cursor++;
    }
    else{
          beforeCursor->next = N;
          N->prev = beforeCursor;
          afterCursor->prev = N;
          N->next = afterCursor;
          beforeCursor = N;
          num_elements++; 
          pos_cursor++;
    }
}

void List::setAfter(ListElement x){
  if(pos_cursor < num_elements && afterCursor!=backDummy){
    afterCursor->data = x;
  }
  else{
        throw std::range_error("**List error: setAfter() List");
  }
}

void List::setBefore(ListElement x){
  if(pos_cursor > 0 && beforeCursor!=frontDummy){
    beforeCursor->data = x;
  }
  else{
        throw std::range_error("**List error: setBefore() List");
  }
}

void List::eraseAfter(){
  Node*temp;
  if(pos_cursor < num_elements && afterCursor!=backDummy){
    temp = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev =beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    delete temp;
  }
  else{
        throw std::range_error("**List error: eraseAfter() List");
  }
}

void List::eraseBefore(){
  Node*temp;
  if(pos_cursor > 0 && beforeCursor!=frontDummy){
    temp = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    num_elements--;
    pos_cursor--;
    delete temp;
  }
  else{
        throw std::range_error("**List error: eraseBefore() List");
  }
}

int List::findNext(ListElement x){
  // this->moveFront();
      while(pos_cursor < num_elements){
        if(this->moveNext() == x){
          return this->position();
        }
      }
      this->moveBack();
      return -1;
}

int List::findPrev(ListElement x){
  while(this->position()>0){
    if(this->movePrev() == x){
      return this->position();
    }
  }
  this->moveFront();
  return -1;
}

void List::cleanup(){
  int pos = pos_cursor;
  int i =0;
  int j;
  Node* inner;
  Node* outer;
  Node* temp;
  Node* bef;
  Node* aft;

  for(outer=this->frontDummy->next; outer->next!=nullptr; outer=outer->next){
        inner = outer ->next;
        j= i +1;
        while(inner->next!=nullptr){
          if (inner->data== outer->data && inner == afterCursor ){
                temp = afterCursor;
                afterCursor = afterCursor->next;
                afterCursor->prev = beforeCursor;
                beforeCursor->next = afterCursor;
                inner = inner->next;
                j++;
                num_elements--;
                delete temp;
          }
          else if (inner->data== outer->data && inner == beforeCursor){
                temp = beforeCursor;
                beforeCursor = beforeCursor->prev;
                beforeCursor->next = afterCursor;
                afterCursor->prev = beforeCursor;
                inner = inner->next;
                j++;
                num_elements--;
                pos_cursor--;
                delete temp;
          }
          else if (inner->data== outer->data && !(j>pos) ){
                temp = inner;
                bef = inner->prev;
                aft = inner->next;
                bef->next= aft;
                aft->prev = bef;
                inner = inner->next;
                j++;
                num_elements--;
                pos_cursor--;
                delete temp;
          }
          else if(inner->data == outer->data){
                  temp = inner;
                  bef = inner->prev;
                  aft = inner->next;
                  bef->next= aft;
                  aft->prev = bef;
                  inner = inner->next;
                  j++;
                  num_elements--;
                  delete temp;
          }
          else{
            inner = inner->next;
            j++;
          }
        }
       i++;
    } 
}


   List List::concat(const List& L) const{
        List J;
        Node* N = this->frontDummy->next;
        Node* M = L.frontDummy->next;
        while( N->next!=nullptr ){
            J.insertBefore(N->data);
            N = N->next;
        }
        while( M->next!=nullptr ){
            J.insertBefore(M->data);
            M = M->next;
        }
        J.moveFront();
        return J;
   }


std::string List::to_string() const{
  Node* N = nullptr;
  std::string s = "(";
      for(N=frontDummy->next; N->next!=nullptr; N=N->next){
          if(N->next->next!=nullptr){
              s += std::to_string(N->data)+", ";
          }
          else{
              s += std::to_string(N->data);
          }
      }
      s+=")";
   return s;
}

bool List::equals(const List& R) const{
   bool eq = false;
   Node* N = nullptr;
   Node* M = nullptr;

   eq = ( this->num_elements == R.num_elements);
   N = this->frontDummy->next;
   M = R.frontDummy->next;
   while( eq && N->next!=nullptr){
      eq = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return eq;
}

std::ostream& operator<<( std::ostream& stream, const List& L ){
  return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ){
  return A.List::equals(B);
}

 List& List::operator=( const List& L ){
   if( this != &L ){ 
      List temp = L;

      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(beforeCursor, temp.beforeCursor);
      std::swap(afterCursor, temp.afterCursor);
      std::swap(pos_cursor, temp.pos_cursor);
      std::swap(num_elements, temp.num_elements);
   }

   return *this;
 }