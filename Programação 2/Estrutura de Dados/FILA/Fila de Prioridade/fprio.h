#ifndef FPRIO
#define FPRIO








// descreve um nodo da fila de prioridades
typedef struct nodo
{
  void *item;       //  item associado ao nodo
  int   tipo ;			// tipo do item
  int   prioridade ;			// prioridade do item
  struct nodo *proximo;	// próximo nodo
} nodo;

// descreve uma fila de prioridades
typedef struct fila
{
  nodo *primeiro ;	// primeiro nodo da fila
  int num ;			// número de itens na fila
} fila;









// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
fila* criar_fprio();


// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
void inserir_fprio(fila* fila, void *item, int tipo, int prioridade);


// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
void* retirar_fprio(fila* fila, int *tipo, int *prioridade);


// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho(fila* fila);


// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void imprimir_fprio(fila* fila);


// Libera todas as estruturas de dados da fila, inclusive os itens.
void destruir_fprio(fila* fila);








#endif
