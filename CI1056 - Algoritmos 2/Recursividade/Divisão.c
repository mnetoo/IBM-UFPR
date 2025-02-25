#include <stdio.h>

int divisao (int x, int y)
{
    if (x < y)
        return 0;
    else
        return 1 + divisao(x - y, y);
}

int main ()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", divisao(a, b));
    return 0;
}