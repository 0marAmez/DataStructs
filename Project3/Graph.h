/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA3
* Graph.h
* Graph prototypes
*********************************************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
#include<stdio.h>
#include<stdbool.h>
#include "List.h"


// Exported type --------------------------------------------------------------
typedef struct GraphObj* Graph;
#define INF -1000
#define NIL -2000
#define WHITE 250
#define BLACK 100
#define GRAY 150
#define UNDEF -1
// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions -----------------------------------------------------------
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
//pa3
int getDiscover(Graph G, int u);
int getDist(Graph G, int u);
int getFinish(Graph G, int u);
//pa3
void getPath(List L, Graph G, int u);

// Manipulation procedures ----------------------------------------------------
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
//pa3
void DFS(Graph G, List S);
//pa3
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Additional procedures ----------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out,Graph G);
void InsertionSortList(List L, int x);
bool inList(List L, int x);



#endif
