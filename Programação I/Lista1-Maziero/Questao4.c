#include <stdio.h>

int main ()
{
	int num, num2, count = 2, soma;

	scanf("%d", &num2);
	scanf("%d", &num);
	soma = num2;	
	while (num != num2 * 2 && num != num2/2)
	{
		soma = soma + num;
		num2 = num;
		count++;
		scanf("%d", &num);
	}
	soma = soma + num;
	printf("%d %d %d %d\n", count, soma, num2, num);
	return 0;
}	
