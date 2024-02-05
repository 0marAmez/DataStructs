/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA4
* MatrixTest.c
* Matrix testing file
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){

   Matrix M = newMatrix(3);
    Matrix P = newMatrix(3);
    Matrix O;
    Matrix T;
    Matrix S;
    Matrix D;
    Matrix sumTest;
    Matrix dotTest;



  //   printf("\n");
  //   printf("%d",size(M));
  //   printf("\n");
  //   printf("%d",NNZ(M));
  //   printf("\n");
    // changeEntry(M, 1,1,0);

  changeEntry(M, 1,1,1);
  // changeEntry(M, 1,1,0);
    changeEntry(M, 1,2,2);
    // changeEntry(M, 1,2,0);
    changeEntry(M, 1,3,3);
    // changeEntry(M,1,3,64);
    changeEntry(M, 2,1,4);
    changeEntry(M, 2,2,5);
    changeEntry(M, 2,3,6);
    changeEntry(M, 3,1,7);
    changeEntry(M, 3,2,8);
    changeEntry(M, 3,3,9);

    changeEntry(P, 1,1,1);
    changeEntry(P, 1,2,2);
    changeEntry(P, 1,3,3);
    changeEntry(P, 2,1,4);
    changeEntry(P, 2,2,5);
    changeEntry(P, 2,3,6);
    changeEntry(P, 3,1,7);
    changeEntry(P, 3,2,8);
    changeEntry(P, 3,3,9);


 printf("One if equal, zero if they're not: %d \n",equals(M,P));
      // changeEntry(M, 1,2,0);
  //   changeEntry(M, 1,2,4);
  //   changeEntry(M, 1,1,6);
  // changeEntry(M, 1,2,0);
  // changeEntry(M, 1,2,7);

printf("----M \n");

printMatrix(stdout, M);
printf("\n");

printf("----P \n");


printMatrix(stdout, P);


makeZero(M);
printf("----M: \n");
printMatrix(stdout, M);
printf("----P: \n");
printMatrix(stdout, P);

printf("One if equal, zero if they're not: %d \n",equals(M,P));
printf("\n");

//Test for all operators changing entries 
    // changeEntry(P, 1,2,0);
    // changeEntry(P, 2,2,0);


O = copy(P);
T= transpose(P);
S = scalarMult(2.0,P);
sumTest =  sum (T,P);
// D = diff(M,P);
D = diff(sumTest,S);
dotTest = product(S,sumTest);



printf("----P: \n");
printMatrix(stdout, P);
printf("----O: \n");
printMatrix(stdout, O);
printf("----T: \n");
printMatrix(stdout, T);
printf("----S: \n");
printMatrix(stdout, S);
printf("----SumTest: \n");
printMatrix(stdout, sumTest);

printf("----DiffTest: \n");
printMatrix(stdout, D);
printf("----DotTest: \n");
printMatrix(stdout, dotTest);
printf("\n");

  freeMatrix(&dotTest);
  freeMatrix(&D);
  freeMatrix(&sumTest);
  freeMatrix(&S);
  freeMatrix(&T);
  freeMatrix(&M);
  freeMatrix(&P);
  freeMatrix(&O);

    return(0);
}