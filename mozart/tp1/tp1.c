#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"


int main (){

    struct racional r1,r2;
    struct racional r_soma,r_subtracao;
    struct racional r_multi,r_divisao;
    int max, n, para;

   /*Este loop solicita ao usuario um valor para "n" enquanto o valor 
    inserido estiver fora do intervalo [1, 99]*/
    para = 1;
    do{
        scanf("%d", &n);
        if (n > 0 && n < 100)
            para = 0;
    }while (para);

    /*Este loop solicita ao usuario um valor para "max" enquanto o valor 
    inserido estiver fora do intervalo [1, 29]*/
    para = 1;
    do{
        scanf("%d", &max);
        if (max > 0 && n < 30)
            para = 0;
    }while (para);
    
    srand(0);

    /*Este loop executa "n" iterações, onde "n" eh o valor inserido 
      anteriormente pelo usuário*/

    for (int i = 1; i <= n; i++){
        printf("%d:", i);

        r1 = sorteia_r(max);
        r2 = sorteia_r(max);

        imprime_r(r1);
        imprime_r(r2);
        
     /*Verifica se algum dos números sorteados eh invalido; 
      se sim, imprime "NUMERO INVALIDO" e encerra o programa*/
        if ((valido_r(r1) || valido_r(r2) )){
        printf("NUMERO INVALIDO\n");
        return 1;
        }
        
        /*realiza as operacoes de calcular os numeros reias*/
        r_soma = soma_r(r1, r2);
        r_subtracao = subtrai_r(r1, r2);
        r_multi = multiplica_r(r1, r2);
        r_divisao = divide_r(r1, r2);
        
        /*Verifica se a divisão eh invalida (divisao por zero ou 
          divisao resultando em um número irracional) e, se sim, 
          imprime "DIVISAO INVALIDA" e encerra o programa*/
        if (valido_r(r_divisao)){
            printf("DIVISAO INVALIDA");
            return 1;
        }

        imprime_r(r_soma);
        imprime_r(r_subtracao);
        imprime_r(r_multi);
        imprime_r(r_divisao);
        printf("\n");
    }

    return 0;
}
