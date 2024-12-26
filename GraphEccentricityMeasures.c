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
GraphEccentricityMeasures* GraphEccentricityMeasuresCompute(Graph* g) {
  assert(g != NULL);

  // COMPLETE THE CODE
  // CREATE AUXILIARY (static) FUNCTIONS, IF USEFUL
  // Graph radius --- the smallest vertex eccentricity value
  // Graph diameter --- the largest vertex eccentricity value
  // Do not forget that -1 represents an IDEFINITE value

  // Computing the set of central vertices
  // Allocate the central vertices array : number of central vertices + 1
  // Fill in the central vertices array

  // Obter o número de vértices
  unsigned int numVertices = GraphGetNumVertices(g);

  // Alocar memória para a estrutura principal
  GraphEccentricityMeasures* measures = (GraphEccentricityMeasures*)malloc(sizeof(GraphEccentricityMeasures));
  measures->eccentricity = (int*)malloc(numVertices * sizeof(int));
  measures->graph = g;

  // Obter as distâncias mais curtas entre todos os pares
  GraphAllPairsShortestDistances* distances = GraphAllPairsShortestDistancesCompute(g);
  const int* const* distMatrix = GraphAllPairsShortestDistancesGetDistances(distances);

  // Inicializar valores de raio e diâmetro
  measures->graphRadius = -1;
  measures->graphDiameter = -1;

  // Calcular excentricidade para cada vértice
  for (unsigned int v = 0; v < numVertices; v++) {
    int maxDist = -1;
    for (unsigned int u = 0; u < numVertices; u++) {
      if (distMatrix[v][u] != -1 && distMatrix[v][u] > maxDist) {
        maxDist = distMatrix[v][u];
      }
    }
    measures->eccentricity[v] = maxDist;

    // Atualizar raio e diâmetro
    if (measures->graphRadius == -1 || maxDist < measures->graphRadius) {
      measures->graphRadius = maxDist;
    }
    if (maxDist > measures->graphDiameter) {
      measures->graphDiameter = maxDist;
    }
  }

  // Identificar os vértices centrais
  unsigned int centralCount = 0;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (measures->eccentricity[v] == measures->graphRadius) {
      centralCount++;
    }
  }

  measures->centralVertices = (unsigned int*)malloc((centralCount + 1) * sizeof(unsigned int));
  measures->centralVertices[0] = centralCount;

  unsigned int index = 1;
  for (unsigned int v = 0; v < numVertices; v++) {
    if (measures->eccentricity[v] == measures->graphRadius) {
      measures->centralVertices[index++] = v;
    }
  }

  // Liberar memória da matriz de distâncias
  GraphAllPairsShortestDistancesDestroy(&distances);

  return measures;
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

  unsigned int size = p->centralVertices[0] + 1;
  unsigned int* copy = (unsigned int*)malloc(size * sizeof(unsigned int));
  for (unsigned int i = 0; i < size; i++) {
    copy[i] = p->centralVertices[i];
  }

  return copy;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures* p) {
  printf("Graph Radius: %d\n", p->graphRadius);
  printf("Graph Diameter: %d\n", p->graphDiameter);

  printf("Vertex Eccentricities:\n");
  unsigned int numVertices = GraphGetNumVertices(p->graph);
  for (unsigned int v = 0; v < numVertices; v++) {
    printf("Vertex %u: %d\n", v, p->eccentricity[v]);
  }

  printf("Central Vertices:\n");
  for (unsigned int i = 1; i <= p->centralVertices[0]; i++) {
    printf("%u ", p->centralVertices[i]);
  }
  printf("\n");
}
