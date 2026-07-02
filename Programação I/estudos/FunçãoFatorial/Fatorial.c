#include <stdio.h>
 
long fatorial (int n)
{
  if (n <= 1)
    return 1;
  else
    return (n * fatorial (n - 1));
}
 
int main ()
{
    int n;

    scanf("%d", &n);  
    printf ("fatorial (%d): %ld\n", n, fatorial (n));
    return 0;
}