/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA4
* Matrix.c
* Matrix definitions
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Matrix.h"


// structs --------------------------------------------------------------------
typedef struct EntryObj* Entry;
// private type
typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef struct MatrixObj {
    List* rows;
    int size;
    int nnz;
} MatrixObj;
void add_diff_helper (List A, List B, Matrix M ,int i ,int op );
double productHelper (List A, List B);
void InsertionSortList(List L, int col,double val);
bool inList(List L, int column);

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Entry object. Initializes next and data fields.
Entry newEntry(int col,double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->column = col;
    E->value = value;
    return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
void freeEntry(Entry* pE) { 
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n){
    int actualSize = n+1;
    Matrix M = malloc(sizeof(MatrixObj));
    M->rows = malloc(sizeof(List) * (actualSize));
    M->size = n;
    M->nnz = 0;
    for (int i = 1; i <= n; i++) {
        M->rows[i] = newList(); // allocates every column 
    } 
    
   return(M);   
}

void freeMatrix(Matrix* pM){
    List L;
    Entry E;
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= (size(*pM)); i++) {
            L = (*pM)->rows[i];
           if( length(L) != 0 ){
               for(moveFront(L);index(L)>=0;moveNext(L)){
                    E = ((Entry)get(L));
                   freeEntry(&E);
               }
            }
		  freeList(&L);
 		}
         free((*pM)->rows);
         free(*pM);
         *pM = NULL;
    }
}

