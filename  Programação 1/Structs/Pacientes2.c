#include <stdio.h>
#include <string.h>
 
struct paciente_t
{
  char  nome[100] ;
  short idade ;
  short quarto ;
} ;
 
// imprime na tela os dados do paciente
void imprime_paciente (struct paciente_t p)
{
  printf ("Paciente %s, %d anos, quarto %d\n", p.nome, p.idade, p.quarto) ;
}
 
// devolve um paciente "nulo"
struct paciente_t paciente_nulo ()
{
  struct paciente_t p = {"nulo", 0, 0} ;
  return (p) ;
}
 
int main ()
{
  // declaração de variável com valor inicial
  struct paciente_t pac1 = { "Home Simpson", 47, 501 } ;
 
  // cópia de struct
  struct paciente_t pac2 = pac1 ;
 
  // struct como parâmetro de função (passagem por cópia)
  imprime_paciente (pac2) ;
 
  // struct como retorno de função
  pac2 = paciente_nulo () ;
  imprime_paciente (pac2) ;
 
  return (0) ;
}