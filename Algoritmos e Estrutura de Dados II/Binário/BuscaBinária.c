#include <stdio.h>

#define TAM 200

// Função para ler os elementos do vetor
void lerVetor(int n, int v[]) 
{

    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &v[i]);
    }
}

// Função para realizar a busca binária
int PesqBin(int n, int elemento, int v[]) {
    int inicio = 0;
    int fim = n - 1;
    int meio;

    while (inicio <= fim) 
    {
        meio = (inicio + fim)/2;
        if (elemento > v[meio]) 
        {
            inicio = meio + 1;
        } 
        else if (elemento < v[meio]) 
        {
            fim = meio - 1;
        } 
        else 
        {
            return meio; // Índice do elemento encontrado
        }
    }
    return 0;
}

int main() 
{
    int v[TAM];
    int n, elemento, resultado;

    scanf("%d", &n);
    lerVetor(n, v);
    scanf("%d", &elemento);

    // Realiza a busca binária e imprime o resultado
    resultado = PesqBin(n, elemento, v);
    if (resultado != 0) 
    {
        printf("%d\n", resultado);
    } 
    else 
    {
        printf("0\n");
    }

    printf("\n");
    return 0;
}