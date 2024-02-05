/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA3
* Graph.c
* Graph definitions
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"

// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
	List* vertexNeighbors;       // Discover    Finish          Undiscover
	int* colors;                 //Gray = 150 , Black =  100,  White = 250
	int* parentVertex;
	int* distance;
	int* discoverTime;
	int* finishTime;
	int order; //the number of vertices
	int size; // the number of	edges
	int lastUsedSource;
} GraphObj;
void visit(Graph G,int x,int* time);


//int time;
// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
	int actualLength = n + 1;
	Graph G = malloc(sizeof(GraphObj));
	G->vertexNeighbors = malloc(sizeof(List) * actualLength);
	G->colors = (int*)malloc(actualLength * sizeof(int));
	G->parentVertex = (int*)malloc((actualLength) * sizeof(int));
	G->distance = (int*)malloc((actualLength) * sizeof(int));
	G->discoverTime = (int*)malloc((actualLength) * sizeof(int));
	G->finishTime = (int*)malloc((actualLength) * sizeof(int));
	G->order = n;
	G->size = 0;
	G->lastUsedSource = NIL;
	for (int i = 1; i <= n; i++) {
		G->vertexNeighbors[i] = newList();
		G->colors[i] = WHITE;
		G->parentVertex[i] = NIL;
		G->distance[i] = INF;
		G->discoverTime[i] = UNDEF;
		G->finishTime[i] = UNDEF;
	}
	return G;
}
 void freeGraph(Graph* pG) {
 	if (pG != NULL && *pG != NULL) {
 	//	free vertexNeighbor Lists
 		for (int i = 1; i <= (getOrder(*pG)); i++) {
			freeList(&((*pG)->vertexNeighbors[i]));
 		}
		 free((*pG)->vertexNeighbors);
		 free((*pG)->colors);
		 free((*pG)->parentVertex);
		 free((*pG)->distance);
		 free((*pG)->discoverTime);
		 free((*pG)->finishTime);
		 free(*pG);
 		*pG = NULL;
 	}
 }
// // Access functions -----------------------------------------------------------

