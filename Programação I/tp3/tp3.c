/*

    Este arquivo contém o main com a implementação do trabalho para definir e manipular números racionais.
    Utiliza as funções do arquivo "racional.c" que contém a implementação das funções que foram prototipadas
    em um arquivo header "racional.h"

*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

// Função para trocar dois ponteiros de racionais
void troca(struct racional **a, struct racional **b)
{
    struct racional *temp = *a;
    *a = *b;
    *b = temp;
}

// Função que ordena vetor de ponteiros de racionais usando Selection Sort
void ordena_racional(struct racional *vetor[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (compara_r(vetor[j], vetor[min]) < 0)
                min = j;

        // Troca o menor elemento encontrado com o primeiro elemento do subvetor não ordenado
        if (min != i)
            troca(&vetor[i], &vetor[min]);
    }
}

void imprime_vetor( int n, struct racional **vetor)
{
    if (n == 0)
        printf("VETOR = ");
    else
    {
        printf("VETOR =");
        for (int i = 0; i < n; i++)
            imprime_r(vetor[i]);
    }

}

void soma_vetor (int n,  struct racional **vetor)
{
    struct racional *soma = cria_r(0, 1);
    struct racional result;

    for (int i = 0; i < n; i++)
    {
        soma_r(soma, vetor[i], &result);
        *soma = result;
    }

    printf("SOMA =");
    imprime_r(soma);
    printf("\n");

    destroi_r(soma);
    soma = NULL;

}

void elimina_invalidos(int *n, struct racional **vetor) 
{
     for (int k = 0; k < *n;) 
     {
         if (!valido_r(vetor[k])) 
         {
             destroi_r(vetor[k]);
             vetor[k] = vetor[*n - 1];
             (*n)--;
         } 
         else
             k++;
     }
}

/* PROGRAMA PRINCIPAL */
int main()
{
    int n;

    // Leitura do valor n até estar no intervalo [1, 99]
    do
    {
        scanf("%d", &n);
    } while (n <= 0 || n >= 100);

    // Alocação do vetor de ponteiros para racionais
    struct racional **vetor = malloc(n * sizeof(struct racional *));
    if (vetor == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Carregando vetor com números racionais
    for (int i = 0; i < n; i++)
    {
        long num, den;
        scanf("%ld %ld", &num, &den);
        vetor[i] = cria_r(num, den);
    }

    imprime_vetor(n, vetor);
    printf("\n");

    elimina_invalidos(&n, vetor);
    imprime_vetor(n, vetor);
    printf("\n");

    // Ordena vetor de racionais
    ordena_racional(vetor, n);
    imprime_vetor(n, vetor);
    printf("\n");

    soma_vetor(n, vetor);

    // Liberando a memória dos racionais no vetor
    for (int i = 0; i < n; i++)
    {
        destroi_r(vetor[i]);
        vetor[i] = NULL; // Define o ponteiro como NULL após liberar
    }

    imprime_vetor(n, vetor);
    printf("\n");

    // Liberando o vetor de ponteiros
    free(vetor);
    vetor = NULL;

    return 0;
}
