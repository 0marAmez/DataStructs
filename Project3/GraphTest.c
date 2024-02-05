/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA3
* GraphTest.c
* Graph testing
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
int main(int argc, char* argv[]) {
//Test#1 Construction --  PASSED
    int i, n = 8;
    Graph G = NULL;
    Graph T = NULL;
    List helper = newList();
    List S = newList();
    for(i=1; i<=n; i++) append(S, i);

    G = newGraph(n);
   
    addArc(G,1,2);
    addArc(G,2,3);
    addArc(G,2,5);
    addArc(G,2,6);
    addArc(G,3,4);
    addArc(G,3,7);
    addArc(G,4,3);
    addArc(G,4,8);
    addArc(G,5,1);
    addArc(G,5,6);
    addArc(G,6,7);
    addArc(G,7,6);
    addArc(G,7,8);
    addArc(G,8,8);
    printGraph(stdout,G);
    DFS(G,S);
    printList(stdout,S);
    T = transpose(G);
    DFS(T,S);
    printf("\n");
    printGraph(stdout,T);
    printList(stdout,S);


printf("Strongest components: \n");

    fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
    printList(stdout,S);

    for(moveBack(S); index(S)>=0;movePrev(S)){
        if(getParent(T,(get(S)))!= NIL){
            prepend(helper,get(S));
        }
        else{
            prepend(helper,get(S));
            printList(stdout,helper);
            clear(helper);
        }
    }

freeGraph(&G);
freeGraph(&T);
freeList(&helper);
freeList(&S);

 
    return(0);

}
