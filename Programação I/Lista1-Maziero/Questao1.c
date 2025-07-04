#include <stdio.h>

int main ()
{
	int n, produto, k = 1;


	scanf("%d", &n);
	produto = k * (k + 1) * (k + 2);
	while (produto < n)
	{
		k++;
		produto = k * (k + 1) * (k + 2);
	}

	if (produto == n)
		printf("1\n");
	else
		printf("0\n");

	return 0;
}		
