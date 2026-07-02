#include <stdio.h>

int main ()
{
	int a, b, seq = 1;

	scanf("%d", &a);
	while (a != 0)
	{
		scanf("%d", &b);
		if (b != a*a)
			seq = 0;
		scanf("%d", &a);
	}
	if (seq == 1)
		printf("1\n");
	else
		printf("0\n");
	return 0;
}
