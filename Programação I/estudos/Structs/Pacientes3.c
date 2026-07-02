#include <stdio.h>
#include <string.h>

#define VECSIZE 3
 
struct paciente_t
{
  char  nome[100] ;
  short idade ;
  short quarto ;
} ;

int main ()
{
    // declaração/alocação
    struct paciente_t paciente[VECSIZE] ; // vetor com VECSIZE pacientes
 
    // inicializa vetor
    for(int i = 0; i < VECSIZE; i++)
    {
    strcpy (paciente[i].nome, "Marcus") ;
    paciente[i].idade  = i;
    paciente[i].quarto = i + 1;
    }

    for(int j = 0; j < VECSIZE; j++)
        printf ("Paciente %s, %d anos, quarto %d\n", paciente[j].nome, paciente[j].idade, paciente[j].quarto);
    return 0;
}