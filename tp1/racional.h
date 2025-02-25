/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de header para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo contém os tipos de dados e protótipos das funções necessárias
 * para definir e manipular números racionais.
 *
 * NÃO ALTERE ESTE ARQUIVO!
*/

#ifndef RACIONAL
#define RACIONAL

/* estrutura que representa um número racional */
struct racional {
  long num;          /* numerador   */
  long den;          /* denominador */
};

/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max);

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b);

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b);

/* Cria um número racional com o numerador e denominador indicados. */
struct racional cria_r (long numerador, long denominador);

/* Retorna 1 se o racional r for válido ou 0 se for inválido.
 * Um racional é inválido se seu denominador for zero */
int valido_r (struct racional r);

/* Retorna um número racional aleatório na forma simplificada.
 * Deve ser sorteado o numerador e depois o denominador.
 * o racional gerado pode ser válido ou inválido.
 * O numerador e o denominador devem ser inteiros entre min e max. */
struct racional sorteia_r (long min, long max);

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r);

/* Imprime um racional r, respeitando estas regras:
   - o racional deve ser impresso na forma simplificada;
   - não imprima espaços em branco e não mude de linha;
   - a saída deve ter o formato "num/den", a menos dos casos abaixo:
     - se o racional for inválido, deve imprimir a mensagem "INVALIDO";
     - se o numerador for 0, deve imprimir somente "0";
     - se o denominador for 1, deve imprimir somente o numerador;
     - se o numerador e denominador forem iguais, deve imprimir somente "1";
     - se o racional for negativo, o sinal "-" deve vir antes do numerador;
     - se numerador e denominador forem negativos, o racional é positivo. */

void imprime_r (struct racional r);

/* Retorna a soma dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional soma_r (struct racional r1, struct racional r2);

/* Retorna a subtração dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional subtrai_r (struct racional r1, struct racional r2);

/* Retorna a multiplicação dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido */
struct racional multiplica_r (struct racional r1, struct racional r2);

/* Retorna a divisão dos racionais r1 e r2.
 * se r1 ou r2 for inválido, o resultado deve ser inválido.
 * observe que a divisão com r1 e r2 válidos pode gerar um racional inválido */
struct racional divide_r (struct racional r1, struct racional r2);

#endif
