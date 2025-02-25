#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* retorna um numero aleatorio entre min e max. */
int aleat (int min, int max){
     
    return min + rand() % (max - min + 1);
}

/* Maximo Divisor Comum entre a e b */
int mdc (int a, int b){

    if (b == 0)
        return a;

    return mdc(b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
int mmc (int a, int b){
    
    return (a * b) / mdc (a , b);
}

/* Recebe um numero racional e o simplifica. */
struct racional simplifica_r (struct racional r){
    
    int divisor;

    divisor = mdc(r.num, r.den);

    r.num /= divisor;
    r.den /= divisor;

    return r;
}

/* Cria um numero racional com base nas informacoes dos parametros. */
struct racional cria_r (int numerador, int denominador){
    
    struct racional r;

    r.num = numerador;
    r.den = denominador;
    r.valido = valido_r(r) != 0;


    return r;
}
/*Verifica se o racional eh valido*/
int valido_r (struct racional r){
    
    if (r.den)
        return 0;

    return 1;

}
/* Retorna um numero racional aleatorio na forma simplificada.*/
struct racional sorteia_r (int n){

    struct racional r;

    r.num = aleat (0, n);
    r.den = aleat (0, n);
    r.valido = valido_r(r) != 0;

    return simplifica_r(r);
}

/* Imprime um racional r*/
void imprime_r (struct racional r){

    //Verificar se  valido o racional, caso a condicao do if nao seja imprime invalido
    if (r.valido){
        printf("INVALIDO");
        return;
    }
    //Verifica se o numerador eh igual a 0
    if (!r.num)
        printf("0");
    //Verifica se o numerador e o denominador sao iguais
    else if (r.num == r.den)
        printf("1");
    //Verifica se o denominador for igual a 1 vai imprimir apenas o numerador
    else if (r.den == 1)
        printf(" %d", r.num);
    //Verifica se o racional  negativo (numerador ou denominador)
    else if (r.num > 0 && r.den < 0)
    //Imprime com sinal negativo
        printf(" -%d/%d", r.num, (r.den * -1));
    //Verifica se ambos numerador e denominador forem negativos, o racional eh positivo;
    else if (r.num < 0 && r.den < 0)
    // Imprime valores normais
        printf(" %d/%d", (r.num * -1), (r.den * -1));
    else
    //Imprime o racional normalmente
        printf(" %d/%d ", r.num, r.den);

}


/* Retorna a soma dos racionais r1 e r2.*/
struct racional soma_r(struct racional r1, struct racional r2) { 
    
    struct racional r;

   // printf("numerador do r1 ->%d/%d valido ->%d\n" ,r1.num,r1.den,r1.valido );
    //printf("numerador do r2 ->%d/%d valido ->%d\n" ,r2.num,r2.den,r2.valido );
    r.num = (r1.num * r2.den) + (r2.num * r1.den);
    r.den = r1.den * r2.den;

    r.valido = valido_r(r) != 0;

    return simplifica_r(r);

}

/* Retorna a subtracao dos racionais r1 e r2.*/
struct racional subtrai_r (struct racional r1, struct racional r2){

    struct racional r;

    r.num = (r1.num * r2.den) - (r2.num * r1.den);
    r.den = r1.den * r2.den;

    r.valido = valido_r(r) != 0;

    return simplifica_r(r);

}


/* Retorna a multiplicacao dos racionais r1 e r2.*/
struct racional multiplica_r (struct racional r1, struct racional r2){

    struct racional r;

    r.num = r1.num * r2.num;
    r.den = r1.den * r2.den;

    r.valido = valido_r(r) != 0;

    return simplifica_r(r);

}

/* Retorna a divisao dos racionais r1 e r2.*/
struct racional divide_r (struct racional r1, struct racional r2){

    struct racional r;

     // Verifica se o numerador de r2 é zero para evitar divisão por zero
    if (r2.num == 0) {
        // Retorna uma estrutura de número racional vazia se o numerador de r2 for zero
        r2.valido = 0;
      
    }else{
        r.num = r1.num * r2.den;
        r.den = r2.num * r1.den;

        r.valido = valido_r(r) != 0;
    }

    return simplifica_r(r);

}