int getOrder(Graph G) {
	if (G == NULL) {
		printf("**Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}
int getSize(Graph G) {
	if (G == NULL) {
		printf("**Graph Error: calling getSize() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
int getSource(Graph G) {
	if (G == NULL) {
		printf("**Graph Error: calling getSource() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	return G->lastUsedSource;
}
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("**Graph Error: calling getParent() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if (u<1 || u>getOrder(G)) {
		printf("**Graph Error: calling getParent() on out of Bounds Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		return G->parentVertex[u];
	}
}
//pa3

int getDiscover(Graph G, int u){
	if (G == NULL) {
	  printf("**Graph Error: calling getDiscover() on NULL Graph reference\n");
	  exit(EXIT_FAILURE);
	}
	else if (u<1 || u>getOrder(G)) {
		printf("**Graph Error: calling getDiscover() on out of Bounds Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		return G->discoverTime[u];
	}
}

int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("**Graph Error: calling getDist() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if (u<1 || u>getOrder(G)) {
		printf("**Graph Error: calling getDist() on out of Bounds Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		return G->distance[u];
	}
}

int getFinish(Graph G, int u){
	if (G == NULL) {
		printf("**Graph Error: calling getFinish() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if (u<1 || u>getOrder(G)) {
		printf("**Graph Error: calling getFinish() on out of Bounds Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		return G->finishTime[u];
	}
}

 void getPath(List L, Graph G, int u) {
	 if (G == NULL) {
		 printf("**Graph Error: calling addEdge() on NULL Graph reference\n");
		 exit(EXIT_FAILURE);
	 }
	 else if (getSource(G) == NIL) {
		 printf("**Graph Error: calling getPath() on NIL source Graph reference\n");
		 exit(EXIT_FAILURE);
	 }
	 else {
		 if (u == getSource(G)) {
			 append(L, getSource(G));
		 }	
		 else if (getParent(G,u) == NIL) {
		//	 clear(L);
			 append(L, getParent(G,u));
		 }
			
		 else {
			 getPath(L, G, getParent(G,u));
			 append(L, u);
		 }

	 }
}

// //Manipulation procedures ------------------------------------
 void makeNull(Graph G) {
	 if (G == NULL) {
		 printf("**Graph Error: calling a makeNull() on NULL Graph reference\n");
		 exit(EXIT_FAILURE);
	 }
	 else {
		 for (int i = 1; i <= getOrder(G); i++) {
			 clear(G->vertexNeighbors[i]);
		 }
		 G->size = 0;
	 }
 }
void addEdge(Graph G, int u, int v) {
	//Check Bounds
	if (G == NULL) {
		printf("**Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if ((u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G))) {
		printf("**Graph Error: calling addEdge() in out of Bounds Graph\n");
		exit(EXIT_FAILURE);
	}
	else {
		// Checks the length of the list, if not empty ensure it's in order
		if (length((G->vertexNeighbors[u])) == 0 && length((G->vertexNeighbors[v])) == 0 ) {
			append(G->vertexNeighbors[u], v);
			append(G->vertexNeighbors[v], u);
			G->size++;
		}

		else if (length((G->vertexNeighbors[u])) == 0 && length((G->vertexNeighbors[v])) != 0) {
			append(G->vertexNeighbors[u], v);
			InsertionSortList(G->vertexNeighbors[v], u);
			G->size++;

		}
		else if (length((G->vertexNeighbors[u])) != 0 && length((G->vertexNeighbors[v])) == 0) {
			append(G->vertexNeighbors[v], u);
			InsertionSortList(G->vertexNeighbors[u], v);
			G->size++;
		}
		else {	
			if (inList(G->vertexNeighbors[u], v) == false && inList(G->vertexNeighbors[v], u)==false) {
				InsertionSortList(G->vertexNeighbors[u], v);
				InsertionSortList(G->vertexNeighbors[v], u);
				G->size++;
			}
		}
	}
}

void DFS(Graph G, List S){
int time;
List temp = newList();
int x;
	if (G == NULL) {
		printf("**Graph Error: calling addEdge() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if(getOrder(G) !=  length(S)){
		printf("**Graph Error: calling DFS() on a not euqal Graph and List reference\n");
		exit(EXIT_FAILURE);
	}
	else{
/// DFS START		
		for (int i = 1; i <= getOrder(G); i++) {
				G->colors[i] = WHITE;
				G->parentVertex[i] = NIL;
		}
	time = 0;
		for (moveFront(S);index(S)>=0;moveNext(S)) {
				if(G->colors[get(S)] == WHITE){
					visit(G,get(S),&time);
				}
		}
/// DFS END		

//order List by creating new List START
	moveFront(S);
	append(temp,get(S));
	for(moveNext(S); index(S)>=0; moveNext(S)){
      moveBack(temp);
      x = get(temp); // 2
      while(getFinish(G,x)<getFinish(G,get(S))){    
         movePrev(temp);
         if( index(temp)==-1 ) {
            prepend(temp, get(S));
            break;
         }
         x = get(temp);
      }
      if(index(temp)>=0 ){
         insertAfter(temp, get(S));
      }
   }
   //order List by creating new List END

  // overwrites list S START
		moveFront(S);
		moveFront(temp);
   	while(index(S)>=0 && index(temp)>=0){
	   	   set(S,get(temp));
	   	   moveNext(S);
		   moveNext(temp);
   	 }
  	 // overwrites list S END
	/// frees temp list
		freeList(&temp);
	}
}
void addArc(Graph G, int u, int v) {
	//Check Bounds
	if (G == NULL) {
		printf("**Graph Error: calling addArc() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else if ((u<1 || u>getOrder(G)) || (v<1 || v>getOrder(G))) {
		printf("**Graph Error: calling addArc() in out of Bounds Graph\n");
		exit(EXIT_FAILURE);
	}
	else {
		// Checks the length of the list, if not empty ensure it's in order
		if (length((G->vertexNeighbors[u])) == 0 ) {
			append(G->vertexNeighbors[u], v);
			G->size++;

		}
		else {
				InsertionSortList(G->vertexNeighbors[u], v);
				G->size++;
		}
	}
}
void BFS(Graph G, int s) {
	int x,y;
		if ((s<1 || s>getOrder(G))) {
		printf("**Graph Error: calling BFS() in out of Bounds source Graph\n");
		exit(EXIT_FAILURE);
	}
		else {
			for (int i = 1; i <= getOrder(G); i++) {
				G->colors[i] = WHITE;
				G->parentVertex[i] = NIL;
				G->distance[i] = INF;
			}
			G->lastUsedSource = s;
			G->colors[s] = GRAY;
			G->distance[s] = 0;
			G->parentVertex[s] = NIL;
			List Q = newList();
			append(Q, s);
			while (length(Q) != 0) {
				x = front(Q);
				deleteFront(Q);
					for (moveFront(G->vertexNeighbors[x]); index(G->vertexNeighbors[x]) >= 0; moveNext(G->vertexNeighbors[x])) {
						y = get(G->vertexNeighbors[x]);
						if (G->colors[y] == WHITE) {
							G->colors[y] = GRAY;
							G->distance[y] = (G->distance[x])+1;
							G->parentVertex[y] = x;
							append(Q, y);
						}
					}
					G->colors[x] = BLACK;
			}
			freeList(&Q);
		}

}

Graph transpose(Graph G){
	if (G == NULL) {
		printf("**Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	Graph x = newGraph(getOrder(G));
for (int i = 1; i <= getOrder(G); i++) {
		for(moveFront(G->vertexNeighbors[i]);index(G->vertexNeighbors[i])>=0;moveNext(G->vertexNeighbors[i])) {
			append(x->vertexNeighbors[get(G->vertexNeighbors[i])],i);
		}
		x->colors[i] = G->colors[i];
		x->parentVertex[i] = G->parentVertex[i];
		x->distance[i] = G->distance[i];
		x->discoverTime[i] = G->discoverTime[i];
		x->finishTime[i] = G->finishTime[i];
	 }
	return x;
}
Graph copyGraph(Graph G){
	if (G == NULL) {
		printf("**Graph Error: calling copyGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	Graph x = newGraph(getOrder(G));
	 for (int i = 1; i <= getOrder(G); i++) {
		for(moveFront(G->vertexNeighbors[i]);index(G->vertexNeighbors[i])>=0;moveNext(G->vertexNeighbors[i])) {
			append(x->vertexNeighbors[i],get(G->vertexNeighbors[i]));
		}
		x->colors[i] = G->colors[i];
		x->parentVertex[i] = G->parentVertex[i];
		x->distance[i] = G->distance[i];
		x->discoverTime[i] = G->discoverTime[i];
		x->finishTime[i] = G->finishTime[i];
	 }
	return x;
}

void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		printf("**Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 1; i <= getOrder(G); i++) {
			fprintf(out, "%d : ", i);
			printList(out, G->vertexNeighbors[i]);
		}
	}
}
void InsertionSortList(List L, int x) {
	int j;
	moveFront(L);
	j = get(L);
	while (j < x && index(L)>=0) {
		moveNext(L);
		if (index(L) == -1) {
			append(L, x);
			break;
		}
		j = get(L);
	}
	if (index(L) >= 0) {
		insertBefore(L, x);
	}
}
bool inList(List L, int x) {
	for (moveFront(L); index(L) >= 0; moveNext(L)) {
		if (get(L) == x) {
			return true;
		}
	}
	return false;
}

void visit(Graph G,int x,int *time){
  int y;
  ++(*time);
  G->discoverTime[x]= *time;
  G->colors[x] = GRAY;
	for (moveFront(G->vertexNeighbors[x]); index(G->vertexNeighbors[x]) >= 0; moveNext(G->vertexNeighbors[x])) {
		y=get(G->vertexNeighbors[x]);
		// printf("\n");
		// printf(" x: %d ---y-value :%d ----- time: %d \n",x,y,(*time));
		if((G->colors[y])== WHITE){
			G->parentVertex[y]= x;
			visit(G,y,time);
		}
	}

	++(*time);
	G->colors[x] = BLACK;
   G->finishTime[x] = *time;

}
