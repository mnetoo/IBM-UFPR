#ifndef ARVORE234_H
#define ARVORE234_H

#define ORDEM 4 // Ordem 4 => até 3 chaves por nó, 4 filhos

// Estrutura de um nó da árvore 2-3-4
typedef struct No234 
{
    int num_chaves;              // Número atual de chaves no nó
    int chaves[ORDEM - 1];       // Vetor de chaves (máximo 3)
    struct No234 *filhos[ORDEM]; // Ponteiros para os filhos (máximo 4)
    int folha;                   // 1 se for folha, 0 se não for
} No234;

// Funções principais
No234* criarNo(int chave, int folha);

void inserir(No234 **raiz, int chave);

void imprimir(No234 *raiz, int nivel);

void liberarArvore(No234 *raiz);

void imprimirArvoreFormatada(No234 *no, int nivel);

void imprimirArvoreHorizontal(No234 *no, int nivel);

void imprimirArvoreVertical(No234 *raiz);

#endif