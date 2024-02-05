/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA4
* Sparse.c
* Read Input and output file
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int token_count, line_count;
   FILE *in, *out;
   char line[MAX_LEN];
   char tokenBuffer[MAX_LEN];
   char* token;
   Matrix A;
   Matrix B;
   Matrix Scalar,Additon,Additon2,Sub,Sub2,T,dot1,dot2;
   int NNZA;
   int NNZB;
   int i,j,x,iterA,iterB;
   double z,value;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file, then count and print tokens
   line_count = 0;
   iterA = 0;
   iterB = 0;
   while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;

      // get tokens in this line
      token_count = 0;
      tokenBuffer[0] = '\0';

      // get first token
      token = strtok(line, " \n");
      
      while( token!=NULL ){ // we have a token
         // update token buffer
         strcat(tokenBuffer, "   ");
         strcat(tokenBuffer, token);
         strcat(tokenBuffer, "\n");
         token_count++;
 // CHECK WHAT'S INSIDE token:
        //  fprintf(out,"Toke #%d: ", token_count);        
        //  fprintf(out,token);
        //  fprintf(out,"\n");
        if(line_count == 1 && token_count == 1){
           sscanf(token, "%d", &x);
            A = newMatrix(x); 
            B = newMatrix(x);
        }
        if (line_count == 1 && token_count == 2){
            sscanf(token, "%d", &x);
            NNZA = x;
        }
        if (line_count == 1 && token_count == 3){
            sscanf(token, "%d", &x);
            NNZB = x;
        }
        if ( token_count == 1 && line_count!=1){
            sscanf(token, "%d", &x);
            i = x;
            // printf("%d row\n",i);
        }
        if (token_count == 2 && line_count!=1){
           sscanf(token, "%d", &x);
            j = x;
            // printf("%d col \n",j);
        }
        if (token_count == 3 && line_count!=1){
           sscanf(token, "%lf", &z);
            value = z;
            // fprintf(out,"%f :", z);
            if(iterA != NNZA){
                if(value != 0.0){
                    changeEntry(A,i,j,value);
                    iterA++;
                }
            }
            else{
                if(iterB != NNZB && iterA == NNZA){
                  if(value!=0.0){
                    changeEntry(B,i,j,value);
                    iterB++;
                  }
                }
            }
        }
         token = strtok(NULL, " \n");
      }
   }
  fprintf(out,"A has %d non-zero entries: \n",NNZ(A)); 
  printMatrix(out,A);
  fprintf(out,"\n");
  fprintf(out,"B has %d non-zero entries: \n",NNZ(B)); 
  printMatrix(out,B);
  fprintf(out,"\n"); 

  Scalar = scalarMult(1.5,A);
  Additon = sum(A,B);
  Additon2 = sum (A,A);
  Sub = diff (B,A);
  Sub2 = diff(A,A);
  T = transpose(A);
  dot1 = product(A,B);
  dot2 = product(B,B);

  fprintf(out,"(1.5)*A =  \n");
  printMatrix(out,Scalar);
  fprintf(out,"\n"); 
  fprintf(out,"A+B =  \n");
  printMatrix(out,Additon);
  fprintf(out,"\n"); 
  fprintf(out,"A+A =  \n");
  printMatrix(out,Additon2);
  fprintf(out,"\n"); 
  fprintf(out,"B-A =  \n");
  printMatrix(out,Sub);
  fprintf(out,"\n"); 
 fprintf(out,"A-A =  \n");
  printMatrix(out,Sub2);
  fprintf(out,"\n"); 
 fprintf(out,"Transpose(A) =  \n");
  printMatrix(out,T);
  fprintf(out,"\n"); 
 fprintf(out,"A*B =  \n");
  printMatrix(out,dot1);
  fprintf(out,"\n");
fprintf(out,"B*B =  \n");
  printMatrix(out,dot2);
  fprintf(out,"\n"); 


   // close files 
   fclose(in);
   fclose(out);
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&Scalar);
   freeMatrix(&Additon);
   freeMatrix(&Additon2);
   freeMatrix(&Sub);
   freeMatrix(&Sub2);
   freeMatrix(&T);
   freeMatrix(&dot1);
   freeMatrix(&dot2);

   return(0);
}