#include <stdio.h>
#include <string.h>

struct paciente
{
    char nome[100];
    short idade;
    short quarto;
};

typedef struct paciente paciente;

int main ()
{
    paciente pac1, pac2;

    pac1.idade = 53;
    pac1.quarto = 417;

    strcpy(pac1.nome, "Marcus Neto");

    pac2 = pac1;

    printf("Paciente %s, %d anos, quarto %d\n", pac1.nome, pac1.idade, pac1.quarto);
    printf("Paciente %s, %d anos, quarto %d\n", pac1.nome, pac1.idade, pac1.quarto);
    return 0;
}