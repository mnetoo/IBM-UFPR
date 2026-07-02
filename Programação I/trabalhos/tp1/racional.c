#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

long aleat(long min, long max) 
{
    return min + rand() % (max - min + 1);
}

/* Máximo Divisor Comum entre a e b */
long mdc (long a, long b)
{
  if (b == 0)
    return a;

  return mdc(b, a % b);
}

/* Mínimo Múltiplo Comum entre a e b */
long mmc (long a, long b)
{   
  return (a * b) / mdc(a, b);
}

/* Recebe um número racional e o simplifica. */
struct racional simplifica_r(struct racional r)
{
  int divisor;

  if (r.den == 0) return r;

  divisor = mdc(r.num, r.den);

  r.num /= divisor;
  r.den /= divisor;

  return r;
}

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r(long numerador, long denominador)
{
    struct racional r;

    r.num = numerador;
    r.den = denominador;

    return r;
}

/* Retorna 1 se o racional r for válido ou 0 se for inválido. */
int valido_r(struct racional r)
{
  if (r.den == 0)
    return 0;

  return 1;
}

/* Retorna um número racional aleatório na forma simplificada. */
struct racional sorteia_r(long min, long max)
{
  struct racional r;

  r.num = aleat(min, max);
  r.den = aleat(min, max);

  return simplifica_r(r);
}

/* Imprime um racional */
void imprime_r(struct racional r)
{
  if (!valido_r(r)) // Se o racional for inválido, imprime INVALIDO
  {        
    printf(" INVALIDO");
    return;
  }
  
  r = simplifica_r(r);
    
  if (r.num == 0)// Se (numerador = 0) então imprime 0
  {
    printf(" 0");
    return;
  }

  if (r.den == 0) // Se (denominador = 0) então imprime invalido
    printf(" INVALIDO");

  else if (r.num == r.den) // Se (numerador = denominador) então imprime 1
    printf(" 1");
    
  else if (r.den == 1) // Se (denominador = 1) então imprime o numerador
    printf(" %ld", r.num);
    
  else if (r.num > 0 && r.den < 0) // Se (denominador < 0) então imprime -numerador/denominador
    printf(" -%ld/%ld", r.num, (r.den * -1));

  else if (r.num < 0 && r.den < 0) // Se (numerador < 0 && denominador < 0) então imprime racional positivo
    printf(" %ld/%ld", (r.num * -1), (r.den * -1)); 

  else // Imprime o racional normalmente
    printf(" %ld/%ld ", r.num, r.den);
}

/* Retorna a soma dos racionais r1 e r2. */
struct racional soma_r(struct racional r1, struct racional r2)
{ 
  struct racional r;

  if (!valido_r(r1) || !valido_r(r2)) /* Verifica se r1 ou r2 são inválidos */
    return cria_r(0, 0);

  long denominador_comum = mmc(r1.den, r2.den); /* Calcula o mmc dos denominadores */

  /* Ajusta os numeradores com base no denominador comum */
  long numerador1 = r1.num * (denominador_comum / r1.den);    
  long numerador2 = r2.num * (denominador_comum / r2.den);

  /* Soma os numeradores */
  r.num = numerador1 + numerador2;
  r.den = denominador_comum;

  return simplifica_r(r);
}

/* Retorna a subtração dos racionais r1 e r2. */
struct racional subtrai_r(struct racional r1, struct racional r2)
{ 
  struct racional r;

  if (!valido_r(r1) || !valido_r(r2)) /* Verifica se r1 ou r2 são inválidos */
    return cria_r(0, 0);

  long denominador_comum = mmc(r1.den, r2.den); /* Calcula o mmc dos denominadores */

  /* Ajusta os numeradores com base no denominador comum */
  long numerador1 = r1.num * (denominador_comum / r1.den);    
  long numerador2 = r2.num * (denominador_comum / r2.den);

  /* Subtrai os numeradores */
  r.num = numerador1 - numerador2;
  r.den = denominador_comum;

  return simplifica_r(r);
}

/* Retorna a multiplicação dos racionais r1 e r2. */
struct racional multiplica_r(struct racional r1, struct racional r2)
{
  struct racional r;

  if (!valido_r(r1) || !valido_r(r2)) /* Verifica se r1 ou r2 são inválidos */
    return cria_r(0, 0);

  /* Multiplica os numeradores e os denominadores */
  r.num = r1.num * r2.num;
  r.den = r1.den * r2.den;

  return simplifica_r(r);
}

/* Retorna a divisão dos racionais r1 e r2. */
struct racional divide_r(struct racional r1, struct racional r2)
{
  struct racional r;

  if (!valido_r(r1) || !valido_r(r2) || r2.num == 0) /* Verifica se r1 é inválido ou se o numerador de r2 é zero */ 
  {
    /* Retorna um racional inválido */
    return cria_r(0, 0);
  }

  /* Multiplica o primeiro racional pelo inverso do segundo */
  r.num = r1.num * r2.den;
  r.den = r1.den * r2.num;

  return simplifica_r(r);
}