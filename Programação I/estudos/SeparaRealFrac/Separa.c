#include <stdio.h>

int separa(float r, int *pi, float *pf) {
    if (pi == NULL || pf == NULL) {
        return 0;  // Retorna 0 se houver algum erro (ponteiro nulo)
    }

    *pi = (int)r;  // Parte inteira
    *pf = r - *pi; // Parte fracionária

    return 1; // Retorna 1 se deu certo
}

int main() {
    float r;
    int parte_inteira;
    float parte_fracionaria;

    printf("Digite um número real: ");
    scanf("%f", &r);

    if (separa(r, &parte_inteira, &parte_fracionaria)) {
        printf("Parte inteira: %d\n", parte_inteira);
        printf("Parte fracionária: %.3f\n", parte_fracionaria);
    } else {
        printf("Erro ao separar o número.\n");
    }

    return 0;
}