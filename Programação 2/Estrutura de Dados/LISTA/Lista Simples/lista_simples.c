#include <stdio.h>
#include <stdlib.h>
#include "lista_simples.h"


//=================================================================================================


// Inicialização da fila
lista* inicializa_lista() 
{
    lista *l = (lista*) malloc(sizeof(lista));

    if (l != NULL) 
    {
        l->inicio = NULL;
        l->fim = NULL;
    }

    return l;
}


//=================================================================================================


// Verifica se a lista foi inicializada corretamente
void verifica_lista(lista* l)
{
    if (l == NULL || l->inicio != NULL || l->fim != NULL)
        printf("Falha na inicialização da fila.\n");
    else
        printf("Lista inicializada e vazia!\n\n");
}


//=================================================================================================


// Insere um valor no fim da lista
void insere_lista(lista* l, int valor)
{
    // Aloca memória para o novo nodo
    nodo* novo = (nodo*) malloc(sizeof(nodo));

    // Verifica se a alocação foi bem sucedida
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para o novo nodo.\n");
        return;
    }

    // Atribui o valor ao novo nodo e faz com que ele aponte para NULL
    novo->valor = valor;
    novo->prox = NULL;

    // Se a lista estiver vazia, o novo nodo é o primeiro e o último
    if (l->inicio == NULL) 
    {
        l->inicio = novo;
        l->fim = novo;
    } 
    else
    {
        l->fim->prox = novo; // O último nodo (atual) aponta para o novo
        l->fim = novo;  // Atualiza o ponteiro fim 
    }
}


//=================================================================================================


// Remove um valor da lista
int remove_lista(lista* l)
{
    // Verifica se a lista está vazia
    if (l->inicio == NULL) 
    {
        printf("Lista vazia! Nada a remover.\n");
        return -1;  // Retorna -1 para indicar que a lista está vazia
    }

    // Guarda a referência do nodo a ser removido
    nodo *remover = l->inicio;

    // Atualiza o ponteiro inicio
    l->inicio = remover->prox;

    // Verifica se a lista ficou vazia
    if (l->inicio == NULL)
        l->fim = NULL;

    // Guarda o valor do nodo a ser removido
    int valor_removido = remover->valor;
    free(remover);

    return valor_removido;
}


//=================================================================================================


// Imprime os valores da lista
void imprimindo_lista(lista* l)
{
    nodo *atual = l->inicio;
    printf("[ ");
    while (atual != NULL) 
    {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf(" ]\n\n");
}


//=================================================================================================