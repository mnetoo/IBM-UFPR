#include <stdio.h>
#include <string.h>
 
struct paciente_t
{
  char  nome[100] ;
  short idade ;
  short quarto ;
} ;
 
int main ()
{
  // declaração/alocação
  struct paciente_t pac, *ptr ;
 
  // atribuição de valor aos campos
  pac.idade = 53 ;
  pac.quarto = 417 ;
  strcpy (pac.nome, "Homer Simpson") ;
 
  // atribuição do ponteiro
  ptr = &pac ;
 
  // acesso pela variável struct
  printf ("Paciente %s, %d anos, quarto %d\n", pac.nome, pac.idade, pac.quarto) ;
 
  // acesso pelo ponteiro
  printf ("Paciente %s, %d anos, quarto %d\n", (*ptr).nome, (*ptr).idade, (*ptr).quarto) ;
 
  return (0) ;
}