/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>



//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};
int peso_aresta(aresta e) {
  return e->peso;
}




static int get_vertice_id(obj v) {
  return vertice_id((vertice) v);
}

static int get_aresta_id(obj e) {
  return aresta_id((aresta) e);
}





//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:



// cria grafo vazio e o retorna
grafo cria_grafo() 
{
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}



// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) 
{
  // 1. Percorre a lista de arestas, removendo uma a uma e liberando a memória.
  while (!vazio(arestas(G))) 
  {
      // desempilha retorna um obj (void *), então fazemos o cast para aresta.
      aresta e = (aresta) desempilha(arestas(G));
      // Agora que temos o ponteiro para a aresta, liberamos a memória dela.
      free(e);
  }


  // 2. Percorre a lista de vertices, fazendo o mesmo.
  while (!vazio(vertices(G))) 
  {
      // Pega o primeiro vértice da lista, removendo-o.
      vertice v = (vertice) desempilha(vertices(G));

      // IMPORTANTE: Antes de liberar o vértice 'v', liberamos a lista 'fronteira' dele.
      // A função 'cria_lista' foi chamada para criar esta fronteira,
      // então precisamos liberar a estrutura da lista.
      free(fronteira(v));
      
      // Agora sim, liberamos a memória da estrutura do vértice.
      free(v);
  }

  // Passo 3: Libera as estruturas das listas principais
  free(arestas(G));
  free(vertices(G));

  // Passo 4: Libera a estrutura do grafo
  free(G);
}




// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) 
{
  // 1. Aloca memória para a estrutura do novo vértice.
  vertice v = (vertice) malloc(sizeof(t_vertice));

  // Verifica se a alocação de memória foi bem sucedida.
  if (!v)
    exit(_ERRO_MALLOC_); // Encerra o programa se malloc falhar.

  
  // 2. Inicializa os campos da estrutura do vértice.
  v->id = id;
  v->fronteira = cria_lista(); // Um novo vértice começa com uma lista de fronteira vazia.


  // 3. Adiciona (empilha) o novo vértice na lista de vértices do grafo.
  // Usamos o getter 'vertices(G)' para acessar a lista.
  empilha(v, vertices(G));
}




// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) 
{
  vertice v = (vertice) busca_chave(id, vertices(G), get_vertice_id);

  if (!v)
    return;

  while (!vazio(fronteira(v))) {
    aresta e = (aresta) desempilha(fronteira(v));
    
    vertice outro_v = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);

    remove_chave(aresta_id(e), fronteira(outro_v), get_aresta_id);
    remove_chave(aresta_id(e), arestas(G), get_aresta_id);

    // --- ATUALIZAÇÃO ---
    // A remoção de 'e' diminuiu o grau de 'outro_v', então atualizamos seus vizinhos.
    atualiza_pesos_incidentes(outro_v);
    
    free(e);
  }

  remove_chave(id, vertices(G), get_vertice_id);
  free(fronteira(v));
  free(v);
}




// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) 
{
  vertice u = (vertice) busca_chave(u_id, vertices(G), get_vertice_id);
  vertice v = (vertice) busca_chave(v_id, vertices(G), get_vertice_id);

  if (!u || !v)
    return;
  
  aresta e = (aresta) malloc(sizeof(t_aresta));
  if (!e)
    exit(_ERRO_MALLOC_);
  
  e->id = id;
  e->u = u;
  e->v = v;
  // O peso inicial é a soma dos graus ANTES da nova aresta ser adicionada
  e->peso = grau(u) + grau(v); 

  empilha(e, arestas(G));
  empilha(e, fronteira(u));
  empilha(e, fronteira(v));

  // --- ATUALIZAÇÃO ---
  // Agora que a aresta foi adicionada, os graus de u e v aumentaram.
  // Precisamos atualizar o peso de todas as arestas vizinhas.
  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
}




