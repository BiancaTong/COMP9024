// Weighted Graph ADT
// Adjacency Matrix Representation ... COMP9024 17s2
// Written by Bianca Tong for COMP9024 ass2
#include "WGraph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_LENGTH 20



Graph newGraph(int V) {
   assert(V >= 0);
   int i;

   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nV = V;
   g->nE = 0;

   // allocate memory for each row
   g->edges = malloc(V * MAX_WORD_LENGTH * sizeof(int *));
   assert(g->edges != NULL);
   // allocate memory for each column and initialise with 0
   for (i = 0; i < V; i++) {
      g->edges[i] = calloc(3* V* MAX_WORD_LENGTH, sizeof(int));
      assert(g->edges[i] != NULL);
   }

   return g;
}

// check if vertex is valid in a graph
bool validV(Graph g, Vertex v) {
   return (g != NULL && v !=NULL);
}

void insertEdge(Graph g, Edge e, int i, int j) {
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   if (g->edges[i][j] == 0) {   // edge e not in graph
      g->edges[i][j] = e.weight;
      g->nE++;
   }
}

void freeGraph(Graph g) {
   assert(g != NULL);

   int i;
   for (i = 0; i < g->nV; i++)
      free(g->edges[i]);
   free(g->edges);
   free(g);
}
