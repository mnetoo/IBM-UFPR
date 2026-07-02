/*

    Implementação de Lista Dupla Encadeada (não-circular).
    Desenvolvido para o trabalho prático 4 (TAD lista de números inteiros)
    da disciplina de Programação I, turma do Professor David Menotti.

    Este arquivo contém a implementação das funções prototipadas
    no arquivo header "lista.h".

*/



#include <stdio.h>
#include <stdlib.h>
#include "lista.h"



// Cria e inicializa uma nova lista vazia.
struct lista_t *lista_cria()
{
    struct lista_t *lista = (struct lista_t *) malloc(sizeof(struct lista_t));

    if (lista == NULL)
        return NULL;

    // Inicializa os membros da lista para representar uma lista vazia.
    lista->prim = NULL;
    lista->ult = NULL;
    lista->tamanho = 0;

    return lista;
}

//============================================================================================================

// Remove todos os itens da lista e libera a memória utilizada.
struct lista_t *lista_destroi(struct lista_t *lst)
{
    if (lst == NULL)
        return NULL;

    struct item_t *atual = lst->prim;

    // Percorre todos os itens da lista
    while (atual != NULL)
    {
        struct item_t *temp = atual; // Armazena o item atual
        atual = atual->prox;         // Avança para o próximo item da lista
        free(temp);                  // Libera a memória do item atual
    }

    free(lst); // Libera a memória da estrutura da lista

    return NULL;
}

//============================================================================================================

// Insere o item na lista na posição indicada;
int lista_insere(struct lista_t *lst, int item, int pos)
{
    if (lst == NULL)
        return -1;

    struct item_t *novo = (struct item_t *)malloc(sizeof(struct item_t));
    if (novo == NULL)
        return -1;

    novo->valor = item;
    novo->ant = NULL;
    novo->prox = NULL;

    // Se posição for igual -1 ou maior que o tamanho atual, insere no final.
    if (pos < 0 || pos >= lst->tamanho)
    {
        if (lst->ult != NULL) // Lista não vazia
        {
            lst->ult->prox = novo;
            novo->ant = lst->ult;
            lst->ult = novo;
        }
        else // Lista vazia
        {
            lst->prim = novo;
            lst->ult = novo;
        }
    }
    else // Insere na posição especificada
    {
        struct item_t *atual = lst->prim;

        // Percorre até a posição desejada
        for (int i = 0; i < pos && atual != NULL; i++)
            atual = atual->prox;

        if (atual == lst->prim)
        {
            novo->prox = lst->prim;
            if (lst->prim != NULL)
                lst->prim->ant = novo;
            lst->prim = novo;

            if (lst->ult == NULL) // Caso seja o único item, atualiza o final também
                lst->ult = novo;
        }
        else
        {
            novo->prox = atual;
            novo->ant = atual->ant;

            if (atual->ant != NULL)
                atual->ant->prox = novo;

            if (atual != NULL)
                atual->ant = novo;
        }
    }

    lst->tamanho++;
    return lst->tamanho;
}

//============================================================================================================

// Retira o item da lista da posição indicada.
int lista_retira(struct lista_t *lst, int *item, int pos)
{
    if (lst == NULL || item == NULL) 
        return -1;

    if (lst->tamanho == 0) 
        return -1;

    struct item_t *atual;

    // Se posição for igual a -1 ou maior ou igual ao tamanho, retira do final
    if (pos < 0 || pos >= lst->tamanho) 
    {
        atual = lst->ult;

        if (atual == NULL) 
            return -1;

        *item = atual->valor;

        if (atual->ant != NULL) 
        {
            lst->ult = atual->ant;
            lst->ult->prox = NULL;
        } 
        else 
        {
            lst->prim = NULL;
            lst->ult = NULL;
        }

        free(atual);
    } 
    else 
    {
        atual = lst->prim;

        // Percorre a lista até a posição indicada
        for (int i = 0; i < pos; i++) 
        {
            atual = atual->prox;
        }

        if (atual == NULL) 
            return -1;

        *item = atual->valor;

        // Ajusta os ponteiros ao remover o item da lista
        if (atual->ant != NULL) 
            atual->ant->prox = atual->prox;
        else 
            lst->prim = atual->prox;

        if (atual->prox != NULL) 
            atual->prox->ant = atual->ant;
        else 
            lst->ult = atual->ant;

        free(atual);
    }

    lst->tamanho--;
    return lst->tamanho;
}

//============================================================================================================

// Retorno: número de itens na lista ou -1 em erro.
int lista_consulta(struct lista_t *lst, int *item, int pos)
{
    if (lst == NULL || item == NULL) 
        return -1;

    if (lst->tamanho == 0) 
        return -1;

    struct item_t *atual;

    // Se posição for -1, consulta o item do final da lista.
    if (pos == -1) 
    {
        atual = lst->ult;
        if (atual == NULL) 
            return -1;

        *item = atual->valor;
    } 
    else if (pos < 0 || pos >= lst->tamanho) 
    {
        return -1;
    } 
    else 
    {
        atual = lst->prim;

        // Percorre a lista até a posição desejada.
        for (int i = 0; i < pos; i++) 
        {
            if (atual == NULL) 
                return -1;

            atual = atual->prox;
        }

        if (atual == NULL) 
            return -1;

        *item = atual->valor; // Armazena o valor encontrado
    }

    return lst->tamanho;
}

//============================================================================================================

// Informa a posição da 1ª ocorrência do valor indicado na lista.
int lista_procura(struct lista_t *lst, int valor)
{
    if (lst == NULL || lst->tamanho == 0)
        return -1;

    struct item_t *atual = lst->prim;
    int posicao = 0;

    // Percorre a lista até encontrar o valor ou até o final
    while (atual != NULL)
    {
        if (atual->valor == valor)
            return posicao;

        atual = atual->prox;
        posicao++;
    }

    return -1;
}

//============================================================================================================

// Retorna o número de itens na lista.
int lista_tamanho(struct lista_t *lst)
{
    if (lst == NULL)
        return -1;

    return lst->tamanho;
}

//============================================================================================================

// Imprime o conteúdo da lista do início ao fim.
void lista_imprime(struct lista_t *lst)
{
    if (lst == NULL || lst->prim == NULL)
        return;

    struct item_t *atual = lst->prim;
    while (atual != NULL)
    {
        printf("%d", atual->valor);
        atual = atual->prox;
        if (atual != NULL)
            printf(" ");
    }
}