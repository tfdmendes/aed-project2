//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Tiago Mendes 
// Student Number : 119378
// Student Name : André Vasconcelos
// Student Number : 118827

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
//! COMPLETE THE CODE
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  unsigned int numVertices = GraphGetNumVertices(g);

  // Grafo com o mesmo número de vértices
  Graph* tcGraph = GraphCreate(numVertices, /*isDigraph=*/1, /*isWeighted=*/0);

  for (unsigned int s = 0; s < numVertices; s++) {
    // Bellman-Ford para descobrir que vértices são alcançáveis a partir de s
    GraphBellmanFordAlg* bellman = GraphBellmanFordAlgExecute(g, s);

    // se v alcançável a partir de s, add aresta (s -> v)
    for (unsigned int v = 0; v < numVertices; v++) {
      if (GraphBellmanFordAlgReached(bellman, v)) {
        GraphAddEdge(tcGraph, s, v);
      }
    }
    GraphBellmanFordAlgDestroy(&bellman);
  } 


  return tcGraph;
}
