#include <stdio.h>

int soma (int x, int y)
{
    if (y == 0)
        return x;
    else   
        return 1 + soma(x, y - 1);
}

int main ()
{
    int a, b;

    scanf("%d %d", &a, &b);
    printf("%d\n", soma(a, b));
    return 0;
}

/*  DEFINIÇÃO RECURSIVA DO PROBLEMA

    A + B = 1 + (a + (b - 1)) ------ se b > 0
    A + B = a ------ se b = 0
    
*/