/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA8
* Dictionary.cpp
* Dictionary.h definitions
*********************************************************************************/
#include "Dictionary.h"
// Private Constructor --------------------------------------------------------
int RED = 1;
int BLACK = 2;
int UNDEF = -1;
// Node constructor
   Dictionary::Node::Node(keyType k, valType v){
      key = k;
      val = v;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
      color =  UNDEF;
   }
   void Dictionary::inOrderString(std::string& s, Node* R) const{
      std::string s1;
         if( R!= nil){
            inOrderString(s,R->left);
            s+=R->key;
            s+=" : ";
            s1 = std::to_string(R->val);
            s+= s1;
            s+="\n";
            inOrderString(s,R->right);
         }
   }

   void Dictionary::preOrderString(std::string& s, Node* R) const{
      if(R!= nil){
         s+= R->key;
         s+="\n";
         preOrderString(s, R->left);
         preOrderString(s, R->right);
      }
   }

   void Dictionary::preOrderCopy(Dictionary& D,Node* R, Node* N){
      if(R!= N){
         D.setValue(R->key, R->val);
         preOrderCopy(D,R->left, N);
         preOrderCopy(D,R->right, N);
      }
   }

   void Dictionary::postOrderDelete(Node* R){
      if(R!= nil){
         postOrderDelete(R->left);
         postOrderDelete(R->right);
         delete R;
         num_pairs--;
      }
   }

   Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
         if( R == nil || k == R->key ){
            return R;
         } 
         else if(k < R->key){
            return search(R->left, k);
         } 
         else{
            return search(R->right, k);
         } 
   }

   Dictionary::Node* Dictionary::findMin(Node* R){
      Node*temp = nil;
      if(size()>0){
         while(R->left != nil){
            R =  R->left;
         }
         temp = R;
      }
      return temp;
   }

   Dictionary::Node* Dictionary::findMax(Node* R){
      Node*temp = nil;
      if(size()>0){
         while(R->right != nil){
            R = R->right;
         }
         temp = R;
      }
      return temp;
   }

   Dictionary::Node* Dictionary::findNext(Node* N){
      if(N->right != nil){
         return findMin(N->right);
      }
      else{
         Node*y = N->parent;
         while( y != nil &&  N == y->right){
            N = y;
            y = y->parent;
         }
         return y;
      }
   }

   Dictionary::Node* Dictionary::findPrev(Node* N){
      if(N->left != nil){
         return  findMax(N->left);
      }
      else{
            Node*y = N->parent;
            while( y != nil &&  N == y->left){
               N = y;
               y = y->parent;
            }
         return y;
      }
   }

      // RBT Helper Functions (Optional) -----------------------------------------
   
   // LeftRotate()
   void Dictionary::LeftRotate(Node* N){
      Node*y = N->right;
      N->right = y->left;
      if(y->left != nil){
         y->left->parent = N;
      }
      y->parent = N->parent;
      if(N->parent == nil){
         root = y;
      }
      else if (N == N->parent->left){
         N->parent->left = y;
      }
      else{
         N->parent->right = y;
      }
      y->left = N;
      N->parent = y;
   }

   // RightRotate()
   void Dictionary::RightRotate(Node* N){
      Node*y = N->left;
      N->left = y->right;
      if(y->right != nil){
         y->right->parent = N;
      }
      y->parent = N->parent;
      if( N->parent == nil){
         root = y;
      }
      else if( N == N->parent->right){
         N->parent->right = y;
      }
      else{
         N->parent->left = y;
      }
      y->right = N;
      N->parent = y;
   }

   // RB_InsertFixUP()
   void Dictionary::RB_InsertFixUp(Node* N){
      Node*y;
   while (N->parent->color == RED){
      if (N->parent == N->parent->parent->left){
         y = N->parent->parent->right;
         if (y->color == RED && y!=nil){
            N->parent->color = BLACK ;             // case 1
            y->color = BLACK ;                    // case 1
            N->parent->parent->color = RED;         // case 1
            N = N->parent->parent;
          }                                        // case 1
         else{ 
            if (N == N->parent->right){
               N = N->parent;                     // case 2
               LeftRotate( N);                 // case 2
            }   
            N->parent->color = BLACK;              // case 3
            N->parent->parent->color = RED;         // case 3
            RightRotate( N->parent->parent);     // case 3
         }
      }     
      else{ 
         y = N->parent->parent->left;
         if (y->color == RED && y != nil){
            N->parent->color = BLACK ;             // case 4
            y->color = BLACK;                     // case 4
            N->parent->parent->color = RED;         // case 4
            N = N->parent->parent;                 // case 4
         }   
         else{ 
            if (N == N->parent->left){
               N = N->parent;                     // case 5
               RightRotate(N);                // case 5
            }   
            N->parent->color = BLACK;              // case 6
            N->parent->parent->color = RED;         // case 6
            LeftRotate(N->parent->parent);      // case 6
         }
      }
   }         
   root->color = BLACK;
   }
   // RB_Transplant()
   void Dictionary::RB_Transplant(Node* u, Node* v){
      if(u->parent == nil){
         root = v;
      }
      else if (u == u->parent->left){
         u->parent->left = v;
      }
      else{
         u->parent->right = v;
      }
      v->parent = u->parent;
   }

   // RB_DeleteFixUp()
   void Dictionary::RB_DeleteFixUp(Node* N){
      Node*w;
      while( N != root && N->color == BLACK){
         if( N == N->parent->left){
            w = N->parent->right;
            if( w->color == RED){
               w->color = BLACK;
               N->parent->color = RED;
               LeftRotate(N->parent);
               w = N->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                  w->color = RED;
                  N = N->parent;
             }
            else{
               if(w->right->color == BLACK){
                  w->left->color = BLACK;
                  w->color = RED;
                  RightRotate(w);
                  w = N->parent->right;
               } 
              w->color = N->parent->color;
              N->parent->color = BLACK;
              w->right->color = BLACK;
              LeftRotate(N->parent);
              N = root;     
            }
         }
         else{
            w = N->parent->left;
            if(w->color == RED){
               w->color = BLACK;
               N->parent->color = RED;
               RightRotate(N->parent);
               w = N->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
               w->color = RED;
               N = N->parent;
            }
            else{
               if( w->left->color == BLACK){
                  w->right->color = BLACK;
                  w->color = RED;
                  LeftRotate(w);
                  w = N->parent->left;
               }
              w->color = N->parent->color;
              N->parent->color = BLACK;
              w->left->color = BLACK;
              RightRotate(N->parent);
              N = root; 
            }
         }

      }
     N->color = BLACK;
   }

   // RB_Delete()
   void Dictionary::RB_Delete(Node* N){
      Node*x;
      Node*y = N;
      int y_original_color = y->color;
      if(N->left == nil){
         x = N->right;
         RB_Transplant(N, N->right);
      }
      else if ( N->right == nil){
         x = N->left;
         RB_Transplant(N,N->left);
      }
      else{
         y = findMin(N->right);
         y_original_color = y->color;
         x = y->right;
         if(y->parent == N){
            x->parent = y;
         }
         else{
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent = y;
         }
         RB_Transplant(N,y);
         y->left = N->left;
         y->left->parent = y;
         y->color = N->color;
      }
     if(y_original_color == BLACK){
        RB_DeleteFixUp(x);
     }
   }

   Dictionary::Dictionary(){
         nil = new Node("/1000",-10000);
         root = current =  nil;
         num_pairs = 0;      
   }

   Dictionary::Dictionary(const Dictionary& D){
         nil = new Node("/1000",-10000);
         root = current =  nil;
         num_pairs = 0;      
         preOrderCopy(*this,D.root, D.nil);
   }

   Dictionary::~Dictionary(){
       this->clear();
       root = current = nullptr;
       delete nil;
   }

   int Dictionary::size() const{
      return num_pairs;
   }

   bool Dictionary::contains(keyType k) const{
       Node*x = search(root, k);
       if (x == nil){
          return false;
       }
       else{
          return true;
       }
   }

   valType& Dictionary::getValue(keyType k) const{
      Node*x; 
         if(this->contains(k)== false){
             throw std::logic_error("**Error_Dictionary_getValue(); Key "+ k + " does not exist on the tree.");
         }
         else{
            x =  search(root, k);
            return x->val;
         }
   }

   bool Dictionary::hasCurrent() const{
      if(current == nil){
         return false;
      }
      else{
         return true;
      }
   }

   keyType Dictionary::currentKey() const{
      if(this->hasCurrent()== false){
             throw std::logic_error("**Error_Dictionary_currentKey(): Current has not being defined.");
      }
      else{
         return current->key;
      }
   }

   valType& Dictionary::currentVal() const{
      if(this->hasCurrent()== false){
             throw std::logic_error("**Error_Dictionary_currentVal(): Current has not being defined.");
      }
      else{
         return current->val;
      }
   }

   void Dictionary::clear(){
       current = nil;
       postOrderDelete(root);
       root = nil;
   }

   void Dictionary::setValue(keyType k, valType v){
      Node*y = nil;
      Node*x = root;
      while(x != nil){
            y = x;
            if (k == x->key){
               x->val = v;
               return;
            }  
            else if(k < x->key){ 
               x = x->left;
            }
            else{ 
               x = x->right;
            }
     }
         Node*z = new Node(k,v);
         z->parent = y;
         if(y == nil){
            root = z;
         }
         else if (k < y->key){
            y->left = z;
         }
         else{
            y->right = z;
         }
         num_pairs++;
         z->right = nil;
         z->left = nil;
         z->color = RED;
         RB_InsertFixUp(z);   
   }

   void Dictionary::remove(keyType k){
      if(contains(k)== false){
            throw std::logic_error("**Error_Dictionary_remove(): KeyType '"+k+"' does not exist.");
      }
      else{
            Node*z = search(root, k);
            if(current == z){
               current = nil;
            }
            RB_Delete(z);
            num_pairs--;
            delete z;
      }
   }

   void Dictionary::begin(){
      if(this->size()==0){
            throw std::logic_error("**Error_Dictionary_begin(): Current can't be defined on empty list.");
      }
      else{
         if(root->left == nil){
            current = root;
         }
         else{
            current = findMin(root->left);
         }
      }
   }

   void Dictionary::end(){
      if(this->size()==0){
            throw std::logic_error("**Error_Dictionary_end(): Current can't be defined on empty list.");
      }
      else{
         if(root->right == nil){
            current = root;
         }
         else{
            current = findMax(root->right);
         }       
      }
   }

   void Dictionary::next(){
      if(this->hasCurrent() == false){
         throw std::logic_error("**Error_Dictionary_next(): Current not defined");
      }
      else{
            current = findNext(current);
      }
   }

   void Dictionary::prev(){
      if(this->hasCurrent() == false){
         throw std::logic_error("**Error_Dictionary_next(): Current not defined");
      }
      else{
            current = findPrev(current);        
      }
   }

   std::string Dictionary::to_string() const{
      std::string s1;
      inOrderString(s1, root);
      return s1; 
   }

   std::string Dictionary:: pre_string() const{
      std::string s1;
      preOrderString(s1, root);
      return s1;
   }

   bool Dictionary::equals(const Dictionary& D) const{
         std::string s1 = this->pre_string();
         std::string s2 = D.pre_string();
         if(s1 == s2){
            return true;
         }
         else{
            return false;
         }
   }

   bool operator==( const Dictionary& A, const Dictionary& B ){
         return A.Dictionary::equals(B);
   }

   std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
        return stream << D.Dictionary::to_string();
   }

   Dictionary&  Dictionary::operator=( const Dictionary& D ){
      if( this != &D ){ 
      Dictionary temp = D;
      std::swap(root, temp.root);
      std::swap(current, temp.current);
      std::swap(num_pairs, temp.num_pairs);
      std::swap(nil,temp.nil);
   }
   // return this with the new data installed
     return *this;
   }