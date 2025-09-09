/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _GRAFO_
#define _GRAFO_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct t_vertice *vertice;
typedef struct t_aresta *aresta;
typedef struct t_grafo *grafo;

typedef struct t_vertice {
	int id;
	lista fronteira;
} t_vertice;

typedef struct t_aresta {
	int id;
	vertice u, v;
} t_aresta;

typedef struct t_grafo {
  lista vertices;
  lista arestas;
} t_grafo ;

//---------------------------------------------------------
// getters:

int vertice_id(vertice v);
lista fronteira(vertice v);
int aresta_id(aresta e);
vertice vertice_u(aresta e);
vertice vertice_v(aresta e);
lista vertices(grafo G);
lista arestas(grafo G);

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo();

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G);

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G);

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G);

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G);

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G);

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v);

// imprime o grafo G
void imprime_grafo(grafo G);

// imprime o vertice v
void imprime_vertice(vertice v);

// imprime a aresta e
void imprime_aresta(aresta e);




/*
 * Transforma o grafo G no seu subgrafo induzido G[X].
 * Remove todos os vértices de G que não estão no conjunto X.
 */
void induzir_subgrafo(grafo G, int *X, int n_X);


/*
 * Verifica se um 'id' pertence a um conjunto de inteiros 'X'.
 * Retorna 1 se pertence, 0 caso contrário.
 */
int pertence_ao_conjunto(int id, int *X, int n_X) ;


// Monta e retorna um novo grafo que é o subgrafo de G induzido pelos vértices em X
grafo subgrafo_induzido_por_vertices(grafo G, int *X, int n_X);

// Monta e retorna um novo grafo que é o subgrafo de G induzido pelas arestas em E_X
grafo subgrafo_induzido_por_arestas(grafo G, int *E_X, int n_E_X);

// Encontra e retorna uma lista contendo os IDs dos vértices de um conjunto independente maximal
lista conjunto_independente_maximal(grafo G);




#endif
