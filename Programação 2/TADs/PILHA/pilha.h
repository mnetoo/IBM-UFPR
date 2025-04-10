#ifndef PILHA
#define PILHA
 



typedef struct nodo
{
    struct nodo* proximo;
    int valor;
} nodo;


typedef struct pilha
{
  struct nodo* base;
  struct nodo* topo;
  int capacidade;
  int tamanho;
} pilha;





// Cria uma pilha vazia com a capacidade informada e a retorna;
// Retorna NULL em caso de erro
pilha *criar_pilha (int capacidade);
 




// Insere o elemento no topo da pilha (politica LIFO);
void inserir_elemento (pilha *pilha, int valor);





// Remove todos os elementos da pilha, libera a memória
void remover_elementos (pilha *pilha);
 
 




// Retira o elemento do topo da pilha (politica LIFO)
void retirar_elemento (pilha *pilha);





// devolve o elemento no topo da pilha, sem removê-lo da pilha
int pilha_topo (pilha *pilha);





// Retorna o tamanho da pilha (número de elementos na pilha)
int tamanho_pilha (pilha *pilha);





// Retorna a capacidade da pilha (número de elementos que ela aceita
int capacidade (pilha *pilha);





// Imprime o conteúdo da pilha, do topo à base
void imprimir_pilha (pilha *pilha);




void destruir_pilha(pilha *pilha);





#endif