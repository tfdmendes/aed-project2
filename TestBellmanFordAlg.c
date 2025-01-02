  //
  // Algoritmos e Estruturas de Dados --- 2024/2025
  //
  // Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
  //
  // Testing the Bellman-Ford algorithm
  //

  #include <assert.h>
  #include <stdio.h>
  #include <stdlib.h>

  #include "Graph.h"
  #include "GraphBellmanFordAlg.h"
  #include "instrumentation.h"

  static Graph* CreateTreeGraph(unsigned int N) {
    // Cria um grafo com N vértices, dirigido ou não (a seu critério).
    // Aqui, vou criar como digrafo (directed=1) para manter coerência
    // com seu uso do Bellman-Ford, mas pode ser 0 se quiser testar não-dirigido.
    Graph* tree = GraphCreate(N, 1, 0);

    // Exemplo de "árvore em linha": 0->1->2->...->(N-1)
    // (Você pode criar qualquer topologia de árvore, inclusive em estrela.)
    for (unsigned int i = 0; i < N - 1; i++) {
      GraphAddEdge(tree, i, i + 1);
    }

    return tree;
  }

  static Graph* CreateCompleteGraph(unsigned int N) {
    // Cria um grafo dirigido completo: cada par (i, j) com i!=j tem aresta i->j
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
    // ------------------------------------------------
    // Código original que testa outros grafos, etc.
    // ------------------------------------------------

    // 1) Grafo dirigido 'dig01'
    // Graph* dig01 = GraphCreate(6, 1, 0);
    // GraphAddEdge(dig01, 1, 2);
    // GraphAddEdge(dig01, 1, 4);
    // GraphAddEdge(dig01, 3, 4);
    // printf("The graph:\n");
    // GraphDisplayDOT(dig01);
    // printf("\n");

    // GraphCheckInvariants(dig01);

    // // Bellman-Ford Algorithm
    // for (unsigned int i = 0; i < 6; i++) {
    //   GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig01, i);
    //   printf("The shortest path tree rooted at %u\n", i);
    //   GraphBellmanFordAlgDisplayDOT(BF_result);
    //   printf("\n");
    //   GraphBellmanFordAlgDestroy(&BF_result);
    // }

    // // 2) Grafo não-dirigido 'g01'
    // Graph* g01 = GraphCreate(6, 0, 0);
    // GraphAddEdge(g01, 0, 5);
    // GraphAddEdge(g01, 2, 4);
    // GraphAddEdge(g01, 2, 3);
    // GraphAddEdge(g01, 1, 2);
    // GraphAddEdge(g01, 0, 1);
    // GraphAddEdge(g01, 3, 4);
    // GraphAddEdge(g01, 3, 5);
    // GraphAddEdge(g01, 0, 2);

    // printf("The graph:\n");
    // GraphDisplayDOT(g01);
    // printf("\n");

    // GraphCheckInvariants(g01);

    // for (unsigned int i = 0; i < 6; i++) {
    //   GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(g01, i);
    //   printf("The shortest path tree rooted at %u\n", i);
    //   GraphBellmanFordAlgDisplayDOT(BF_result);
    //   printf("\n");
    //   GraphBellmanFordAlgDestroy(&BF_result);
    // }

    // // 3) Ler grafo dirigido de arquivo (DG_2.txt)
    // FILE* file = fopen("DG_2.txt", "r");
    // Graph* dig03 = GraphFromFile(file);
    // fclose(file);

    // GraphDisplayDOT(dig03);
    // printf("\n");
    // GraphCheckInvariants(dig03);

    // for (unsigned int i = 0; i < GraphGetNumVertices(dig03); i++) {
    //   GraphBellmanFordAlg* BF_result = GraphBellmanFordAlgExecute(dig03, i);
    //   printf("The shortest path tree rooted at %u\n", i);
    //   GraphBellmanFordAlgDisplayDOT(BF_result);
    //   printf("\n");
    //   GraphBellmanFordAlgDestroy(&BF_result);
    // }

    // GraphDestroy(&dig01);
    // GraphDestroy(&g01);
    // GraphDestroy(&dig03);

    // ------------------------------------------------
    // A PARTIR DAQUI: Best Case e Worst Case
    // ------------------------------------------------

    // Tamanhos que queremos testar
  unsigned int testSizes[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
  unsigned int numTests = sizeof(testSizes) / sizeof(testSizes[0]);

  for (unsigned int idx = 0; idx < numTests; idx++) {
    unsigned int N = testSizes[idx];

    printf("\n======================================\n");
    printf("TESTE PARA N = %u\n", N);
    printf("======================================\n");

    //
    // BEST CASE: ÁRVORE
    //
    printf("\n--- BEST CASE: ARVORE ---\n");
    Graph* tree = CreateTreeGraph(N);

    InstrReset(); // zerar contadores antes da execução
    GraphBellmanFordAlg* bf_best = GraphBellmanFordAlgExecute(tree, 0);
    // Exibir árvore de caminhos, se quiser:
    // GraphBellmanFordAlgDisplayDOT(bf_best);

    GraphBellmanFordAlgDestroy(&bf_best);
    InstrPrint(); // imprime tempo/contadores do best case

    GraphDestroy(&tree);

    //
    // WORST CASE: GRAFO COMPLETO
    //
    printf("\n--- WORST CASE: GRAFO COMPLETO ---\n");
    Graph* complete = CreateCompleteGraph(N);

    InstrReset(); // zerar contadores antes da execução
    GraphBellmanFordAlg* bf_worst = GraphBellmanFordAlgExecute(complete, 0);
    // Exibir árvore de caminhos, se quiser:
    // GraphBellmanFordAlgDisplayDOT(bf_worst);

    GraphBellmanFordAlgDestroy(&bf_worst);
    InstrPrint(); // imprime tempo/contadores do worst case

    GraphDestroy(&complete);
  }

  return 0;
}