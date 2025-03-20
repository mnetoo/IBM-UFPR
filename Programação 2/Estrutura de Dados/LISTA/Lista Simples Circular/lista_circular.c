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
    //  Se não existe a fila retorna
    if(!lista)
        return;

    //  Aloca um novo nodo
    nodo* novo = (nodo*) malloc(sizeof(nodo));
    novo->prox = novo;
    novo->valor = valor;

    //  Se a fila estiver vazia, o novo nodo é o primeiro e o último
    if(!lista->primeiro)
    {
        lista->primeiro = novo;
        lista->ultimo = novo;
    }
    //  Se não estiver vazia, insere no final da lista e atualiza para manter circular
    else
    {
        //  o proximo do novo é o primeiro da lista para ficar ciruclar
        novo->prox = lista->primeiro;
        //  o proximo do antigo ultimo é o novo nodo
        lista->ultimo->prox = novo;
        //  e o novo ultimo é o novo nodo
        lista->ultimo = novo;
    }

    //  aumenta o numero de itens na lista
    lista->num++;
}






int remover_lista(lista* lista)
{
    // Se a lista estiver vazia, retorna
    if(!lista->primeiro)
    {
        printf("Lista vazia! Nada a remover.\n");
        return -1;  // Retorna -1 para indicar que a lista está vazia
    }

    // Se a lista tiver um único elemento
    if(lista->primeiro == lista->ultimo)
    {
        int valor_removido = lista->primeiro->valor;
        free(lista->primeiro);  // Libera o único nodo
        lista->primeiro = NULL;  // Lista agora vazia
        lista->ultimo = NULL;    // A lista ficou vazia
        lista->num--;  // Atualiza o número de elementos
        return valor_removido;
    }

    // Se tiver mais de um elemento, remove o primeiro da lista e atualiza
    nodo *removido = lista->primeiro;
    int valor_removido = removido->valor;

    // O primeiro da lista recebe o próximo dele que se torna o primeiro da lista
    lista->primeiro = lista->primeiro->prox;

    // O último nó ainda precisa apontar para o primeiro, pois a lista é circular
    lista->ultimo->prox = lista->primeiro;

    // Libera a memória do nodo removido
    free(removido);

    // Atualiza a quantidade de itens na lista
    lista->num--;

    return valor_removido;
}







void destruir_lista(lista* lista)
{
    //  Se lista for NULL retorna
    if(!lista)
        return;

    //  enquanto a lista estiver nao vazia, remove
    while(lista->primeiro)
    {
        remover_lista(lista);
    }

    //  libera a memória alocada para a lista
    free(lista);
}





void imprimir_lista(lista* lista)
{
    if(!lista->primeiro)
    {
        printf("Lista vazia! Nada a remover.\n");
        return;
    }


    nodo *atual = lista->primeiro;

    printf("[");
    do
    {
        printf(" %d", atual->valor);  // Imprime o valor do nó
        atual = atual->prox;           // Avança para o próximo nó
    } while (atual != lista->primeiro);  // Continua até voltar ao primeiro nó
    printf(" ]\n\n");
}