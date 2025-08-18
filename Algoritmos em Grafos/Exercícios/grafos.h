#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>


struct grafo {
    int numVertices;   // número de vértices
    int** matriz;      // matriz de adjacência
} ;


//===========================================================

// Cria um grafo com "numVertices" vértices
struct grafo* cria_grafo(int numVertices);

//===========================================================

// Insere aresta não-direcionada (grafo simples)
void insere_aresta(struct grafo* g, int origem, int destino);

//===========================================================

// Remove aresta
void remove_aresta(struct grafo* g, int origem, int destino);

//===========================================================

// Verifica se existe aresta entre dois vértices
int verifica_aresta(struct grafo* g, int origem, int destino);

//===========================================================

// Imprime a matriz de adjacência
void imprime(struct grafo* g);

//===========================================================

// Libera memória do grafo
void destroi_grafo(struct grafo* g);

//===========================================================

int** multiplica_matrizes(int** mat1, int** mat2, int n);
int encontra_menor_caminho(struct grafo* g, int origem, int destino);

#endif
