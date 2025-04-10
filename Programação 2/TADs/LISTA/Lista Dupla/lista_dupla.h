#ifndef LISTA_DUPLA
#define LISTA_DUPLA



// Struct que representa cada nodo da lista
typedef struct nodo 
{
    int valor;
    struct nodo *prox;
    struct nodo *ant;
} nodo;

// Struct que representa a lista
typedef struct lista 
{
    nodo *inicio;
    nodo *fim;
    int tamanho;
} lista;


//=============================================================================

// Função que cria uma lista
lista* criar_lista();


//=============================================================================

// Função que insere um dado na lista
void inserir_lista(lista *l, int valor);


//=============================================================================

// Função que remove um dado da lista
void remover_lista(lista *l, int valor);


//=============================================================================

// Função que imprime a lista
void imprime_lista(lista *l);


//=============================================================================

// Função que destrói a lista
void destruir_lista(lista *l);


//=============================================================================


#endif