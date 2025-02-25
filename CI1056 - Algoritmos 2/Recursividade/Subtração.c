#include <stdio.h>

int subtracao(int x, int y)
{
    if (y == 0)
        return x;
    else
        return (subtracao(x - 1, y - 1));
}

int main ()
{
    int a, b;

    scanf("%d %d", &a, &b);
    printf("%d\n", subtracao(a, b));
    return 0;
}