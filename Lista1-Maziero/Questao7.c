#include <stdio.h>

int main ()
{
	int n, i;
	long long int fatorial = 1;

	scanf("%d", &n);
	for (i = 2; i <= n; i++)
	{
		fatorial = fatorial * i;
	}
	printf("%lld\n", fatorial);
	return 0;
}
