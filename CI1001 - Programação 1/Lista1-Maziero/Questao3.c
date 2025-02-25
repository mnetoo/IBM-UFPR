#include <stdio.h>
#include <math.h>

int main()
{
    int k, count = 0, num = 1;

    scanf("%d", &k);
    while (count < k)
    {
        int somaDivisores = 0;

        for (int i = 1; i <= sqrt(num); i++)
        {
            if (num % i == 0)
            {
                somaDivisores += i;
                if (i != 1 && i != num / i)
                {
                    somaDivisores += num / i;
                }
            }
        }

        if (somaDivisores == num)
        {
            printf("%d\n", num);
            count++;
        }

        num++;
    }

    return 0;
}
