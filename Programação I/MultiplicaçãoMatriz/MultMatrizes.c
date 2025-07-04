#include <stdio.h>

#define DIMENSÃO 100

int main ()
{
    int matriz_A [DIMENSÃO][DIMENSÃO];
    int matriz_B [DIMENSÃO][DIMENSÃO];
    int matriz_resultado [DIMENSÃO][DIMENSÃO];
    int lA, cA, lB,cB;

    printf("Dimensões da primeira matriz: \n");
    scanf("%d %d", &lA, &cA);
    printf("Dimensões da segunda matriz: \n");
    scanf("%d %d", &lB, &cB);

    /*verifica se a multiplicação é possível*/
    if (cA != lB)
    {
        printf("Não é possível multiplicar as matrizes!\n");
        return 0;
    }

    printf("Digite os elementos da primeira matriz: \n");
    for(int i = 0; i < lA; i++)
    {
        for(int j = 0; j < cA; j++)
        {
            scanf("%d", &matriz_A[i][j]);
        }
    }
    printf("Digite os elementos da segunda matriz: \n");
    for(int i = 0; i < lB; i++)
    {
        for(int j = 0; j < cB; j++)
        {
            scanf("%d", &matriz_B[i][j]);
        }
    }

    /*inicializa a matriz resultado com 0*/
    for(int i = 0; i < lA; i++)
    {
        for(int j = 0; j < cB; j++)
        {
            matriz_resultado[i][j] = 0;
        }
    }

    /*multiplicação das matrizes*/
    for(int i = 0; i < lA; i++)
    {
        for(int j = 0; j < cB; j++)
        {
            for(int k = 0; k < cA; k++)
            {
                matriz_resultado[i][j] += matriz_A[i][k] * matriz_B[k][j];
            }
        }
    }
    printf("Matriz resultante da multiplicação: \n");
    for(int i = 0; i < lA; i++)
    {
        for(int j = 0; j < cB; j++)
        {
            printf("%d ", matriz_resultado[i][j]);
        }
        printf("\n");
    }
    return 0;
}