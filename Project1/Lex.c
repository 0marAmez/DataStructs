
/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA1
* Lex.c
* main program
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
// File I/O
  int line_count;
  FILE *in, *out;
  char line[MAX_LEN];
  char **array = malloc(0); //malloc for dynamic memory since the input size is unknown
  // INSERTION SORT ALGORITHM
    int i,j;
    List L = newList();

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
   while( fgets(line, MAX_LEN, in) != NULL)  {
    line_count++;
    // printf ("%s",line);
    array = realloc(array, line_count * sizeof (char*)); //declare array with unknown size
     array[line_count - 1] = malloc(100 * sizeof(char));  // allocate memory for 100 chars
    strcpy(array[line_count - 1], line);  
   }

// INSERTION SORT ALGORITHM
 append(L, 0);
   for(i=1; i<line_count; i++){
      moveBack(L);
      j = get(L);
      while( strcmp(array[i], array[j])<=0 ){    
         movePrev(L);
         if( index(L)==-1 ) {
            prepend(L, i);
            break;
         }
         j = get(L);
      }
      if(index(L)>=0 ){
         insertAfter(L, i);
      }
   }

//SORTED ARRAY PRINT
  for(moveFront(L); index(L)>=0; moveNext(L)){
      fprintf(out, "%s",array[get(L)]);
   }
   // close files 
   fclose(in);
   fclose(out);


//FREE ARRAY AND LIST
freeList(&L);
for (int i=0; i < line_count; i++) {
    free(array[i]);
}
free(array);
   return(0);
}


