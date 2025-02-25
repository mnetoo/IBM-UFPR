#include <stdio.h>

#define DIMENSÃO 8

int main ()
{
      int matriz [DIMENSÃO][DIMENSÃO];
      int matriz_transposta [DIMENSÃO][DIMENSÃO];
      int l, c;

    scanf("%d %d", &l, &c);
    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < l; j++)
        {
            matriz_transposta[i][j] = matriz[j][i];
        }
    }
    for(int i = 0; i < c; i++)
    {
        for(int j = 0; j < l; j++)
        {
            printf("%d ", matriz_transposta[i][j]);        
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}