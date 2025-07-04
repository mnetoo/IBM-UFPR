#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"



// Cria uma pilha vazia com a capacidade informada e a retorna;
// Retorna NULL em caso de erro
pilha* criar_pilha (int capacidade)
{
    pilha* p = (pilha*) malloc(sizeof(pilha));

    if(!p)
    {
        printf("Falha ao criar a pilha\n");
        return NULL;
    }

    p->base = NULL;
    p->topo = NULL;
    p->capacidade = capacidade;

    return p;
}





// Insere o elemento no topo da pilha (politica LIFO);
void inserir_elemento (pilha *pilha, int valor)
{
    if(!pilha || pilha->tamanho == pilha->capacidade)
    {
        printf("\nPilha cheia!\n");
        return;   //  ERRO
    }

    nodo* novo = (nodo*) malloc(sizeof(nodo));

    if(!novo)
    {
        printf("Erro ao inserir novo elemento!\n");
        return; //  ERRO
    }

    //  o novo nodo aponta para o antigo topo
    novo->proximo = pilha->topo;
    novo->valor = valor;
    //  o novo nodo se torna o topo da pilha
    pilha->topo = novo;

    //  se era a primeira inserção, a base aponta para o novo
    if(!pilha->base)
        pilha->base = novo;

    //  incrementa o tamanho ba pilha
    pilha->tamanho++;
}






// Remove todos os elementos da pilha, libera a memória
void remover_elementos (pilha *pilha)
{
    if(!pilha || !pilha->topo)
    {
        printf("Pilha vazia, nada a remover!\n");
        return;
    }

    while(pilha->topo)
    {
        //  nodo a ser removido
        nodo *atual = pilha->topo;

        //  atualiza o novo topo com o proximo
        pilha->topo = pilha->topo->proximo;

        //  libera a memoria do nodo
        free(atual);
    }

    pilha->base = NULL;
    pilha->tamanho = 0;
}






// Retira o elemento do topo da pilha (politica LIFO)
void retirar_elemento (pilha *pilha)
{
    if(!pilha || !pilha->topo)
    {
        printf("Pilha vazia, nada a remover!\n");
        return;
    }

    //  topo a ser removido
    nodo *topo = pilha->topo;

    //  atualiza o novo topo
    pilha->topo = topo->proximo;

    //  se a pilha ficou vazia após a remoção
    if(!pilha->topo)
        pilha->base = NULL;

    //  libera a memória
    free(topo);

    //  decrementa o tamanho da pilha
    pilha->tamanho--;
}




//  Retorna o elemento que está no topo da pilha, sem remove-lo
int pilha_topo (pilha *pilha)
{
    if(!pilha || !pilha->topo)
    {
        printf("Pilha vazia!\n");
        return -1;
    }

    return pilha->topo->valor;
}





// Retorna o tamanho da pilha (número de elementos na pilha)
int tamanho_pilha (pilha *pilha)
{
    if(!pilha || !pilha->topo)
    {
        printf("Pilha vazia!\n");
        return -1;
    }

    return pilha->tamanho;
}





// Retorna a capacidade da pilha (número de elementos que ela aceita
int capacidade (pilha *pilha)
{
    if(!pilha)
    {
        printf("Pilha não criada!\n");
        return -1;
    }

    return pilha->capacidade;
}





// Imprime o conteúdo da pilha, do topo à base
void imprimir_pilha (pilha *pilha)
{
    if(!pilha || !pilha->topo)
    {
        printf("Pilha vazia!\n");
        return;
    }

    printf("\n---- PILHA ----\n");  
    nodo *atual = pilha->topo;
    while (atual) 
    {
        printf("|  %d  |\n", atual->valor);
        atual = atual->proximo;   
    }
    printf("--------------\n\n");    
}




// Libera toda a memória da pilha
void destruir_pilha(pilha *pilha) 
{
    if (!pilha) 
        return; // Se a pilha não existe, não há o que destruir

    nodo *atual = pilha->topo;
    while (atual) 
    {
        nodo *prox = atual->proximo; // Guarda o próximo nó
        free(atual); // Libera o nó atual
        atual = prox; // Avança para o próximo nó
    }

    free(pilha); // Libera a estrutura da pilha
    printf("Pilha destrída\n");
}