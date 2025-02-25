#include <stdio.h>
#include <math.h>

double potencia(double a, int b)
{
    return pow(a, b);
}


int main ()
{
    double a;
    int b;

    scanf("%lf %d", &a, &b);
    printf("%.2lf\n", potencia(a, b));
}