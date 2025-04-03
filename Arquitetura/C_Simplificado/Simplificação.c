#include <stdio.h>

int main() 
{
    // Definição dos vetores (equivalente a armazená-los na memória logo após as instruções)
    int A[10] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
    int B[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int R[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Registradores simulados
    int i = 0;  // Equivalente a um registrador de índice

    // Loop para somar os elementos
    while (i < 10) 
    {
        R[i] = A[i] + B[i];  // Simula uma operação de carga e soma
        i = i + 1;           // Simula um incremento do registrador
    }

    // Exibir resultado (para verificação)
    i = 0;  // Resetando índice para a exibição
    while (i < 10) 
    {
        printf("%d ", R[i]);  // Simula saída do resultado
        i = i + 1;
    }
    printf("\n");

    return 0;
}