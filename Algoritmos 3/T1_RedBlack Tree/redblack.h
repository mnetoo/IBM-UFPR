/*
    Disciplina: Algoritmos e Estrutura de Dados III.
    Professor: Prof. Dr. Eduardo Cunha de Almeida.
    Aluno: Marcus Sebastião Adriano Rocha Neto.
    GRR: 20240710.
    Curso: Informática Biomédica.
    Descrição: Trabalho 1, implementação Árvore Rubro Negra.
*/

#ifndef __REDBLACK__
#define __REDBLACK__

#define RED 1
#define BLACK 0

// Estrutura de cada nó da árvore
struct nodo 
{
	struct nodo *esquerda;
	struct nodo *direita;
	struct nodo *pai;
	
	int chave;
	int cor;
	int nivel;
};

// Estrutura para representar a raiz da árvore
struct arvore
{
	struct nodo *raiz;
};

// Estrutura para simular folha nulas
extern struct nodo *NILL;


//==========================================================================================

// Função para inicializar o nó sentinela NILL
void inicializa_nill();

//==========================================================================================

// Função para criar uma árvore
struct arvore* cria_arvore();

//==========================================================================================

// Função para criar um novo nó na árvore
struct nodo *cria_nodo(struct nodo *pai, int chave);

//==========================================================================================

// Função para encontrar o nó com a maior chave em uma subárvore
struct nodo *maximum(struct nodo *x);

//==========================================================================================

// Função para realizar uma rotação à direita em um nó y
void rot_direita(struct arvore *tree, struct nodo *y);

// Função para realizar uma rotação à esquerda em um nó x
void rot_esquerda(struct arvore *tree, struct nodo *x);

//==========================================================================================

//  FUNÇÕES PARA INSERIR VALORS NA ÁRVORE REDBLACK 

// Função para corrigir a árvore após inclusão de novo nó
void inserir_fixup(struct arvore *t, struct nodo *z);

// Função para inserir mum valor na árvore BST
void inserir(struct arvore *t, struct nodo *z);

//==========================================================================================

//  FUNÇÕES PARA REMOVER VALORES DA ÁRVORE REDBLACK

// Função para buscar um nó com uma chave específica em uma árvore binária
struct nodo *busca_no(struct nodo *n, int procurado);

// Função para transplantar (substituir) uma subárvore por outra
void transplante(struct arvore *t, struct nodo *u, struct nodo *v);

// Função para corrigir a árvore após a exclusão de um nó
void remover_fixup(struct arvore *t, struct nodo *x);

// Função para excluir um nó da árvore
void remover(struct arvore *t, struct nodo *z);

//==========================================================================================

// Função para ajustar níveis dos nós
void ajustar_nivel(struct nodo *no, int nivel);

//==========================================================================================

// Função para imprimir a árvore (EM ORDEM)
void imprimir(struct nodo *no);

//==========================================================================================

// Função auxiliar recursiva para liberar os nós
void libera_nos(struct nodo *no);

// Função para destruir a árvore e liberar memória
void destruir_arvore(struct arvore *arvore);

//==========================================================================================

#endif