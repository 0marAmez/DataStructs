/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA3
* FindComponents.c
* File I/O
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {

    int token_count, line_count;
    FILE* in, * out;
    char line[MAX_LEN];
    char tokenBuffer[MAX_LEN];
    char* token;
    // VARIABLES FOR COUNTER AND VERTEX
    int x;
    int u;
    int v;
    int c = 0;
    // GRAPHS AND LISTS DEFINITIONS
    Graph G = NULL;
    Graph T = NULL ;
    List L = NULL;
    List helper = NULL;


    // check command line for correct number of arguments
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // REDIFINES VARIABLES TO PREVENT MEMORY LEAKS
    line_count = 0;
    L = newList();
    helper =  newList ();
    while (fgets(line, MAX_LEN, in) != NULL) {
        line_count++;
        token_count = 0;
        tokenBuffer[0] = '\0';
        token = strtok(line, " \n");
        while (token != NULL) { // we have a token
           // update token buffer
            strcat(tokenBuffer, "   ");
            strcat(tokenBuffer, token);
            strcat(tokenBuffer, "\n");
            token_count++;
            //CONVERST TOKEN TO INTEGER       
            sscanf(token, "%d", &x);

            if(x==0){
                 break;
             }   
            if (line_count == 1) {
                //CREATES GRAPH G AND LIST L
                G = newGraph(x);
                 for(int i=1; i<=x; i++){
                     append(L, i);
                 } 
            }
            if (token_count == 1 ) {
                u = x;
            }
            if (token_count == 2) {
                v = x;
                addArc(G, u, v);
            }

            token = strtok(NULL, " \n");
        }
    }

   fprintf(out,"Adjacency list representation of G:");
   fprintf(out,"\n");
   printGraph(out, G);
   fprintf(out,"\n");
   DFS(G, L);
   T = transpose(G);
   DFS(T, L);

 for(moveBack(L); index(L)>=0;movePrev(L)){
    if(getParent(T,(get(L)))== NIL){
            c++;
        }
    }

   fprintf(out,"G contains %d strongly connected components:" , c);
   fprintf(out,"\n");
    c = 0;
for(moveBack(L); index(L)>=0;movePrev(L)){
    if(getParent(T,(get(L)))!= NIL){
        prepend(helper,get(L));
    }
    else{
        prepend(helper,get(L));
        ++c;
        fprintf(out,"Component %d: ", c);
        printList(out,helper);
        clear(helper);
        }
    }





 // close files 
    fclose(in);
    fclose(out);
    freeGraph(&G);
    freeGraph(&T);
    freeList(&helper);
    freeList(&L);



    return(0);
}