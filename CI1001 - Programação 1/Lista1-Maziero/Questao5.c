#include <stdio.h>

int main ()
{
	int n, produto,soma = 0, digito;

	scanf("%d", &n);
	produto = n * 37;
	while (produto != 0)
	{
		digito = produto % 10;
		soma = soma + digito;
		produto = produto/10;
	}
	if (soma == n)
		printf("SIM\n");
	else
		printf("NÃO\n");
	return 0;
}
	
