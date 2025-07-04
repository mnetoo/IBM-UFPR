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

// Função recursiva para realizar a busca binária
int PesqBinRecursiva(int v[], int inicio, int fim, int elemento) 
{
    if (inicio > fim) 
    {
        return 0; // Elemento não encontrado
    }

    int meio = (inicio + fim) / 2;

    if (elemento == v[meio]) 
    {
        return meio; // Retorna o índice do elemento encontrado
    }
    else if (elemento > v[meio]) 
    {
        return PesqBinRecursiva(v, meio + 1, fim, elemento); // Busca na metade direita
    } 
    else 
    {
        return PesqBinRecursiva(v, inicio, meio - 1, elemento); // Busca na metade esquerda
    }
}

int main() 
{
    int v[TAM];
    int n, elemento, resultado;

    scanf("%d", &n);
    lerVetor(n, v);
    scanf("%d", &elemento);

    // Realiza a busca binária recursiva e imprime o resultado
    resultado = PesqBinRecursiva(v, 0, n - 1, elemento);
    
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
