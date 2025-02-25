// TAD lista de números inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// Definição da interface do TAD - NÃO ALTERAR

#ifndef LISTA
#define LISTA

// estrutura de um item da lista
struct item_t
{
  int valor ;			// valor do item
  struct item_t *ant ;		// item anterior
  struct item_t *prox ;	// próximo item
} ;

// estrutura de uma lista
struct lista_t
{
  struct item_t *prim ;	// primeiro item
  struct item_t *ult ;		// último item
  int tamanho ;		// número de itens da lista
} ;

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL em erro.
struct lista_t *lista_cria ();

// Remove todos os itens da lista e libera a memória.
// Retorno: NULL.
struct lista_t *lista_destroi (struct lista_t *lst);

// Nas operações insere/retira/consulta/procura, a lista inicia na
// posição 0 (primeiro item) e termina na posição TAM-1 (último item).

// Insere o item na lista na posição indicada;
// se a posição for além do fim da lista ou for -1, insere no fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_insere (struct lista_t *lst, int item, int pos);

// Retira o item da lista da posição indicada.
// se a posição for além do fim da lista ou for -1, retira do fim.
// Retorno: número de itens na lista após a operação ou -1 em erro.
int lista_retira (struct lista_t *lst, int *item, int pos);

// Informa o valor do item na posição indicada, sem retirá-lo.
// se a posição for além do fim da lista ou for -1, consulta do fim.
// Retorno: número de itens na lista ou -1 em erro.
int lista_consulta (struct lista_t *lst, int *item, int pos);

// Informa a posição da 1ª ocorrência do valor indicado na lista.
// Retorno: posição do valor ou -1 se não encontrar ou erro.
int lista_procura (struct lista_t *lst, int valor);

// Informa o tamanho da lista (o número de itens presentes nela).
// Retorno: número de itens na lista ou -1 em erro.
int lista_tamanho (struct lista_t *lst);

// Imprime o conteúdo da lista do inicio ao fim no formato "item item ...",
// com um espaço entre itens, sem espaços antes/depois, sem newline.
void lista_imprime (struct lista_t *lst);

#endif
