#include <stdio.h>
#include <stdlib.h>
#include "jukefila.h"





jukefila* criar_jukefila()
{
    jukefila *fila = (jukefila*) malloc(sizeof(jukefila));

    if(!fila)
    {
        printf("Erro ao criar a fila!\n");
        return NULL;
    }

    fila->inicio = NULL;
    fila->final = NULL;

    return fila;
}



void inserir_jukefila(pedido* elemento, jukefila* fila)
{
    //  se a fila estava vazia ou o novo elemento deve ser inserido no início
    if (!fila->inicio || fila->inicio->valor < elemento->valor)
    {
        elemento->proximo = fila->inicio;
        elemento->anterior = NULL;
        
        if (fila->inicio) // se tinha um primeiro elemento ajusta o ponteiro anterior
            fila->inicio->anterior = elemento;
        else
            fila->final = elemento; // se a fila estava vazia o fim também é atualizado

        fila->inicio = elemento;
    }
    else
    {
        pedido *atual = fila->inicio;

        //  percorre a lista até encontrar a posição correta
        while (atual->proximo != NULL && atual->proximo->valor >= elemento->valor)
            atual = atual->proximo;

        //  insere na posição correta
        elemento->proximo = atual->proximo;
        elemento->anterior = atual;
        atual->proximo = elemento;

        // atualiza o nó seguinte 
        if (elemento->proximo)
            elemento->proximo->anterior = elemento;
        else
            fila->final = elemento; // se for o último atualiza o final
    }
}



pedido* consumir_jukefila(jukefila* fila)
{
    // 1. Verifica se a fila está vazia
    if (fila->inicio == NULL) 
        return NULL;  // Sai da função se não houver músicas

    // 2. Remove a música do início da fila (maior valor)
    pedido *tocada = fila->inicio;      // Salva referência para a música que será tocada
    fila->inicio = tocada->proximo;     // Atualiza o início da fila para a próxima música

    return tocada;
}



unsigned int contar_jukefila(jukefila* fila)
{
    unsigned int count = 0;

    pedido *atual = fila->inicio;

    while(atual != NULL)
    {
        count++;
        atual = atual->proximo;
    }
    return count;
}



void destruir_jukefila(jukefila *fila)
{
    if(!fila)
        return;

    pedido *atual = fila->inicio;

    while(atual != NULL)
    {
        pedido *temp = atual;
        destruir_pedido(atual);
        atual = temp->proximo;
    }

    free(fila);
}