int size(Matrix M){
    if(M==NULL){
		printf("**Matrix Error: calling getSize() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
   return(M->size); 
}

int NNZ(Matrix M){
    if(M==NULL){
		printf("**Matrix Error: calling NNZ() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
   return(M->nnz);  
}

int equals(Matrix A, Matrix B){
    double valueA;
    double valueB;
    if(A==NULL || B==NULL){
		printf("**Matrix Error: calling equals() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else if (size(A)!=size(B)){
        return 0;
    }
    else if (A==B){
        return 1;
    }
    else{
        for(int i = 1;i<=size(A);i++){
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            if(length(A->rows[i])!=length(B->rows[i])){
                return 0;
            }
             while(index(A->rows[i])>=0 && index(B->rows[i])>=0){
                    valueA = ((Entry)get(A->rows[i]))->value;
                    valueB = ((Entry)get(B->rows[i]))->value;
                    if(valueA!=valueB){
                        return 0;
                    }
                    moveNext(A->rows[i]);
                    moveNext(B->rows[i]);
                }
        }
        return 1;
    }
}

void makeZero(Matrix M){
    if(M==NULL){
		printf("**Matrix Error: calling makeZero() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else{
    List L;
    Entry E;
        for (int i = 1; i <= size(M); i++) {
            L = M->rows[i];
           if( length(L) != 0 ){
               for(moveFront(L);index(L)>=0;moveNext(L)){
                    E = ((Entry)get(L));
                    M->nnz--;
                   freeEntry(&E);
               }
               clear(L);
            }
 		}
    }
}

void changeEntry(Matrix M, int i, int j, double x){
Entry E = newEntry(j,x);
    if(M==NULL){
		printf("**Matrix Error: calling ChangeEntry() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else if (j>size(M) || i >size(M)){
        printf("**Matrix Error: exceeding limit of square matrix\n");
		exit(EXIT_FAILURE);
    }
    else if (NNZ(M)!=0){
            if (length(M->rows[i])==0 && x!=0.0){
                append(M ->rows[i],E);
                M->nnz++;
            }
            else if (length(M->rows[i])!=0 && x!=0.0){
                // printf("case2 \n");
                InsertionSortList(M->rows[i],j,x);
                M->nnz++;
                freeEntry(&E);
            }
            else if (length(M->rows[i])!=0 && x==0.0){
                List L = M->rows[i];
                Entry ptr;
                if(inList(L,j)==true){
                    for(moveFront(L);index(L)>=0;moveNext(L)){
                        ptr = ((Entry)get(L));
                        if(ptr->column == j){
                            M->nnz--;
                            freeEntry(&ptr);
                            delete(L);
                            break;
                        }
                    } 
                }
                freeEntry(&E);
            }
            else{
              freeEntry(&E);
                return;
            }
    }
    else{
        if(x!=0.0){
           append(M ->rows[i],E);
            M->nnz++;
        }
        else{
            freeEntry(&E); 
        }
    }
}
Matrix copy(Matrix A){
    if(A==NULL){
		printf("**Matrix Error: calling copy() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else{
        Matrix M = newMatrix(size(A));
        List tempA;
        int col;
        double value;
        for(int i = 1; i<= size(M);i++){
            tempA = A->rows [i]; 
            for(moveFront(tempA);index(tempA)>=0;moveNext(tempA)){
               col = ((Entry)get(tempA))->column;
               value = ((Entry)get(tempA))->value;
                changeEntry(M,i,col,value);

                
            }
        }
         return (M);
    }
}

Matrix transpose(Matrix A){
    if(A==NULL){
		printf("**Matrix Error: calling transpose() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else{
        Matrix M = newMatrix(size(A));
        List tempA;
        // Entry E;
        int col;
        double value;
        for(int i = 1; i<= size(M);i++){
            // tempM = M->rows[i];
            tempA = A->rows [i];
            for(moveFront(tempA);index(tempA)>=0;moveNext(tempA)){
               col = ((Entry)get(tempA))->column;
               value = ((Entry)get(tempA))->value;
                // E = ((Entry)get(tempA));
                changeEntry(M,col,i,value);
            }
        }
         return (M);
    }
}

Matrix scalarMult(double x, Matrix A){
    if(A==NULL){
		printf("**Matrix Error: calling scalarMult on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else{
        Matrix M = newMatrix(size(A));
        List tempA;
        int col;
        double value;
        for(int i = 1; i<= size(M);i++){
            tempA = A->rows [i]; 
            if(length(tempA)!=0){
                for(moveFront(tempA);index(tempA)>=0;moveNext(tempA)){
                    col = ((Entry)get(tempA))->column;
                    value = ((Entry)get(tempA))->value;
                    changeEntry(M,i,col,x*value); 
                }
            }
        }
         return (M);
    }
}

Matrix sum(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
		printf("**Matrix Error: calling sum() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else if (size(A)!= size(B)){
        printf("**Matrix Error: calling sum() on two different size Matrix\n");
		exit(EXIT_FAILURE);
    }
    else if (A==B){
        Matrix C = copy(A);
        Matrix S  = sum (A,C);
        freeMatrix(&C);
        return(S);
    }
    else{
        Matrix M = newMatrix(size(A));
        List tempA;
        List tempB;
       // List tempM;
        for(int i = 1; i <=size(A);i++){
            tempA = A->rows[i];
            tempB = B->rows[i];
            //tempM = M->rows[i];
            add_diff_helper (tempA,tempB, M ,i ,1 );   
        }
        return M;
    }
}

Matrix diff(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
		printf("**Matrix Error: calling diff() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else if (size(A)!= size(B)){
        printf("**Matrix Error: calling diff() on two different size Matrix\n");
		exit(EXIT_FAILURE);
    }
    else if (A==B){
        Matrix C = copy(A);
        Matrix S  = diff (A,C);
        freeMatrix(&C);
        return(S);
    }
    else{
        Matrix M = newMatrix(size(A));
        List tempA;
        List tempB;
       // List tempM;
        for(int i = 1; i <=size(A);i++){
            tempA = A->rows[i];
            tempB = B->rows[i];
            //tempM = M->rows[i];
            add_diff_helper (tempA,tempB, M ,i ,0 );   
        }
        return M;
    }

}

Matrix product(Matrix A, Matrix B){
    if(A==NULL || B==NULL){
		printf("**Matrix Error: calling prduct() on NULL Matrix reference\n");
		exit(EXIT_FAILURE);
    }
    else if (size(A)!= size(B)){
        printf("**Matrix Error: calling product() on two different size Matrix\n");
		exit(EXIT_FAILURE);
    }
    else if (A == B){
        Matrix C = copy(A);
        Matrix S  = product (A,C);
        freeMatrix(&C);
        return(S);
    }
    else{
        // Entry E;
        double x;
        Matrix M = newMatrix(size(A));
        Matrix T= transpose(B);
        List tempA;
        List tempT;
        for(int i = 1; i <=size(A);i++){
            tempA = A->rows[i];
            if(length(tempA)!=0){
                for(int j = 1;j<=size(A);j++){
                     tempT = T->rows[j];
                     x = productHelper(tempA,tempT);
                    changeEntry(M,i, j, x);
                }  
            }
        }
        
        freeMatrix(&T);
        return M;   
    }
}


void printMatrix(FILE* out, Matrix M){
    int j;
    double value;
    if(NNZ(M)==0){
        return;
    }
        for(int i = 1; i<=size(M);i++){
            if(length(M->rows[i])!=0){
            fprintf(out,"%d : ",i);
                for(moveFront(M->rows[i]);index(M->rows[i])>=0;moveNext(M->rows[i])){
                    j = ((Entry)get(M->rows[i]))->column;
                    value = ((Entry)get(M->rows[i]))->value;
                    fprintf(out," ( %d , %.1f )",j,value);
                    fprintf(out ," ");
                }   
            fprintf(out,"\n");
            }   
        }
}

void InsertionSortList(List L, int col,double value) {
 int j;
if(inList(L,col)==false){
    Entry E = newEntry(col,value);
    moveFront(L);
    j = ((Entry)get(L))->column;
	while (j < col && index(L)>=0) {
		moveNext(L);
		if (index(L) == -1) {
			append(L, E);
			break;
		}
		j = ((Entry)get(L))->column;
	}
	if (index(L) >= 0) {
		insertBefore(L, E);
	}
}
else{
    for (moveFront(L); index(L) >= 0; moveNext(L)) {
       j = ((Entry)get(L))->column;
	    if (j == col) {
			((Entry)get(L))->value = value; 
		}
	}
}
    

} 

bool inList(List L, int column) {
int j;
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
       j = ((Entry)get(L))->column;
		if (j == column) {
			return true;
		}
	}
	return false;
}


void add_diff_helper (List A, List B, Matrix M ,int i ,int op ){
    int col;
    double value;
    //Entry E;
    if(op ==1){
        if(length(A)==0 &&  length(B)!=0){
            for(moveFront(B);index(B)>=0;moveNext(B)){
                col = ((Entry)get(B))->column;
                value  = ((Entry)get(B))->value;
                changeEntry(M, i,col,value);
            }
        }
        else if (length(A)!=0 &&  length(B)==0){
            for(moveFront(A);index(A)>=0;moveNext(A)){
                col = ((Entry)get(A))->column;
                value  = ((Entry)get(A))->value;
                changeEntry(M, i,col,value);
            }   
        }
        else{ 
                int col_A;
                int col_B;
                double valueA;
                double valueB;
                moveFront(A);
                moveFront(B);
                while(index(A)!=-1 || index(B)!=-1){
                    if(index(A)==-1 && index(B)!=-1 ){
                        col_B=((Entry)get(B))->column;
                        valueB = ((Entry)get(B))->value;
                        changeEntry(M, i,col_B,valueB);
                        moveNext(B);
                    }
                    else if(index(A)!=-1 && index(B)==-1 ){
                        col_A=((Entry)get(A))->column;
                        valueA = ((Entry)get(A))->value;
                        changeEntry(M, i,col_A,valueA);
                        moveNext(A); 
                    }
                    else{
                            col_A=((Entry)get(A))->column;
                            col_B=((Entry)get(B))->column;
                            valueA = ((Entry)get(A))->value;
                            valueB = ((Entry)get(B))->value;
                            if(col_A<col_B){
                                changeEntry(M, i,col_A,valueA);
                                moveNext(A); 
                            }
                            else if (col_A>col_B){
                                changeEntry(M, i,col_B,valueB);
                                moveNext(B); 
                            }
                            else{
                                if(valueA+valueB !=0){
                                    changeEntry(M, i,col_A,(valueB+valueA));
                                }   
                                    moveNext(B); 
                                    moveNext(A);
                            }
                    }
                }
        }
    }
    else{
        if(length(A)==0 &&  length(B)!=0){
            for(moveFront(B);index(B)>=0;moveNext(B)){
                col = ((Entry)get(B))->column;
                value  = ((Entry)get(B))->value;
                changeEntry(M, i,col,((-1)*value));

            }
        }
        else if (length(A)!=0 &&  length(B)==0){
            for(moveFront(A);index(A)>=0;moveNext(A)){
                col = ((Entry)get(A))->column;
                value  = ((Entry)get(A))->value;
                changeEntry(M, i,col,value);
            }   
        }
        else{ 
                int col_A;
                int col_B;
                double valueA;
                double valueB;
                moveFront(A);
                moveFront(B);
                while(index(A)!=-1 || index(B)!=-1){
                    if(index(A)==-1 && index(B)!=-1 ){
                        col_B=((Entry)get(B))->column;
                        valueB = ((Entry)get(B))->value;
                        changeEntry(M, i,col_B,(-1)*valueB);
                        moveNext(B);
                    }
                    else if(index(A)!=-1 && index(B)==-1 ){
                        col_A=((Entry)get(A))->column;
                        valueA = ((Entry)get(A))->value;
                        changeEntry(M, i,col_A,valueA);
                        moveNext(A); 
                    }
                    else{        
                        col_A=((Entry)get(A))->column;
                        col_B=((Entry)get(B))->column;
                        valueA = ((Entry)get(A))->value;
                        valueB = ((Entry)get(B))->value;
                        if(col_A<col_B){
                            changeEntry(M, i,col_A,valueA);
                            moveNext(A); 
                        }
                        else if (col_A>col_B){
                            changeEntry(M, i,col_B,-1*valueB);
                            moveNext(B); 
                        }
                        else{  
                            if(valueA-valueB !=0){
                                changeEntry(M, i,col_A,(valueA-valueB));
                            }  
                            moveNext(B); 
                            moveNext(A); 
                        }
                    
                    }
                    

                }
        }
    }
}
double productHelper (List A, List B){
    int col_A;
    int col_B;
    double sum = 0;
    double valueA;
    double valueB;
    moveFront(A);
    moveFront(B);
    while(index(A)>=0 && index(B)>=0){
        col_A=((Entry)get(A))->column;
        col_B=((Entry)get(B))->column;
        valueA = ((Entry)get(A))->value;
        valueB = ((Entry)get(B))->value;
            if(col_A<col_B){
                moveNext(A); 
             }
            else if (col_A>col_B){
                moveNext(B); 
            }
            else{  
                sum+=((valueA)*(valueB));
                moveNext(B); 
                moveNext(A); 
            }
    }
    return sum;
 }

// moveFront(M->rows[1]);
// List l = M->rows[1];
// for(moveFront(l); index(l) != -1; moveNext(l)){
//     printf("col: %d ", ((Entry)get(l))->column);
//     printf("val: %f\n", ((Entry)get(l))->value);
// }