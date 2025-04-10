#include <stdio.h>
#include <stdlib.h>
#include "deque.h"





deque* criar_deque(int capacidade)
{
    deque* d = (deque*) malloc(sizeof(deque));

    if(!d)
    {
        printf("Falha ao criar deque!\n");
        return NULL;
    }

    d->capacidade = capacidade;
    d->primeiro = NULL;
    d->ultimo = NULL;
    d->tamanho = 0;

    printf("Deque criado com sucesso!\n");
    return d;
}



void insere_inicio(deque* deque, int valor)
{
    if(!deque)
    {
        printf("Deque não inicializado!\n");
        return;
    }

    // Verifica se o deque já atingiu sua capacidade máxima
    if(deque->tamanho >= deque->capacidade)
    {
        printf("Deque cheio! Não é possível inserir no início.\n");
        return;
    }

    // Se o deque estava vazio
    if(!deque->primeiro)
    {
        nodo* novo = (nodo*) malloc(sizeof(nodo));
        novo->proximo = NULL;
        novo->valor = valor;

        deque->primeiro = novo;
        deque->ultimo = novo;

        deque->tamanho++;
    }
    // Se já continha itens
    else
    {
        nodo* novo = (nodo*) malloc(sizeof(nodo));
        novo->proximo = NULL;
        novo->valor = valor;

        // O antigo primeiro é o próximo do novo nodo 
        novo->proximo = deque->primeiro;
        // O novo nodo é o primeiro
        deque->primeiro = novo;

        deque->tamanho++;
    }
}







void insere_fim(deque* deque, int valor)
{
    if(!deque)
    {
        printf("Deque não inicializado!\n");
        return;
    }

    // Verifica se o deque já atingiu sua capacidade máxima
    if(deque->tamanho >= deque->capacidade)
    {
        printf("Deque cheio! Não é possível inserir no final.\n");
        return;
    }

    // Se o deque estava vazio
    if(!deque->primeiro)
    {
        nodo* novo = (nodo*) malloc(sizeof(nodo));
        novo->proximo = NULL;
        novo->valor = valor;

        deque->primeiro = novo;
        deque->ultimo = novo;

        deque->tamanho++;
    }
    // Se o deque já continha itens
    else
    {
        nodo* novo = (nodo*) malloc(sizeof(nodo));
        novo->proximo = NULL;
        novo->valor = valor;
        
        deque->ultimo->proximo = novo;
        deque->ultimo = novo;

        deque->tamanho++;
    }
}






void retira_inicio(deque* deque)
{
    if(!deque || !deque->primeiro)
    {
        printf("Deque vazio, nada a remover!\n");
        return;
    }

    //  guarda a referencia para o primeiro
    nodo *removido = deque->primeiro;
    //  atualiza o novo primeiro
    deque->primeiro = deque->primeiro->proximo;

    //  se o deque ficou vazio, atualiza o ultimo
    if(!deque->primeiro)
        deque->ultimo = NULL;

    //libera a memoria do antigo primeiro
    free(removido);

    deque->tamanho--;
}





void retira_fim(deque* deque)
{
    if(!deque || !deque->primeiro)
    {
        printf("Deque vazio, nada a remover!\n");
        return;
    }

    //  se o deque tiver um elemento
    if(deque->primeiro == deque->ultimo)
    {
        free(deque->primeiro);
        deque->primeiro = NULL;
        deque->ultimo = NULL;
    }
    else
    {
        nodo *atual = deque->primeiro;

        while(atual->proximo != deque->ultimo)
            atual = atual->proximo;

        atual->proximo = NULL;
        free(deque->ultimo);
        deque->ultimo = atual;        
    }

    deque->tamanho--;
}




int deque_inicio(deque* deque)
{
    if(!deque || !deque->primeiro)
    {
        printf("Deque vazio!\n");
        return -1;
    }

    return deque->primeiro->valor;
}





int deque_fim(deque* deque)
{
    if(!deque || !deque->primeiro)
    {
        printf("Deque vazio!\n");
        return -1;
    }

    return deque->ultimo->valor;
}




int deque_tamanho(deque* deque)
{
    if(!deque)
    {
        printf("Deque não inicializado!\n");
        return -1;  // Retorna -1 se o deque não foi inicializado
    }

    return deque->tamanho;
}






void imprimir_deque(deque* deque)
{
    if(!deque)
    {
        printf("Deque não inicializado!\n");
        return;
    }

    if(!deque->primeiro)
    {
        printf("Deque vazio!\n");
        return;
    }

    nodo *atual = deque->primeiro;
    printf("[");
    while(atual != NULL)
    { 
        printf(" %d", atual->valor);
        atual = atual->proximo;
    }
    printf(" ]\n\n");
}




void destruir_deque(deque* deque)
{
    if (!deque) 
    {
        printf("Deque não inicializado!\n");
        return;
    }

    // Percorre a lista e libera cada nó
    nodo* atual = deque->primeiro;
    while (atual != NULL)
    {
        nodo* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    // Libera o deque
    free(deque);

    printf("Deque destruído com sucesso!\n");
}
