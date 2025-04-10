#include <stdio.h>
#include <stdlib.h>
#include "lista_dupla.h"

//===========================================================================================


// Função que cria uma lista vazia
lista* criar_lista()
{
    lista *l = (lista*) malloc(sizeof(lista));

    if (l == NULL)
    {
        printf("Erro ao alocar memória para a lista\n");
        exit(1);
    }
    else
    {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        printf("Lista criada com sucesso\n\n");
    }

    return l;
}


//===========================================================================================


// Função que insere um dado na lista
void inserir_lista(lista *l, int valor)
{
    //  Aloca memória para o novo nodo
    nodo* novo = (nodo*) malloc(sizeof(nodo));

    //  Verifica se a alocação foi bem sucedida
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para o novo nodo\n");
        exit(1);
    }
    
    //  Atribui o valor ao novo nodo
    novo->valor = valor;
    novo->prox = NULL;
    novo->ant = l->fim;

    //  Verifica se a lista está vazia
    if(l->inicio == NULL)
    {
        //  Se a lista estiver vazia, o novo nodo será o primeiro e o último
        l->inicio = novo;
        l->fim = novo;
    }
    else
    {
        //  Se a lista não estiver vazia, o novo nodo será o último
        l->fim->prox = novo;
        l->fim = novo;
    }

    //  Incrementa o tamanho da lista
    l->tamanho++;
}


//===========================================================================================


// Função para imprimir a lista (para testes)
void imprime_lista(lista* l) 
{
    nodo* atual = l->inicio;

    printf("[");
    while (atual != NULL) 
    {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("]");
    printf("\n\n");
}


//===========================================================================================


// Função para remover um valor da lista
void remover_lista(lista *l, int valor)
{
    // Verifica se a lista está vazia
    if(l->inicio == NULL)
    {
        printf("Lista vazia, nada a remover.\n");
        return;
    }

    nodo *atual = l->inicio;

    // Caso 1: Remover o primeiro nó (início da lista)
    if (atual->valor == valor) 
    {
        l->inicio = atual->prox;

        // Se a lista não estiver vazia após a remoção, ajusta o ponteiro anterior
        if (l->inicio != NULL)
        {
            l->inicio->ant = NULL; 
        }
        else
        {
            l->fim = NULL; // Se a lista ficar vazia
        }

        free(atual);
        l->tamanho--;
        return;
    }

    // Caso 2: Remover o último nó (fim da lista)
    if (l->fim->valor == valor) 
    {
        nodo *remover = l->fim;
        l->fim = l->fim->ant;

        // Se a lista não estiver vazia após a remoção, ajusta o ponteiro próximo
        if (l->fim != NULL)
        {
            l->fim->prox = NULL;
        }
        else
        {
            l->inicio = NULL; // Se a lista ficar vazia
        }

        free(remover);
        l->tamanho--;
        return;
    }

    // Caso 3: Remover um nó intermediário
    atual = l->inicio;
    while (atual != NULL) 
    {
        if (atual->valor == valor) 
        {
            if (atual->ant != NULL) 
            {
                atual->ant->prox = atual->prox;
            }
            if (atual->prox != NULL) 
            {
                atual->prox->ant = atual->ant;
            }

            free(atual);
            l->tamanho--;
            return;
        }

        atual = atual->prox;
    }

    // Se o elemento não for encontrado
    printf("Elemento não encontrado na lista.\n");
}


//===========================================================================================


// Função que destrói a lista
void destruir_lista(lista *l)
{
    if (l == NULL)
    {
        return;  // Se a lista já estiver NULL, não faz nada
    }

    nodo *atual = l->inicio;

    // Percorre todos os nodos da lista e vai liberando a memória
    while (atual != NULL)
    {
        nodo *temp = atual;
        atual = atual->prox;
        free(temp);  // Libera a memória do nodo
    }

    // Depois de liberar todos os nodos, libera a memória da estrutura da lista
    free(l);
    
    printf("Lista destruída com sucesso.\n");
}