void remove_aresta(int id, grafo G) 
{
  // A busca precisa ser feita antes, pois a aresta pode ser removida da lista.
  // Usamos busca_chave ao invés de remove_chave no começo.
  aresta e = (aresta) busca_chave(id, arestas(G), get_aresta_id);

  if (!e)
    return;

  vertice u = vertice_u(e);
  vertice v = vertice_v(e);
  
  // Agora sim removemos a aresta de todas as listas
  remove_chave(id, arestas(G), get_aresta_id);
  remove_chave(id, fronteira(u), get_aresta_id);
  remove_chave(id, fronteira(v), get_aresta_id);
  
  // --- ATUALIZAÇÃO ---
  // Agora que a aresta foi removida, os graus de u e v diminuiram.
  // Atualizamos o peso das arestas vizinhas remanescentes.
  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
  
  free(e);
}



//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:




// calcula e devolve o grau do vertice v
int grau(vertice v) 
{
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}




// imprime o grafo G
void imprime_grafo(grafo G) 
{
  no n;

  printf("\n--- IMPRESSÃO DO GRAFO ---\n");

  // Seção de Vértices
  printf("VÉRTICES:\n");
  if (vazio(vertices(G))) {
    printf("  (O grafo não possui vértices)\n");
  } else {
    // Itera pela lista de vértices e chama a nova imprime_vertice para cada um
    for (n = primeiro_no(vertices(G)); n; n = proximo(n)) {
      imprime_vertice((vertice) conteudo(n));
    }
  }

  // Seção de Arestas
  printf("\nARESTAS:\n");
  if (vazio(arestas(G))) {
    printf("  (O grafo não possui arestas)\n");
  } else {
    // Itera pela lista de arestas e chama a nova imprime_aresta para cada uma
    for (n = primeiro_no(arestas(G)); n; n = proximo(n)) {
      imprime_aresta((aresta) conteudo(n));
    }
  }
  
  printf("--- FIM DO GRAFO ---\n\n");
}




// imprime o vertice v
void imprime_vertice(vertice v) 
{
  printf("  Vértice %d [grau %d]:", vertice_id(v), grau(v));
  
  no n = primeiro_no(fronteira(v));
  
  if (!n) {
    printf(" (isolado)\n");
    return;
  }
  
  printf(" vizinhos -> ");
  
  while (n) {
    aresta e = (aresta) conteudo(n);
    vertice vizinho = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);
    
    // Mostra o peso da aresta
    printf("%d (aresta %d, peso %d)", vertice_id(vizinho), aresta_id(e), peso_aresta(e));
    
    if (proximo(n)) {
      printf(", ");
    }
    
    n = proximo(n);
  }
  
  printf("\n");
}




// imprime a aresta e
void imprime_aresta(aresta e) 
{
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  
  // Mostra o peso no final
  printf("  Aresta %d: {%d, %d} [Peso: %d]\n", aresta_id(e), u_id, v_id, peso_aresta(e));
}






// --- FUNÇÕES AUXILIARES ---

/*
 * Verifica se um 'id' pertence a um conjunto de inteiros 'X'.
 * Retorna 1 se pertence, 0 caso contrário.
 */
int pertence_ao_conjunto(int id, int *X, int n_X) 
{
  for (int i = 0; i < n_X; i++) 
    if (X[i] == id)
      return 1;

  return 0;
}

/*
 * Transforma o grafo G no seu subgrafo induzido G[X].
 * Remove todos os vértices de G que não estão no conjunto X.
 */
void induzir_subgrafo(grafo G, int *X, int n_X) 
{
  no n_vert = primeiro_no(vertices(G));
  
  // Itera pela lista de vértices de forma segura para remoção
  while (n_vert) 
  {
    // 1. Salva o ponteiro para o próximo nó ANTES de qualquer modificação
    no proximo_n = proximo(n_vert);

    vertice v = (vertice) conteudo(n_vert);
    int v_id = vertice_id(v);

    // 2. Verifica se o vértice atual deve ser removido
    if (!pertence_ao_conjunto(v_id, X, n_X)) 
    {
      // Se não pertence a X, remove do grafo
      printf("-> Removendo vértice %d (não pertence a X).\n", v_id);
      remove_vertice(v_id, G);
    }

    // 3. Avança para o próximo nó (que foi salvo anteriormente)
    n_vert = proximo_n;
  }
}


static void atualiza_pesos_incidentes(vertice v) 
{
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n)) 
  {
    aresta e = (aresta) conteudo(n);
    // A regra: peso = grau(u) + grau(v)
    e->peso = grau(vertice_u(e)) + grau(vertice_v(e));
  }
}