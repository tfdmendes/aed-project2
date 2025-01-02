//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Tiago Mendes 
// Student Number : 119378
// Student Name : André Vasconcelos
// Student Number : 118827

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
  unsigned int*
      centralVertices;  // centralVertices[0] = number of central vertices
                        // array size is (number of central vertices + 1)
  int* eccentricity;    // the eccentricity value of each vertex
  Graph* graph;         // the graph
  int graphRadius;      // the graph radius
  int graphDiameter;    // the graph diameter
};

// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
// COMPLETE THE CODE
// CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
// Graph radius --- the smallest vertex eccentricity value
// Graph diameter --- the largest vertex eccentricity value
// Do not forget that -1 represents an IDEFINITE value

// Computing the set of central vertices
// Allocate the central vertices array : number of central vertices + 1
// Fill in the central vertices array

GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);
  GraphEccentricityMeasures* result = (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
  assert(result != NULL);
  result->graph = g;
  unsigned int numVertices = GraphGetNumVertices(g);

  // Array de excentricidades
  result->eccentricity = (int*)malloc(numVertices * sizeof(int));
  assert(result->eccentricity != NULL);

  // Inicializar as excentricidades com valores indefinidos (-1)
  for (unsigned int i = 0; i < numVertices; i++) {
    result->eccentricity[i] = -1;  
  }

  GraphAllPairsShortestDistances* allPairs = GraphAllPairsShortestDistancesExecute(g);

  for (unsigned int i = 0; i < numVertices; i++) {
    int maxDist = -1;  // Começar com um valor indefinido (maxDist)

    // Para cada vértice j, verificar a distância i -> j
    for (unsigned int j = 0; j < numVertices; j++) {
      if (i != j) {
        int dist = GraphGetDistanceVW(allPairs, i, j);
        if (dist != -1) {  // Se a distância for válida
          maxDist = (dist > maxDist) ? dist : maxDist;
        }
      }
    }

    // A excentricidade do vértice i é a maior distância encontrada
    result->eccentricity[i] = maxDist;
  }

  // Calcular o raio e o diâmetro do grafo
  result->graphRadius = (result->eccentricity[0] != -1) ? result->eccentricity[0] : 1;
  result->graphDiameter = (result->eccentricity[0] != -1) ? result->eccentricity[0] : 1;

  for (unsigned int i = 0; i < numVertices; i++) {
    if (result->eccentricity[i] != -1) {
      result->graphRadius = (result->eccentricity[i] < result->graphRadius) ? result->eccentricity[i] : result->graphRadius;
      result->graphDiameter = (result->eccentricity[i] > result->graphDiameter) ? result->eccentricity[i] : result->graphDiameter;
    }
  }

  // Identificar os vértices centrais (excentricidade igual ao raio do grafo)
  unsigned int centralCount = 0;
  for (unsigned int i = 0; i < numVertices; i++) {
    if (result->eccentricity[i] == result->graphRadius) {
      centralCount++;
    }
  }

  // Alocar e preencher os vértices centrais
  result->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  result->centralVertices[0] = centralCount;  // O primeiro valor é o número de vértices centrais

  unsigned int centralIndex = 1;
  for (unsigned int i = 0; i < numVertices; i++) {
    if (result->eccentricity[i] == result->graphRadius) {
      result->centralVertices[centralIndex++] = i;
    }
  }

  GraphAllPairsShortestDistancesDestroy(&allPairs);
  return result;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures** p) {
  assert(*p != NULL);

  GraphEccentricityMeasures* aux = *p;

  free(aux->centralVertices);
  free(aux->eccentricity);

  free(*p);
  *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures* p) {
  assert(p != NULL);

  return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures* p,
                               unsigned int v) {
  assert(p != NULL);
  assert(v < GraphGetNumVertices(p->graph));
  assert(p->eccentricity != NULL);

  return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int* GraphGetCentralVertices(const GraphEccentricityMeasures* p) {
  assert(p != NULL);
  assert(p->centralVertices != NULL);

  // COMPLETE THE CODE

  unsigned int* centralVerticesCopy = (unsigned int*)malloc(sizeof(unsigned int) * (p->centralVertices[0] + 1));
  if (centralVerticesCopy == NULL) {
    perror("Failed to allocate memory for centralVerticesCopy");
    return NULL;
  }

  // Copiar os vértices centrais para o novo array
  for (unsigned int i = 0; i <= p->centralVertices[0]; i++) {
    centralVerticesCopy[i] = p->centralVertices[i];
  }

  return centralVerticesCopy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  // COMPLETE THE CODE
  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);
  
  printf("Vertex Eccentricities:\n");
  unsigned int numVertices = GraphGetNumVertices(p->graph);
  for (unsigned int i = 0; i < numVertices; i++) {
    printf("Vertex %d: Eccentricity = %d\n", i, p->eccentricity[i]);
  }

  printf("Central Vertices: ");
  for (unsigned int i = 1; i <= p->centralVertices[0]; i++) {
    printf("%d ", p->centralVertices[i]);
  }
  printf("\n");
}
