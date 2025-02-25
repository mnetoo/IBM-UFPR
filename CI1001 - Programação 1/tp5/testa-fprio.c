// TAD Fila de prioridades (FPRIO) genérica
// Carlos Maziero, DINF/UFPR, Out 2024
// Programa de teste

#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

// item a guardar na FPRIO
struct item_t
{
  int dado1 ;
  int dado2 ;
} ;

//------------------------------------------------------------------------------

// cria um novo item
struct item_t *item_cria (int a, int b)
{
  struct item_t *item ;

  item = malloc (sizeof (struct item_t)) ;
  if (!item)
    abort () ;

  item->dado1  = a ;
  item->dado2  = b ;

  return (item) ;
}

//------------------------------------------------------------------------------

// destroi um item
struct item_t *item_destroi (struct item_t *item)
{
  if (item)
    free (item) ;
  return (NULL) ;
}

//------------------------------------------------------------------------------

// imprime a FP
void fprio_print (struct fprio_t *fp)
{
  int tam ;

  if (!fp)
    return ;

  // imprime a FP
  printf ("Fila: ") ;
  fprio_imprime (fp) ;
  tam = fprio_tamanho (fp) ;

  // imprime o tamanho da FP
  switch (tam)
  {
    case 0:
      printf ("(0 itens)\n") ;
      break ;
    case 1:
      printf (" (1 item)\n") ;
      break ;
    default:
      printf (" (%d itens)\n", tam) ;
  }
}

//------------------------------------------------------------------------------

// imprime mensagem de erro e encerra execução
void erro (char *msg)
{
  fprintf (stderr, "ERRO: %s\n", msg) ;
  exit (1) ;
}

//------------------------------------------------------------------------------

int main ()
{
  struct fprio_t *fp ;
  struct item_t *item ;
  int tipo, prio, status ;
  int tipo_ant, prio_ant ;

  // cria uma FP vazia
  printf ("Cria a fila:\n") ;
  fp = fprio_cria () ;
  if (!fp)
    erro ("não criou a fila") ;
  fprio_print (fp) ;
  printf ("\n") ;

  // cria e insere itens na FP
  printf ("Insere itens com prioridades crescentes:\n") ;
  for (int i = 0; i < 3; i++)
  {
    item = item_cria (0, 0) ;
    if (!item)
      erro ("não criou o item") ;
    printf ("Insere item [%d %d] com tipo %d e prioridade %d\n",
              item->dado1, item->dado2, 0, i) ;
    status = fprio_insere (fp, item, 0, i) ;
    if (status < 0)
      erro ("não inseriu na lista") ;
    fprio_print (fp) ;
  }
  printf ("\n") ;

  // insere mais eventos na LEF
  printf ("Insere itens com prioridades decrescentes:\n") ;
  for (int i = 3; i >= 0; i--)
  {
    item = item_cria (1, 1) ;
    if (!item)
      erro ("não criou o item") ;
    printf ("Insere item [%d %d] com tipo %d e prioridade %d\n",
              item->dado1, item->dado2, 1, i) ;
    status = fprio_insere (fp, item, 1, i) ;
    if (status < 0)
      erro ("não inseriu na lista") ;
    fprio_print (fp) ;
  }
  printf ("\n") ;

  printf ("Retira os 4 primeiros itens:\n") ;
  for (int i = 0; i < 4; i++)
  {
    //   retira o primeiro item da FP
    item = fprio_retira (fp, &tipo, &prio) ;
    if (item)
    {
      printf ("retirou item [%d %d] com tipo %d e prioridade %d\n",
              item->dado1, item->dado2, tipo, prio) ;
      item = item_destroi (item) ;
    }
    else
      erro ("não retirou item") ;

    fprio_print (fp) ;
  }
  printf ("\n") ;

  // insere mais eventos na LEF
  printf ("Insere itens com prioridades crescentes:\n") ;
  for (int i = 1; i < 5; i++)
  {
    item = item_cria (2, 2) ;
    if (!item)
      erro ("não criou o item") ;
    printf ("Insere item [%d %d] com tipo %d e prioridade %d\n",
              item->dado1, item->dado2, 2, i) ;
    status = fprio_insere (fp, item, 2, i) ;
    if (status < 0)
      erro ("não inseriu na lista") ;
    fprio_print (fp) ;
  }
  printf ("\n") ;

  // enquanto a FP não estiver vazia
  printf ("Retira itens verificando a ordem:\n") ;
  tipo_ant = -1 ;
  prio_ant = -1 ;
  while (fprio_tamanho (fp) > 0)
  {
    //   retira o primeiro item da FP
    item = fprio_retira (fp, &tipo, &prio) ;
    if (item)
    {
      printf ("retirou item [%d %d] com tipo %d e prioridade %d\n",
              item->dado1, item->dado2, tipo, prio) ;
      item = item_destroi (item) ;

      // verifica se itens estão saindo na ordem correta
      if ((prio > prio_ant) || ((prio == prio_ant) && (tipo > tipo_ant)))
      {
        tipo_ant = tipo ;
        prio_ant = prio ;
      }
      else
        if (prio < prio_ant)
          erro ("fila não respeita ordem de prioridades") ;
        else
          erro ("fila não respeita ordem FIFO para a mesma prioridade") ;
    }
    else
      erro ("não retirou item") ;

    fprio_print (fp) ;
  }
  printf ("\n") ;

  // testa operações inválidas sobre lista ou valor inexistentes
  printf ("Testa operações com parâmetros inválidos:\n") ;

  item = item_cria (0, 0) ;

  // insere com fila NULL
  status = fprio_insere (NULL, item, 0, 0) ;
  if (status != -1)
    erro ("insere com fila NULL não retornou erro") ;

  // insere com item NULL
  status = fprio_insere (fp, NULL, 0, 0) ;
  if (status != -1)
    erro ("insere com item NULL não retornou erro") ;

  // insere com item repetido
  status = fprio_insere (fp, item, 0, 0) ;
  if (status == -1)
    erro ("insere item falhou") ;
  status = fprio_insere (fp, item, 0, 0) ;
  if (status != -1)
    erro ("insere item repetido não retornou erro") ;

  // retira com fila NULL
  item = fprio_retira (NULL, &tipo, &prio) ;
  if (item)
    erro ("retira com fila NULL não retornou erro") ;

  // retira com tipo NULL
  item = fprio_retira (fp, NULL, &prio) ;
  if (item)
    erro ("retira com tipo NULL não retornou erro") ;

  // retira com prioridade NULL
  item = fprio_retira (fp, &tipo, NULL) ;
  if (item)
    erro ("retira com prioridade NULL não retornou erro") ;

  // tamanho com fila NULL
  status = fprio_tamanho (NULL) ;
  if (status != -1)
    erro ("tamanho em fila NULL não retornou erro") ;

  printf ("\n") ;

  // destroi a FP
  printf ("Destroi a fila:\n") ;
  fp = fprio_destroi (fp) ;
  fprio_print (fp) ;
  printf ("\n") ;

  // encerra
  return (0) ;
}
