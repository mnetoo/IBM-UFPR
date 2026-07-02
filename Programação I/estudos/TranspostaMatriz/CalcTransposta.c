#include <stdio.h>

#define DIMENSÃO 8

void leMatriz (int l, int c, int matriz[][DIMENSÃO])
{
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void calcTransposta(int l, int c, int matriz[][DIMENSÃO], int transposta[][DIMENSÃO])
{
    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < l; j++)
        {
            transposta[i][j] = matriz[j][i];
        }
    }
}

int imprimeMatriz(int l, int c, int transposta[][DIMENSÃO])
{
    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < l; j++)
        {
            printf("%d ", transposta[i][j]);        
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}

int main ()
{
    int l, c;
    int matriz[DIMENSÃO][DIMENSÃO], transposta[DIMENSÃO][DIMENSÃO];

    scanf("%d %d", &l, &c);
    leMatriz(l, c, matriz);
    calcTransposta(l, c, matriz, transposta);
    imprimeMatriz(l, c, transposta);
    return 0;
}