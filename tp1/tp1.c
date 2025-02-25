#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


int main ()
{
    int max, n;
    struct racional r1,r2;
    struct racional r_soma,r_subtracao;
    struct racional r_multi,r_divisao;


    /* Realiza a leitura ate o valor de "n" estar no intervalo [1, 99] */
    do {
        scanf("%d", &n);
    } while (n <= 0 || n >= 100);

    /* Realiza a leitura ate o valor de "max" estar no intervalo [1, 29] */ 
    do {
        scanf("%d", &max);
    } while (max <= 0 || max >= 30);

    srand(0);

    /* Executa "n" iterações */
    for (int i = 1; i <= n; i++)
    {
        printf("%d:", i);

        r1 = sorteia_r(-max, max);
        r2 = sorteia_r(-max, max);

        imprime_r(r1);
        imprime_r(r2);
        
        if ((!valido_r(r1) || !valido_r(r2) )) /* Se algum dos racionais é invalido Então imprime e encerra o programa */
        {
            printf(" NUMERO INVALIDO\n");
            return 1;
        }

        /* Realiza as operações */
        r_soma = soma_r(r1, r2);
        r_subtracao = subtrai_r(r1, r2);
        r_multi = multiplica_r(r1, r2);
        r_divisao = divide_r(r1, r2);

        if (!valido_r(r_divisao)) /* Se (r1/r2 = invalido) Então imprime DIVISAO INVALIDA e encerra */
        {
            printf(" DIVISAO INVALIDA\n");
            return 1;
        }

        /* Imprime os resultados */
        imprime_r(r_soma);
        imprime_r(r_subtracao);
        imprime_r(r_multi);
        imprime_r(r_divisao);
        printf("\n");
    }
    return 0;
}