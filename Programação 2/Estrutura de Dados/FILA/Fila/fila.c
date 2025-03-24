#include <stdio.h>
#include <stdlib.h>
#include "fila.h"






fila* criar_fila()
{
    fila* f = (fila*) malloc(sizeof(fila));

    if(!f)
    {
        printf("Falha ao criar a fila!\n");
        return NULL;
    }

    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    printf("Fila criada com sucesso\n");

    return f;
}




void inserir_fila(fila* fila, int valor)
{
    if(!fila)
    {
        printf("Fila não inicializada");
        return;
    }

    nodo* novo = (nodo*) malloc(sizeof(nodo));

    novo->proximo = NULL;
    novo->valor = valor;

    //  se a fila estava vazia
    if(!fila->inicio)
    {
        fila->inicio = novo;
        fila->fim = novo;
    }
    else
    {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }

    fila->tamanho++;
}




void remover_fila(fila* fila)
{
    if(!fila)
    {
        printf("Fila não inicializada");
        return;
    }

    if(!fila->inicio)
    {
        printf("Fila vaiza, nada a remover!\n");
        return;
    }

    nodo* remover = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    if(!fila->inicio)
        fila->fim = NULL;

    free(remover);
    fila->tamanho--;
}




void destruir_fila(fila* fila)
{
    if(!fila)
    {
        printf("Fila não inicializada");
        return;
    }

    nodo *atual = fila->inicio;

    while(atual)
    {
        nodo *remover = atual;
        atual = atual->proximo;
        free(remover);
    }

    fila->fim = NULL;
    fila->inicio = NULL;
    fila->tamanho = 0;
}




void imprimir_fila(fila *fila)
{
    if (!fila || !fila->inicio)
    {
        printf("Fila vazia!\n");
        return;
    }

    nodo *atual = fila->inicio;
    printf("[");
    while (atual)
    {
        printf(" %d", atual->valor);
        atual = atual->proximo;
    }
    printf(" ]\n");
}