/* 

  Este arquivo contém as implementações das funções utilizadas
  para definir e manipular números racionais.
  Utiliza os protótipos definidos no arquivo header "racionais.h"

*/

#include <stdio.h>
#include <stdlib.h>
#include "racional.h"


long aleat(long min, long max) 
{
    return min + rand() % (max - min + 1);
}

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

/* Recebe um número racional e o simplifica. */
struct racional simplifica_r(struct racional r)
{
  int divisor;

  if (r.den == 0)
    return r;

  divisor = mdc(r.num, r.den);

  r.num /= divisor;
  r.den /= divisor;

  if(r.den < 0)
  {
    r.num = -r.num;
    r.den = -r.den;
  }

  return r;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r(long numerador, long denominador)
{
  struct racional r;

  r.num = numerador;
  r.den = denominador;

  return simplifica_r(r);
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r(struct racional r) 
{
    return (r.den != 0);
}

/* Retorna um número racional aleatório na forma simplificada. */
struct racional sorteia_r(long min, long max)
{
  struct racional r;

  r.num = aleat(min, max);
  r.den = aleat(min, max);

  return simplifica_r(r);
}

/* Imprime um racional r */
void imprime_r (struct racional r) 
{
   if (!valido_r(r))
   {
       printf("NaN ");
       return;
   }
   if (r.num == 0)
       printf("0 ");
   else if (r.den == 1)
       printf("%ld ", r.num);
   else if (r.num == r.den)
       printf("1 ");
   else 
       printf("%ld/%ld ", r.num, r.den);
}

/* Compara dois números racionais r1 e r2 */
int compara_r(struct racional r1, struct racional r2) 
{
   
    long numerador1 = r1.num * r2.den;

    long numerador2 = r2.num * r1.den;

    if (!valido_r(r1) || !valido_r(r2))
        return -2;

    if (numerador1 < numerador2) 
        return -1;

    if (numerador1 > numerador2) 
        return 1;

    return 0;
}

/* Retorna a soma dos racionais r1 e r2 e armazena o resultado em r3 */
int soma_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || (r3 == NULL)) /* Verifica se r1 ou r2 são inválidos ou r3 é nulo*/
    return 0;                         // Retorna 0 indicando erro

  long denominador_comum = mmc(r1.den, r2.den); 

  long numerador1 = r1.num * (denominador_comum / r1.den);
  long numerador2 = r2.num * (denominador_comum / r2.den);

  r3->num = numerador1 + numerador2;
  r3->den = denominador_comum;

  *r3 = simplifica_r(*r3);

  return 1; // Retorna 1 indicando sucesso
}

/* Retorna a subtração dos racionais r1 e r2 e armazena o resultado em r3 */
int subtrai_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || (r3 == NULL))
    return 0;                         

  long denominador_comum = mmc(r1.den, r2.den);

  long numerador1 = r1.num * (denominador_comum / r1.den);
  long numerador2 = r2.num * (denominador_comum / r2.den);

  r3->num = numerador1 - numerador2;
  r3->den = denominador_comum;

  *r3 = simplifica_r(*r3);

  return 1;
}

/* Retorna a multiplicação dos racionais r1 e r2 e armazena o resultado em r3 */
int multiplica_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || (r3 == NULL)) 
    return 0;                         

  r3->num = r1.num * r2.num;
  r3->den = r1.den * r2.den;

  *r3 = simplifica_r(*r3);

  return 1;
}

/* Retorna a divisão dos racionais r1 e r2 e armazena o resultado em r3 */
int divide_r(struct racional r1, struct racional r2, struct racional *r3)
{
  if (!valido_r(r1) || !valido_r(r2) || r2.num == 0 || (r3 == NULL)) 
    return 0;                                 

  r3->num = r1.num * r2.den;
  r3->den = r1.den * r2.num;

  *r3 = simplifica_r(*r3);

  return 1;
}
