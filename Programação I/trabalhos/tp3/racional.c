/*

Este arquivo contém as implementações das funções utilizadas
para definir e manipular números racionais.
Utiliza os protótipos definidos no arquivo header "racional.h"

*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

/* Máximo Divisor Comum entre a e b */
long mdc(long a, long b)
{
    if (b == 0)
        return a;

    return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc(long a, long b)
{
    return (a * b) / mdc(a, b);
}

/* Simplifica o número racional indicado no parâmetro */
int simplifica_r(struct racional *r)
{
    if (r == NULL || r->den == 0)
        return 0; // Retorna 0 em caso de erro: ponteiro nulo ou denominador zero

    int divisor = mdc(r->num, r->den);

    r->num /= divisor;
    r->den /= divisor;

    // Se o denominador for negativo, ajusta os sinais
    if (r->den < 0)
    {
        r->num = -r->num;
        r->den = -r->den;
    }

    return 1; // Retorna 1 em sucesso
}

/* Cria um número racional com o numerador e denominador indicados e retorna um ponteiro que aponta para ele.*/
struct racional *cria_r(long numerador, long denominador)
{
    // Aloca memória para um novo número racional
    struct racional *r = malloc(sizeof(struct racional));

    // Verifica se a alocação foi bem-sucedida
    if (r == NULL)
        return NULL; // Retorna NULL se não conseguiu alocar memória

    r->num = numerador;
    r->den = denominador;

    simplifica_r(r);

    return r;
}

/* Libera a memória alocada para o racional apontado por r */
void destroi_r(struct racional *r)
{
    if (r != NULL)
    {
        free(r);  // Libera a memória alocada para o número racional
        r = NULL; // Evita ponteiros "pendurados"
    }
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido */
int valido_r(struct racional *r)
{
    if (r == NULL)
        return 0;

    return (r->den != 0); // Retorna 1 se o denominador não for zero, caso contrário retorna 0
}

/* Imprime um racional r */
void imprime_r(struct racional *r)
{
    if (r == NULL)
    {
        printf(" NULL");
        return;
    }

    if (!valido_r(r))
    {
        printf(" NaN");
        return;
    }

    if (r->num == 0) // Se o numerador for 0, imprime "0"
        printf(" 0");

    else if (r->den == 1) // Se o denominador for 1, imprime somente o numerador
        printf(" %ld", r->num);

    else if (r->num == r->den) // Se o numerador e o denominador forem iguais, imprime "1"
        printf(" 1");

    else // Formato padrão "num/den"
    {
        if (r->num < 0 || r->den < 0) // Imprime o sinal negativo se o numerador for negativo
            printf(" %ld/%ld", -labs(r->num), labs(r->den));
        else
            printf(" %ld/%ld", r->num, r->den);
    }
}

/* Compara dois números racionais r1 e r2 */
int compara_r(struct racional *r1, struct racional *r2)
{
    if (r1 == NULL || r2 == NULL)
        return -2; // Retorna -2 se algum ponteiro for nulo

    if (!valido_r(r1) || !valido_r(r2))
        return -2; // Retorna -2 se algum racional não for válido

    long denominador_mmc = mmc(r1->den, r2->den);

    long numerador1 = r1->num * (denominador_mmc / r1->den);
    long numerador2 = r2->num * (denominador_mmc / r2->den);

    if (numerador1 < numerador2)
        return -1; // r1 é menor que r2

    if (numerador1 > numerador2)
        return 1; // r1 é maior que r2

    return 0; // r1 é igual a r2
}

/* Coloca em *r3 a soma simplificada dos racionais *r1 e *r2 */
int soma_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (r1 == NULL || r2 == NULL || r3 == NULL || !valido_r(r1) || !valido_r(r2))
        return 0; // Retorna 0 indicando erro

    long denominador_comum = mmc(r1->den, r2->den);

    long numerador1 = r1->num * (denominador_comum / r1->den);
    long numerador2 = r2->num * (denominador_comum / r2->den);

    r3->num = numerador1 + numerador2;
    r3->den = denominador_comum;

    simplifica_r(r3);

    return 1;
}

/* Coloca em *r3 a diferença simplificada dos racionais *r1 e *r2 */
int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3)
{

    if (r1 == NULL || r2 == NULL || r3 == NULL || !valido_r(r1) || !valido_r(r2))
        return 0; // Retorna 0 indicando erro

    long denominador_comum = mmc(r1->den, r2->den);

    long numerador1 = r1->num * (denominador_comum / r1->den);
    long numerador2 = r2->num * (denominador_comum / r2->den);

    r3->num = numerador1 - numerador2;
    r3->den = denominador_comum;

    simplifica_r(r3);

    return 1;
}

/* Coloca em *r3 o produto simplificado dos racionais *r1 e *r2 */
int multiplica_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (r1 == NULL || r2 == NULL || r3 == NULL || !valido_r(r1) || !valido_r(r2))
        return 0; // Retorna 0 indicando erro

    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den;

    simplifica_r(r3);

    return 1;
}

/* Coloca em *r3 a divisão simplificada do racional *r1 por *r2 */
int divide_r(struct racional *r1, struct racional *r2, struct racional *r3)
{
    if (r1 == NULL || r2 == NULL || r3 == NULL || !valido_r(r1) || !valido_r(r2) || r2->num == 0)
        return 0; // Retorna 0 indicando erro

    r3->num = r1->num * r2->den;
    r3->den = r1->den * r2->num;

    simplifica_r(r3);

    return 1;
}
