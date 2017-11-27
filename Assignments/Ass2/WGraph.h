// Weighted Graph ADT interface ... COMP9024 17s2
// Written by Bianca Tong for COMP9024 ass2
#include <stdbool.h>

#define MAX_WORD_LENGTH 20

typedef struct GraphRep {
   int **edges;  // adjacency matrix storing positive weights
		 // 0 if nodes not adjacent
   int nV;       // #vertices
   int nE;       // #edges
} GraphRep;

typedef struct GraphRep *Graph;

// vertices are ints
typedef char Vertex [MAX_WORD_LENGTH];

// edges are pairs of vertices (end-points)
typedef struct Edge {
   Vertex v;
   Vertex w;
   int weight;
} Edge;

Graph newGraph(int);
void  insertEdge(Graph, Edge, int i, int j);
void  freeGraph(Graph);
