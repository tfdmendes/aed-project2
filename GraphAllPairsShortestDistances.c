//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances {
  int** distance;  // The 2D matrix storing the all-pairs shortest distances
                   // It is stored as an array of pointers to 1D rows
                   // Idea: an INDEFINITE distance value is stored as -1
  Graph* graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances* GraphAllPairsShortestDistancesExecute(Graph* g) {
  assert(g != NULL);

  // 1) Alocar a estrutura de dados que guarda a matriz de distâncias
  GraphAllPairsShortestDistances* result = 
      (GraphAllPairsShortestDistances*)malloc(sizeof(struct _GraphAllPairsShortestDistances));
  assert(result != NULL);

  result->graph = g;

  // 2) Determinar o número de vértices do grafo
  unsigned int numVertices = GraphGetNumVertices(g);

  // 3) Alocar uma matriz 2D de dimensões numVertices x numVertices
  //    Armazenaremos cada "linha" como um ponteiro para um array de int
  result->distance = (int**)malloc(numVertices * sizeof(int*));
  for (unsigned int i = 0; i < numVertices; i++) {
    result->distance[i] = (int*)malloc(numVertices * sizeof(int));
    // Inicializa com -1 indicando "distância indefinida"
    for (unsigned int j = 0; j < numVertices; j++) {
      result->distance[i][j] = -1;  
    }
  }

  // 4) Para cada vértice "origem" i, executamos Bellman-Ford
  //    para calcular distâncias curtas de i até cada outro vértice j
  for (unsigned int i = 0; i < numVertices; i++) {
    // Executa Bellman-Ford partindo do vértice i
    GraphBellmanFordAlg* bf = GraphBellmanFordAlgExecute(g, i);

    // Para cada vértice j, extrair do bf a distância i -> j
    for (unsigned int j = 0; j < numVertices; j++) {
      int dist = GraphBellmanFordAlgDistance(bf, j);
      // Se dist >= 0, significa que j é alcançável a partir de i
      result->distance[i][j] = dist;  
    }

    // Destruir a instância do Bellman-Ford para liberar memória
    GraphBellmanFordAlgDestroy(&bf);
  }

  // 5) Retornar a estrutura com a matriz
  return result;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances** p) {
  assert(*p != NULL);

  GraphAllPairsShortestDistances* aux = *p;
  unsigned int numVertices = GraphGetNumVertices(aux->graph);

  for (unsigned int i = 0; i < numVertices; i++) {
    free(aux->distance[i]);
  }

  free(aux->distance);

  free(*p);
  *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances* p, unsigned int v,
                       unsigned int w) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(w < GraphGetNumVertices(p->graph));

  return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances* p) {
  assert(p != NULL);

  unsigned int numVertices = GraphGetNumVertices(p->graph);
  printf("Graph distance matrix - %u vertices\n", numVertices);

  for (unsigned int i = 0; i < numVertices; i++) {
    for (unsigned int j = 0; j < numVertices; j++) {
      int distanceIJ = p->distance[i][j];
      if (distanceIJ == -1) {
        // INFINITY - j was not reached from i
        printf(" INF");
      } else {
        printf(" %3d", distanceIJ);
      }
    }
    printf("\n");
  }
}
