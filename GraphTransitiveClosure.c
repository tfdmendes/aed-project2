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

  // 1) Criar um novo grafo (digrafo e não ponderado) com o mesmo número de vértices
  Graph* tcGraph = GraphCreate(numVertices, /*isDigraph=*/1, /*isWeighted=*/0);

  // 2) Para cada vértice s do grafo original
  for (unsigned int s = 0; s < numVertices; s++) {
    // Usar Bellman-Ford para descobrir que vértices são alcançáveis a partir de s
    GraphBellmanFordAlg* bellman = GraphBellmanFordAlgExecute(g, s);

    // 3) Para cada vértice v, se v for alcançável a partir de s, adicionar aresta (s -> v)
    for (unsigned int v = 0; v < numVertices; v++) {
      if (GraphBellmanFordAlgReached(bellman, v)) {
        // Podemos inserir (s -> v). 
        // Se quisermos evitar laços (s -> s), podemos verificar (s != v), mas em 
        // muitos contextos de fecho transitivo o laço (s -> s) também costuma ser inserido 
        // (já que s é triv. alcançável de s). Depende da convenção desejada.
        GraphAddEdge(tcGraph, s, v);
      }
    }

    // Libertar a memória do Bellman-Ford para o vértice s
    GraphBellmanFordAlgDestroy(&bellman);
  }

  // Retornar o grafo que representa o fecho transitivo
  return tcGraph;
}
