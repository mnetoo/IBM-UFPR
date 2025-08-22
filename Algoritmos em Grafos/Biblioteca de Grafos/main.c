#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"




void imprime_lista_de_ids(lista l) {
  if (vazio(l)) {
    printf("(vazia)");
    return;
  }
  for (no n = primeiro_no(l); n; n = proximo(n)) {
    int* id_ptr = (int*) conteudo(n);
    printf("%d ", *id_ptr);
  }
}





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


  grafo H = cria_grafo();
  adiciona_vertice(1, H);
  adiciona_vertice(2, H);
  adiciona_vertice(3, H);
  adiciona_vertice(4, H);
  adiciona_vertice(5, H);

  adiciona_aresta(101, 1, 2, H);
  adiciona_aresta(102, 1, 3, H);
  adiciona_aresta(103, 2, 3, H);
  adiciona_aresta(104, 3, 4, H);
  adiciona_aresta(105, 4, 5, H);

  printf("Grafo Original:");
  imprime_grafo(H);

  // --- Exemplo 1: Subgrafo induzido por vértices ---
  printf("--- Testando Subgrafo Induzido por Vértices ---\n");
  int conjunto_vertices[] = {1, 2, 3, 5}; 
  grafo H1 = subgrafo_induzido_por_vertices(H, conjunto_vertices, 4);
  printf("\nSubgrafo induzido pelos vértices {1, 2, 3, 5}:");
  imprime_grafo(H1);
  destroi_grafo(H1); // Lembre-se de destruir o novo grafo

  // --- Exemplo 2: Subgrafo induzido por arestas ---
  printf("\n--- Testando Subgrafo Induzido por Arestas ---\n");
  int conjunto_arestas[] = {101, 105};
  grafo H2 = subgrafo_induzido_por_arestas(H, conjunto_arestas, 2);
  printf("\nSubgrafo induzido pelas arestas {101, 105}:");
  imprime_grafo(H2);
  destroi_grafo(H2);

  // --- Exemplo 3: Conjunto Independente Maximal ---
  printf("\n--- Testando Conjunto Independente Maximal ---\n");
  lista S = conjunto_independente_maximal(H);
  printf("Um conjunto independente maximal encontrado: ");
  imprime_lista_de_ids(S);
  printf("\n");
  
  // Limpeza da lista do conjunto independente (libera os int* e a estrutura da lista)
  while(!vazio(S)) {
    free(desempilha(S));
  }
  free(S);

  // Destroi o grafo original no final
  destroi_grafo(H);

  return 0;
}