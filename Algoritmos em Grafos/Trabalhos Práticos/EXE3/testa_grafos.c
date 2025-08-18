#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"





int main() 
{
  // 1. Cria e popula um grafo de exemplo
  grafo G = cria_grafo();

  printf("Criando um grafo de exemplo com 5 vértices e 6 arestas...\n");

  for (int i = 1; i <= 5; i++) {
    adiciona_vertice(i, G);
  }

  adiciona_aresta(101, 1, 2, G);
  adiciona_aresta(102, 1, 3, G);
  adiciona_aresta(103, 2, 3, G);
  adiciona_aresta(104, 2, 4, G);
  adiciona_aresta(105, 4, 5, G);
  adiciona_aresta(106, 3, 5, G);

  printf("==============================================\n");
  printf("Grafo Original (G):\n");
  imprime_grafo(G);

  // 2. Lê o conjunto X do usuário
  int X[100]; // Suporta até 100 vértices no conjunto X
  int n_X = 0;
  int id_lido;

  printf("==============================================\n");
  printf("Digite os IDs dos vértices para o subgrafo G[X]\n");
  printf("(separe com espaço ou enter, termine com -1): ");
  
  while (scanf("%d", &id_lido) == 1 && id_lido != -1) {
    X[n_X++] = id_lido;
  }

  printf("\nConjunto X inserido: { ");
  for(int i = 0; i < n_X; i++) printf("%d ", X[i]);
  printf("}\n");

  // 3. Aplica a transformação
  printf("\nProcesso de indução do subgrafo:\n");
  induzir_subgrafo(G, X, n_X);

  // 4. Imprime o resultado
  printf("\n==============================================\n");
  printf("Grafo Resultante (G[X]):\n");
  imprime_grafo(G);

  // 5. Libera a memória
  destroi_grafo(G);

  return 0;
}