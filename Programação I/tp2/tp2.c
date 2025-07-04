/* 

    Este arquivo contém o main com a implementação do trabalho para definir e manipular números racionais.
    Utiliza as funções do arquivo "racional.c" que contém a implementação das funções que foram prototipadas
    em um arquivo header "racional.h"

*/


#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


void ordena_racionais(struct racional vetor[], int n) 
{
    int i, j;
    struct racional temp;
    for (i = 0; i < n - 1; i++) 
    {
        for (j = 0; j < n - i - 1; j++) 
        {
            if (compara_r(vetor[j], vetor[j + 1]) > 0) 
            {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

int main() 
{
    int n;
    struct racional vetor[100];
    struct racional soma = {0, 1};


    // Lê um valor n tal que 0 < n < 100
    do {
        scanf("%d", &n);
    } while (n <= 0 || n >= 100);

    // Preenche o vetor com n números racionais lidos da entrada
    for (int i = 0; i < n; i++) 
    {
        long num, den;
        scanf("%ld %ld", &num, &den);
        vetor[i] = cria_r(num, den);
    }

    // Imprime os números racionais do vetor
    printf("VETOR = ");
    for (int i = 0; i < n; i++)
        imprime_r(vetor[i]);
    printf("\n");
    

    // Retira os elementos inválido do vetor
    int i = 0;
    while (i < n) 
    {
        if (!valido_r(vetor[i])) 
        {
            for (int j = i; j < n - 1; j++)
                vetor[j] = vetor[j + 1];          

            n--;
        } 
        else 
            i++;
    }

    // Imprime os números racionais válidos do vetor
    printf("VETOR = ");
    for (int i = 0; i < n; i++)
        imprime_r(vetor[i]);
    printf("\n");

    ordena_racionais(vetor, n);

    // Imprime o vetor com os números racionais ordenados
    printf("VETOR = ");
    for (int i = 0; i < n; i++)
        imprime_r(vetor[i]);
    printf("\n");

    // Soma todos os elementos do vetor
    for (int i = 0; i < n; i++)
    {
        struct racional temp;
        if (soma_r(soma, vetor[i], &temp))
            soma = temp;
    }

    printf("SOMA = ");
    imprime_r(soma);
    printf("\n");
    return 0;
}
