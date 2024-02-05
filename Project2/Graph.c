/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA1
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
	int order; //the number of vertices
	int size; // the number of	edges
	int lastUsedSource;
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
	int actualLength = n + 1;
	Graph G = malloc(sizeof(GraphObj));
	G->vertexNeighbors = malloc(sizeof(List) * actualLength);
	G->colors = (int*)malloc(actualLength * sizeof(int));
	G->parentVertex = (int*)malloc((actualLength) * sizeof(int));
	G->distance = (int*)malloc((actualLength) * sizeof(int));
	G->order = n;
	G->size = 0;
	G->lastUsedSource = NIL;
	for (int i = 1; i <= n; i++) {
		G->vertexNeighbors[i] = newList();
		G->colors[i] = WHITE;
		G->parentVertex[i] = NIL;
		G->distance[i] = INF;
	}
	return G;
}
 void freeGraph(Graph* pG) {
 	if (pG != NULL && *pG != NULL) {
 		//free vertexNeighbor Lists
 		for (int i = 1; i < (getOrder(*pG)); i++) {
			freeList(&(**pG).vertexNeighbors[i]);
 		}
 		free((**pG).parentVertex);
 		free((**pG).colors);
 		free((**pG).distance);
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
			 prepend(L, getSource(G));
		 }	
		 else if (G->parentVertex[u] == NIL) {
			 clear(L);
			 append(L, u);
		 }
			
		 else {
			 getPath(L, G, G->parentVertex[u]);
			 append(L, u);
		 }

	 }
}

// //Manipulation procedures ------------------------------------
 void makeNull(Graph G) {
	 if (G == NULL) {
		 printf("**Graph Error: calling amakeNull() on NULL Graph reference\n");
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
void printGraph(FILE* out, Graph G) {
	if (G == NULL) {
		printf("**Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(EXIT_FAILURE);
	}
	else {
		for (int i = 1; i <= getOrder(G); i++) {
			fprintf(out, "%d :", i);
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
