#include <stdio.h>

#define TAM 5

void ordenaVetor (int v[], int n) 
{
    for (int i = 1; i < n; i++)
    {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > chave) 
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = chave;
    }
}

void lerVetor (int v[], int n)
{
    for ( int i = 0; i < n; i++)
        scanf("%d", &v[i]);
}

void imprimeVetor (int v[], int n)
{
    for ( int i = 0; i < n; i++) 
    {
        if (i != n)
            printf(" ");
        printf("%d", v[i]);
    }
}

int main ()
{
    int v[TAM];

    lerVetor (v, TAM);
    ordenaVetor (v, TAM);
    imprimeVetor (v, TAM);

    return 0;
}