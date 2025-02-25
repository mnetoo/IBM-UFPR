#include <stdio.h>

#define MAX 1000

int main ()
{
    int n, num, soma = 0;
    float media = 0.00;
    int vetor[MAX];

    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &num);
        vetor[i] = num;
    }

    for(int j = 0; j < n; j++)
    {
        soma += vetor[j];
    }
    media = soma/n;
    printf("%.2f\n", media);
    for(int k = 0; k < n; k++)
    {
        if(vetor[k] > media)
            printf("%d ", vetor[k]);
    }
    printf("\n");
    return 0;
}