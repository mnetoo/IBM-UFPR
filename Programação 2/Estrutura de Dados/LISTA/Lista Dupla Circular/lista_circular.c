#include <stdio.h>
#include <stdlib.h>
#include "lista_circular.h"









lista* criar_lista()
{
    lista* l = (lista*) malloc(sizeof(lista));

    if(!l)
        return NULL;

    l->primeiro = NULL;
    l->ultimo = NULL;
    l->num = 0;

    return l;
}






void inserir_lista(lista* lista, int valor)
{
    if(!lista)
        return;

    nodo* novo = (nodo*) malloc(sizeof(nodo));
    novo->valor = valor;

    //  se a lista estiver vazia, o novo nodo é o primeiro e o ultimo
    if(!lista->primeiro)
    {
        novo->proximo = novo;
        novo->anterior = novo;
        lista->primeiro = novo;
        lista->ultimo = novo;
    }
    else
    {
        //  o anterior do novo nodo aponta para o antigo ultimo
        novo->anterior = lista->ultimo;

        //  o proximo do antigo ultimo aponta para o novo nodo que agora é o ultimo 
        lista->ultimo->proximo = novo;

        //  o proximo do novo nodo aponta para o primeiro
        novo->proximo = lista->primeiro;

        //  o anterior do primeiro aponta para o novo ultimo que é o novo nodo
        lista->primeiro->anterior = novo;

        //  o novo nodo é o ultimo da lista
        lista->ultimo = novo;
    }

    lista->num++;
}





int remover_lista(lista* lista)
{
    if(!lista->primeiro)
    {
        printf("Lista vazia, nada a remover.");
        return -1;
    }

    //  se a lista tiver apenas um elemento
    if(lista->primeiro == lista->ultimo)
    {
        int valor_removido = lista->primeiro->valor;
        free(lista->primeiro);
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->num--;
        return valor_removido;
    }
    else
    {
        nodo *removido = lista->primeiro;
        int valor_removido = lista->primeiro->valor;

        //  o lista primeiro aponta para o proximo que se torna o novo primeiro
        lista->primeiro = lista->primeiro->proximo;

        // o anterior do novo lista primeiro aponta para o ultimo
        lista->primeiro->anterior = lista->ultimo;

        // o proximo do ultimo aponta para o novo primeiro
        lista->ultimo->proximo = lista->primeiro;

        free(removido);
        lista->num--;
        return valor_removido;
    }

}