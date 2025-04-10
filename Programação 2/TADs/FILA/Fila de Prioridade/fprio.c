#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"




// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
fila* criar_fprio()
{
    fila* f = (fila*) malloc(sizeof(fila));

    if(!f)
    {
        printf("Erro ao criar a fila!\n");
        return NULL;
    }

    f->num = 0;
    f->primeiro = NULL;

    printf("Fila criada com sucesso!\n");
    
    return f;
}





// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
void inserir_fprio(fila* fila, void *item, int tipo, int prioridade)
{
    if(!fila)
    {
        printf("Fila não inicializada!\n");
        return;
    }

    if(!item)
    {
        printf("Item inválido!\n");
        return;
    }

    //  veririficando se o item já existe na fila
    nodo *temp = fila->primeiro;
    while(temp)
    {
        if(temp == item)
        {
            printf("Item já existe na fila!\n");
            return;
        }

        temp = temp->proximo;
    }

    nodo *novo = (nodo*) malloc(sizeof(nodo));

    if(!novo)
    {
        printf("Erro ao criar novo nodo!\n");
        return;
    }

    novo->item = item;
    novo->prioridade = prioridade;
    novo->tipo = tipo;
    novo->proximo = NULL;

    //  fila vazia
    if(fila->num == 0)
    {
        fila->primeiro = novo;
    }
    //  inserindo de forma ordenada
    else
    {
        nodo *atual = fila->primeiro;
        nodo *anterior = NULL;

        //  se a prioridade do nodo atual for menor ou igual à nova prioridade, o novo nodo deve vir depois
        while(atual && atual->prioridade <= prioridade)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        // Inserir no começo
        if (anterior == NULL)
        {
            novo->proximo = fila->primeiro;
            fila->primeiro = novo;
        }
        // Inserir no meio ou no final
        else
        {
            anterior->proximo = novo;
            novo->proximo = atual;
        }
    }

    fila->num++; // Incrementa o número de itens na fila
    printf("Item inserido com sucesso!\n");
}





void* retirar_fprio(fila *f, int *tipo, int *prio)
{
    if (f->num == 0)  // Verifica se a fila está vazia
    {
        printf("Fila vazia!\n");
        return NULL;  // Retorna NULL se a fila estiver vazia
    }

    nodo *temp = f->primeiro; // Pega o primeiro nodo
    *tipo = temp->tipo;       // Salva o tipo do item
    *prio = temp->prioridade;       // Salva a prioridade do item

    f->primeiro = temp->proximo; // Atualiza o ponteiro para o próximo nodo
    f->num--;                    // Decrementa o número de itens

    void *item = temp->item;     // Pega o item associado ao nodo
    free(temp);                  // Libera a memória do nodo

    return item;                 // Retorna o item retirado (ponteiro void*)
}




// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho(fila* fila)
{
    if (!fila)
    {
        printf("Fila não inicializada!\n");
        return -1;  // Retorna -1 em caso de erro
    }

    return fila->num;  // Retorna o número de itens na fila
}




// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void imprimir_fprio(fila* fila)
{
    if (!fila || fila->num == 0)
    {
        printf("Fila vazia!\n");
        return;
    }

    nodo *temp = fila->primeiro;
    int primeiro = 1;

    while (temp)
    {
        if (!primeiro)
            printf(" ");
        else
            primeiro = 0;

        // Supondo que os itens armazenados são inteiros
        printf("(%d %d %d)", *((int*)temp->item), temp->tipo, temp->prioridade);

        temp = temp->proximo;
    }
}





void destruir_fprio(fila *fila)
{
    if (!fila)
    {
        printf("Fila não inicializada!\n");
        return;
    }

    nodo *temp = fila->primeiro;
    while (temp)
    {
        nodo *proximo = temp->proximo;
        free(temp->item);  // Agora podemos liberar os itens corretamente
        free(temp);
        temp = proximo;
    }

    free(fila);
    printf("Fila destruída com sucesso!\n");
}