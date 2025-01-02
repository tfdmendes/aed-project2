//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Transitive Closure algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"


// BEST CASE: grafo acíclico com N vértices
// 0->1->2->...->(N-1)
static Graph* CreateDAGLine(unsigned int N) {
  Graph* dag = GraphCreate(N, 1, 0);
  for (unsigned int i = 0; i < N - 1; i++) {
    GraphAddEdge(dag, i, i + 1);
  }
  return dag;
}

// WORST CASE: Grafo dirigido completo com N vértices
// (i->j para todo i!=j)
static Graph* CreateCompleteDigraph(unsigned int N) {
  Graph* complete = GraphCreate(N, 1, 0);
  for (unsigned int i = 0; i < N; i++) {
    for (unsigned int j = 0; j < N; j++) {
      if (i != j) {
        GraphAddEdge(complete, i, j);
      }
    }
  }
  return complete;
}




int main(void) {
  /*
  // What kind of graph is dig01?
  Graph* dig01 = GraphCreate(6, 1, 0);
  GraphAddEdge(dig01, 1, 2);
  GraphAddEdge(dig01, 1, 4);
  GraphAddEdge(dig01, 3, 4);
  printf("The graph:\n");
  // Displaying in DOT format
  GraphDisplayDOT(dig01);
  printf("\n");

  GraphCheckInvariants(dig01);

  Graph* tcdig01 = GraphComputeTransitiveClosure(dig01);
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig01);
  printf("\n");

  GraphCheckInvariants(tcdig01);

  // Reading a directed graph from file
  FILE* file = fopen("DG_2.txt", "r");
  Graph* dig03 = GraphFromFile(file);
  fclose(file);
  // Displaying in DOT format
  GraphDisplayDOT(dig03);
  printf("\n");

  GraphCheckInvariants(dig03);

  Graph* tcdig03 = GraphComputeTransitiveClosure(dig03);
  printf("The transitive closure:\n");
  // Displaying in DOT format
  GraphDisplayDOT(tcdig03);
  printf("\n");

  GraphCheckInvariants(tcdig03);

  GraphDestroy(&dig01);
  GraphDestroy(&dig03);

  GraphDestroy(&tcdig01);
  GraphDestroy(&tcdig03);
  */
  unsigned int testSizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
  unsigned int numTests = 12;
  for (unsigned int i = 0; i < numTests; i++) {
      unsigned int N = testSizes[i];

      printf("\n======================================\n");
      printf("TESTE PARA N = %u\n", N);
      printf("======================================\n");

      // BEST CASE
      printf("--- BEST CASE: DAG em linha ---\n");
      Graph* dag = CreateDAGLine(N);
      InstrReset();
      Graph* dagTC = GraphComputeTransitiveClosure(dag);
      GraphDestroy(&dag);
      GraphDestroy(&dagTC);
      InstrPrint();

      // WORST CASE
      printf("--- WORST CASE: Grafo completo ---\n");
      Graph* complete = CreateCompleteDigraph(N);
      InstrReset();
      Graph* compTC = GraphComputeTransitiveClosure(complete);
      GraphDestroy(&complete);
      GraphDestroy(&compTC);
      InstrPrint();
  }


  return 0;
}