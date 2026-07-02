/*

    Implementação de Fila de Prioridades (Genérica).
    Desenvolvido para o trabalho prático 4 (TAD lista de números inteiros)
    da disciplina de Programação I, turma do Professor David Menotti.

    Este arquivo contém a implementação das funções prototipadas
    no arquivo header "lista.h".

*/


#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"





// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria() 
{
    struct fprio_t *fila = (struct fprio_t *)malloc(sizeof(struct fprio_t));
    
    if (fila == NULL) 
        return NULL;

    // Inicializa os campos da fila
    fila->prim = NULL; // Sem nodos inicialmente
    fila->num = 0;     // Número de itens na fila

    return fila;
}

//------------------------------------------------------------------------------------------------------

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi(struct fprio_t *f) 
{
    if (f == NULL)
        return NULL;

    struct fpnodo_t *atual = f->prim; // Ponteiro para o primeiro nodo da fila
    struct fpnodo_t *temp;             // Armazena o nodo atual

    // Percorre a fila e libera cada nodo e item
    while (atual != NULL) 
    {
        temp = atual;     
        atual = atual->prox; 

        // Libera o item do nodo
        if (temp->item != NULL)
            free(temp->item);

        // Libera o nodo
        free(temp);
    }

    // Libera a fila
    free(f);
    return NULL;
}

//------------------------------------------------------------------------------------------------------

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a política FIFO (retirar
// na ordem em que foram inseridos).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere(struct fprio_t *f, void *item, int tipo, int prio) 
{
    // Verifica se a fila ou item é nulo
    if (f == NULL || item == NULL) 
        return -1;

    // Verifica se o item já está na fila
    struct fpnodo_t *atual = f->prim;
    while (atual != NULL) 
    {
        if (atual->item == item)
            return -1; 
        
        atual = atual->prox;
    }

    // Cria um novo nodo
    struct fpnodo_t *novo_nodo = (struct fpnodo_t *)malloc(sizeof(struct fpnodo_t));
    if (novo_nodo == NULL)
        return -1;

    // Inicializa o novo_nodo
    novo_nodo->item = item;
    novo_nodo->tipo = tipo;
    novo_nodo->prio = prio;
    novo_nodo->prox = NULL;

    // Se a fila está vazia ou novo nodo tem prioridade maior que o primeiro
    if (f->prim == NULL || prio < f->prim->prio) 
    {
        novo_nodo->prox = f->prim; // Novo nodo aponta para o primeiro
        f->prim = novo_nodo;       // Atualiza o primeiro nodo da fila
    }
    else 
    {
        struct fpnodo_t *anterior = NULL;
        atual = f->prim;

        // Percorre a fila para encontrar a posição correta de inserção
        while (atual != NULL && atual->prio <= prio) 
        {
            anterior = atual;       // Mantém o nodo anterior
            atual = atual->prox;   // Avança para o próximo nodo
        }

        // Insere o novo nodo na posição correta
        novo_nodo->prox = atual;    // Novo nodo aponta para o próximo
        if (anterior == NULL) 
            f->prim = novo_nodo;     // Novo nodo vira o primeiro

        else 
            anterior->prox = novo_nodo; // Nodo anterior aponta para o novo

    }

    f->num++;
    return f->num; // Retorna o número de itens na fila após a inserção
}

//------------------------------------------------------------------------------------------------------

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira(struct fprio_t *f, int *tipo, int *prio) 
{
    // Verifica se a fila é válida, se a fila está vazia,se tipo é NULL ou se prio é NULL
    if (f == NULL || f->prim == NULL || tipo == NULL || prio == NULL)
        return NULL;

    // Obtém o primeiro nodo da fila
    struct fpnodo_t *nodo_removido = f->prim;

    // Armazena os valores de tipo e prioridade do item removido
    *tipo = nodo_removido->tipo;
    *prio = nodo_removido->prio;

    // Move o ponteiro do primeiro nodo para o próximo nodo
    f->prim = nodo_removido->prox;
    f->num--;

    void *item_removido = nodo_removido->item;

    free(nodo_removido);

    return item_removido;
}

//------------------------------------------------------------------------------------------------------

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho(struct fprio_t *f) 
{
    // Verifica se a fila é válida
    if (f == NULL) 
        return -1;

    return f->num;
}

//------------------------------------------------------------------------------------------------------

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime(struct fprio_t *f) 
{
    // Verifica se a fila é válida e não está vazia
    if (f == NULL || f->prim == NULL)
        return;

    struct fpnodo_t *atual = f->prim; // Inicia no primeiro nodo
    int primeiro = 1; // Controle do formato da saída

    // Percorre todos os nodos da fila
    while (atual != NULL) 
    {
        // Imprime um espaço antes do item, exceto para o primeiro
        if (!primeiro)
            printf(" ");
        
        // Imprime o tipo e prioridade
        printf("(%d %d)", atual->tipo, atual->prio);
        primeiro = 0; // Marca que já imprimimos o primeiro item

        atual = atual->prox;
    }
}
