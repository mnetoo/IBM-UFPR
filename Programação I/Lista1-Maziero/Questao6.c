#include <stdio.h>

int main ()
{
	int n, i;
	long long  int fib1 = 1, fib2 = 1, fibAtual;

	scanf("%d", &n);

	if (n == 1)
	{
		printf("1\n");
	}
	else if (n == 2)
	{
		printf("1 1\n");
	}
	else
	{
		printf("1 1");
		for (i = 3; i <= n; i++)
		{	
			fibAtual = fib1 + fib2;
 			printf(" %lld", fibAtual);
			fib1 = fib2;
			fib2 = fibAtual;
		}
		printf("\n");
	}
	return 0;
}	
