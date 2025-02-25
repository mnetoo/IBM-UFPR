#include <stdio.h>

int multiplicacao (int x, int y)
{
    if (y == 1)
        return x;
    else
        return (x + multiplicacao(x, y - 1 ));
}

int main ()
{
    int a, b;

    scanf("%d %d", &a, &b);
    printf("%d\n", multiplicacao(a, b));
    return 0;
}

/*  DEFINIÇÃO RECURSIVA DO PROBLEMA

    A * B = a + (a * (b - 1)) ------ se b > 1
    A * B = a ------ b = 0
*/