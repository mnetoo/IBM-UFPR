// Tipo abstrato de dado "fila de inteiros"
// Prof. Carlos Maziero - DINF/UFPR, Out 2024
//
// Este TAD implementa uma fila de números inteiros com capacidade
// para até CAP elementos, definida no momento de sua criação.
//
// Implementação com alocação dinâmica (completar).

#include <stdio.h>
#include <stdlib.h>
#include "fila.h"



// Cria uma fila vazia (sem capacidade definida) e a retorna;
// Retorna NULL em caso de erro
struct fila_t *fila_cria() 
{
    // Aloca memória para a estrutura da fila
    struct fila_t *fila = (struct fila_t *) malloc(sizeof(struct fila_t));
    
    // Verifica se a alocação foi bem-sucedida
    if (fila == NULL)
        return NULL;

    // Inicializa os campos da fila
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->num = 0;

    // Retorna a fila criada
    return fila;
}



// Remove todos os elementos da fila, libera memória e retorna NULL
struct fila_t *fila_destroi (struct fila_t *f)
{
    if (f == NULL)
        return NULL;

    struct nodo_t *atual = f->primeiro;
    struct nodo_t *temp;

    while (atual != NULL)
    {
        temp = atual->prox;
        free(atual);
        atual = temp;
    }

    free(f);
    return NULL;
}


// Insere o elemento no final da fila (política FIFO);
// Retorna o número de elementos na fila após a operação
// ou -1 em caso de erro
int fila_insere(struct fila_t *f, int elem) 
{
    if (f == NULL) 
        return -1; // Se a fila for NULL, retorna erro

    // Aloca memória para o novo nodo
    struct nodo_t *novo = (struct nodo_t *) malloc(sizeof(struct nodo_t));

    if (novo == NULL)
        return -1; // Se não conseguir alocar memória, retorna erro

    // Atribui o valor ao novo nodo e define o próximo como NULL
    novo->valor = elem;
    novo->prox = NULL;

    // Se a fila estiver vazia, inicializa primeiro e último
    if (f->ultimo == NULL) 
    {
        f->primeiro = novo;
        f->ultimo = novo;
    } 
    else 
    {
        // Se não estiver vazia, insere no final
        f->ultimo->prox = novo;
        f->ultimo = novo;
    }

    // Incrementa o número de elementos na fila
    f->num++;

    // Retorna o número de elementos após a inserção
    return f->num;
}


// Retira o elemento do inicio da fila (politica FIFO) e o devolve;
// Retorna o número de elementos na fila após a operação
// ou -1 em caso de erro
int fila_retira (struct fila_t *f, int *elem)
{
    if (f == NULL || f->primeiro == NULL)
        return -1;

    struct nodo_t *temp = f->primeiro;
    *elem = temp->valor;

    f->primeiro = temp->prox;

    if (f->primeiro == NULL)
        f->ultimo = NULL;

    free(temp);
    f->num--;
    return f->num;
}


// Devolve o primeiro da fila, sem removê-lo
// Retorna o número de elementos na fila ou -1 em caso de erro
int fila_primeiro (struct fila_t *f, int *elem)
{
    if (f == NULL || f->primeiro == NULL || elem == NULL)
        return -1;

    *elem = f->primeiro->valor;

    return f->num;
}


// Retorna o tamanho da fila (número de elementos presentes)
int fila_tamanho (struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}


// Retorna a capacidade da fila (número máximo de elementos)
int fila_capacidade (struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->capacidade;
}


// Imprime o conteúdo da fila do início ao fim, no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois e sem \n no fim
void fila_imprime (struct fila_t *f)
{
    if (f == NULL || f->primeiro == NULL)
        return;

    struct nodo_t *atual = f->primeiro;

    while (atual != NULL) 
    {
        printf("%d", atual->valor);
        atual = atual->prox;

        if (atual != NULL)
            printf(" ");
    }
}