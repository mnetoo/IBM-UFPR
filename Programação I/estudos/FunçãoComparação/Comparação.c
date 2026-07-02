#include <stdio.h>

int compara (int a, int b)
{
    if(a < b) return -1;
    if(a > b) return 1;
    return 0;
}

int main ()
{
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d\n", compara(a, b));
    return 0;
}