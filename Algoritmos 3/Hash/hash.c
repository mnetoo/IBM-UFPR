#include "hash.h"




// Primeira função hash: h1(k) = k % M
int h1(int k) 
{
    return k % M;
}

// Segunda função hash: h2(k) = floor(M * (k*0.9 - floor(k*0.9)))
int h2(int k) 
{
    double produto = k * 0.9;
    double parte_fracionaria = produto - floor(produto);
    return (int)floor(M * parte_fracionaria);
}



// Inserção na tabela (no final da lista)
void inserir_h1(struct nodo* tabela[], int chave) 
{
    int pos = h1(chave);
    
    // Cria struct novo nó
    struct nodo* novo = (struct nodo*) malloc(sizeof(struct nodo));
    novo->chave = chave;
    novo->prox = NULL;

    // Se a lista estiver vazia, insere diretamente
    if (tabela[pos] == NULL)
        tabela[pos] = novo;
    else 
    {
        // Percorre até o final da lista
        struct nodo* atual = tabela[pos];

        while (atual->prox != NULL)
            atual = atual->prox;

        atual->prox = novo;  // Insere no final
    }
}

// Inserção na tabela (no final da lista)
void inserir_h2(struct nodo* tabela[], int chave) 
{
    int pos = h2(chave);
    
    // Cria struct novo nó
    struct nodo* novo = (struct nodo*) malloc(sizeof(struct nodo));
    novo->chave = chave;
    novo->prox = NULL;

    // Se a lista estiver vazia, insere diretamente
    if (tabela[pos] == NULL)
        tabela[pos] = novo;
    else 
    {
        // Percorre até o final da lista
        struct nodo* atual = tabela[pos];

        while (atual->prox != NULL)
            atual = atual->prox;

        atual->prox = novo;  // Insere no final
    }
}




// Impressão da tabela hash
void imprimirTabela(struct nodo* tabela[]) 
{
    printf("Tabela Hash:\n");
    for (int i = 0; i < M; i++) 
    {
        printf("[%d]: ", i);
        struct nodo* atual = tabela[i];

        while (atual != NULL) 
        {
            printf("%d -> ", atual->chave);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}



// Liberar memória
void liberarTabela(struct nodo* tabela[]) 
{
    for (int i = 0; i < M; i++) 
    {
        struct nodo* atual = tabela[i];

        while (atual != NULL) 
        {
            struct nodo* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}