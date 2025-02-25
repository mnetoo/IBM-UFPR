#include <stdio.h>


// - n: número de discos a mover
// - origem: o pino de onde os discos estão sendo movidos
// - destino: o pino para onde os discos devem ser movidos
// - auxiliar: o pino auxiliar usado no processo



void hanoi(int n, char origem, char destino, char auxiliar) 
{
    // Caso base: Se houver apenas 1 disco, mova diretamente da origem para o destino
    if (n == 1) 
    {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }

    // Passo 1: Mover n-1 discos da origem para o pino auxiliar, usando o destino como auxiliar
    hanoi(n - 1, origem, auxiliar, destino);
    
    // Passo 2: Mover o disco maior (n) da origem para o destino
    printf("\n");
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    printf("\n");

    // Passo 3: Mover os n-1 discos do pino auxiliar para o destino, usando a origem como auxiliar
    hanoi(n - 1, auxiliar, destino, origem);
}

int main() {
    int n;  // Variável para armazenar o número de discos

    // Solicita ao usuário que insira o número de discos
    printf("Digite o número de discos: ");
    scanf("%d", &n);
    printf("\n");

    // Imprimir uma introdução ao problema
    printf("Resolvendo as Torres de Hanoi para %d discos:\n", n);
    printf("\n");

    // Chamamos a função recursiva para resolver o problema
    // Inicialmente, todos os discos estão na torre A, e precisamos movê-los para a torre C
    // Usamos a torre B como torre auxiliar
    hanoi(n, 'A', 'C', 'B');

    return 0;
}