#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES


// Struct que representa cada nodo da lista
typedef struct no 
{
    int valor;
    struct no *prox;
} nodo;

// Struct que representa a fila
typedef struct lista
{
    nodo *inicio;
    nodo *fim;
} lista;


// Inicialização da fila
lista* inicializa_lista();

// Verifica se a lista foi inicializada corretamente
void verifica_lista(lista* l);

// Insere um valor no fim da lista
void insere_lista(lista* l, int valor);

// Remove um valor da lista
int remove_lista(lista* l);

// Imprime os valores da lista
void imprimindo_lista(lista* l);

#endif