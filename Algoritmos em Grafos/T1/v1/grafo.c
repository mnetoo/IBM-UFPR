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


//=================================================================================


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

static int get_vertice_id(obj v) {
  return vertice_id((vertice) v);
}

static int get_aresta_id(obj e) {
  return aresta_id((aresta) e);
}


//=================================================================================


//  Verifica se um id pertence a um conjunto de inteiros X.
int pertence_ao_conjunto(int id, int *X, int n_X) 
{
  for (int i = 0; i < n_X; i++) 
    if (X[i] == id)
      return 1;

  return 0;
}


//=================================================================================


//  Transforma o grafo G no seu subgrafo induzido G[X].
void induzir_subgrafo(grafo G, int *X, int n_X) 
{
  no n_vert = primeiro_no(vertices(G));
  
  // Passa pela lista de vértices de forma segura para remoção
  while (n_vert) 
  {
    no proximo_n = proximo(n_vert);

    vertice v = (vertice) conteudo(n_vert);
    int v_id = vertice_id(v);

    // Verifica se o vértice atual deve ser removido
    if (!pertence_ao_conjunto(v_id, X, n_X)) 
    {
      // Se não pertence a X, remove do grafo
      printf("-> Removendo vértice %d (não pertence a X).\n", v_id);
      remove_vertice(v_id, G);
    }

    n_vert = proximo_n;
  }
}


//=================================================================================


//  Funções para lidar com os pesos
static void atualiza_pesos_incidentes(vertice v) 
{
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n)) 
  {
    aresta e = (aresta) conteudo(n);

    // peso = grau(u) + grau(v)
    e->peso = grau(vertice_u(e)) + grau(vertice_v(e));
  }
}


void atualiza_pesos(grafo G) 
{
    for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) 
    {
        vertice v = (vertice)conteudo(n);
        atualiza_pesos_incidentes(v);
    }
}


//=================================================================================


//  Cria grafo vazio e o retorna
grafo cria_grafo() 
{
  grafo G = (grafo) malloc(sizeof(t_grafo));

  if (!G)
    exit(_ERRO_MALLOC_);

  G->vertices = cria_lista();
  G->arestas = cria_lista();

  return G;
}


//=================================================================================


//  Funções para destruir grafo
void destroi_lista(lista L) 
{
    no atual = primeiro_no(L);
    while (atual) 
    {
        no prox = proximo(atual);
        free(atual);
        atual = prox;
    }
    free(L);
}


void destroi_grafo(grafo G) 
{
    // libera arestas
    while (!vazio(arestas(G))) 
    {
        aresta e = (aresta) desempilha(arestas(G));
        free(e);
    }

    destroi_lista(arestas(G));  // libera nós e cabeçalho da lista

    // libera vértices
    while (!vazio(vertices(G))) 
    {
        vertice v = (vertice) desempilha(vertices(G));
        destroi_lista(fronteira(v));
        free(v);
    }

    destroi_lista(vertices(G));

    // libera estrutura principal do grafo
    free(G);
}


//=================================================================================


//  Cria novo vertice com id e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) 
{
  vertice v = (vertice) malloc(sizeof(t_vertice));

  if (!v)
    exit(_ERRO_MALLOC_);

  v->id = id;
  v->fronteira = cria_lista(); // Um novo vértice começa com uma lista de fronteira vazia.


  // empilha o novo vértice na lista de vértices do grafo.
  empilha(v, vertices(G));
}


//=================================================================================


//  Remove vertice com id do grafo G e o destroi
void remove_vertice(int id, grafo G) 
{
  // Busca o vértice com o id fornecido na lista de vértices do grafo
  vertice v = (vertice) busca_chave(id, vertices(G), get_vertice_id);

  if (!v)
    return;


  // Passa sobre todas as arestas na fronteira do vértice v
  while (!vazio(fronteira(v))) 
  {
    // remove a primeira aresta da fronteira de v.
    aresta e = (aresta) desempilha(fronteira(v));
    
    // encontra o outro vértice conectado pela aresta e
    vertice outro_v = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);

    // remove a aresta e da fronteira do outro vértice.
    remove_chave(aresta_id(e), fronteira(outro_v), get_aresta_id);

    // remove a aresta e da lista principal de arestas do grafo.
    remove_chave(aresta_id(e), arestas(G), get_aresta_id);

    free(e);
  }

  // remove o vértice v da lista de vértices do grafo.
  remove_chave(id, vertices(G), get_vertice_id);

  free(fronteira(v));
  free(v);
}


//=================================================================================


//  Cria aresta com id incidente a vertices
void adiciona_aresta(int id, int u_id, int v_id, grafo G) 
{
  // busca pelos ponteiros dos vértices u e v usando seus IDs.
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

  // conecta a aresta ao grafo, adicionando-a a todas as listas relevantes.
  empilha(e, arestas(G));    
  empilha(e, fronteira(u)); 
  empilha(e, fronteira(v));

  e->peso = grau(u) + grau(v);
}


//=================================================================================


//  Remove aresta com id do grafo G e a destroi
void remove_aresta(int id, grafo G) 
{
  // usa remove_chave para encontrar a aresta pelo id e já remove da lista de arestas.
  aresta e = (aresta) remove_chave(id, arestas(G), get_aresta_id);

  if (!e)
    return;


  // pega os ponteiros para os vértices que a aresta conectava.
  vertice u = vertice_u(e);
  vertice v = vertice_v(e);

  // remove a mesma aresta das listas de fronteira de u e v.
  remove_chave(id, fronteira(u), get_aresta_id);
  remove_chave(id, fronteira(v), get_aresta_id);

  free(e);

  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
}


//=================================================================================


//  Calcula e devolve o grau do vertice v
int grau(vertice v) 
{
  int d_v = 0;

  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;

  return d_v;
}


//=================================================================================


//  Funções para impressão do Grafo
void imprime_grafo(grafo G)
{
  printf("\nVertices: <id> - [grau] - <fronteira> \n");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id> - {u,v} / [ PESO = X ]\n");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
}


void imprime_vertice(vertice v)
{
  printf(" VÉRTICE_ID: %d - GRAU: [%d] -", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
}


void imprime_aresta(aresta e)
{
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));

  printf(" ARESTA_ID: %d - {%d,%d} / [ PESO = %d ] ", aresta_id(e), u_id, v_id, e->peso);
}


//=================================================================================