/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA4
* ListTest.c
* List Testing file
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   int X[] = {0,1,2,3,4,5,6,7,8,9,10};
   int i;
   int z = -80;
   int num = -90;


   // initialize Lists A and B
   for( i=1; i<=10; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   // print both lists of integers in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   printf("Lenght of List A %d \n",length(A));
   printf("Lenght of List B %d \n",length(B));

   moveFront(A);
   moveBack(B);
   for (i = 0; i<5;i++){
      moveNext(A);
      movePrev(B);
   }

   printf("\n");
/// PRINTS LISTS
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   printf("Lenght of List A %d \n",length(A));
   printf("Lenght of List B %d \n",length(B));
   printf("Index of List A %d \n",index(A));
   printf("Index of List B %d \n",index(B));


   printf("\n");

   moveFront(A);
   moveBack(B);


   for (i = 0; i<5;i++){
      moveNext(A);
      movePrev(B);
   }
   insertBefore(A, &z);
   insertAfter(B, &z);
   printf("Index of List A %d \n",index(A));
   printf("Index of List B %d \n",index(B));

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");


   printf("Lenght of List A %d \n",length(A));
   printf("Lenght of List B %d \n",length(B));

   printf("\n");

   moveBack(A);
   moveFront(B);
   for (i = 0; i<5;i++){
      moveNext(B);
      movePrev(A);
   }

   printf("Index of List A %d \n",index(A));
   printf("Index of List B %d \n",index(B));
   delete(A);
   delete(B);
   deleteFront(A);
   deleteBack(B);


  for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveBack(A);
   moveFront(B);
   for (i = 0; i<5;i++){
      moveNext(B);
      movePrev(A);
   }
   printf("Returns Front of A: %d \n", *(int*)front(A));
   printf("Returns Back of A: %d \n", *(int*)back(A));
   printf("Returns Cursor of A: %d \n", *(int*)get(A));
   printf("Returns Front of B: %d \n", *(int*)front(B));
   printf("Returns Back of B: %d \n", *(int*)back(B));
   printf("Returns Cursor of B: %d \n", *(int*)get(B));
   printf("Index of List A %d \n",index(A));
   printf("Index of List B %d \n",index(B));
   set(A,&num);
   set(B,&num);

  for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   freeList(&A);
   freeList(&B);


   return(0);
}