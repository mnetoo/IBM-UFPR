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

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  
  // codificar...
  
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {
  
  // codificar...

}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  
  // codificar...

}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  
  // codificar...

}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  
  // codificar...

}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}
