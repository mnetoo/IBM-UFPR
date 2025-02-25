#include <stdio.h>

void troca(int *a, int *b)
{
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}

int main ()
{
    int i = 21;
    int j = 76;

    printf("Antes da troca: i = %d  /  j = %d\n", i, j);
    troca(&i, &j);
    printf("Depois da troca: i = %d  /  j = %d\n", i, j);
    return 0;
}