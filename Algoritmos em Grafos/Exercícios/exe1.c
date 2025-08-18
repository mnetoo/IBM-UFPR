#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

int main() 
{
    struct grafo* g = NULL;
    int vertices;
    int u, v;

    printf("Digite a quantidade de vértices do grafo: ");
    scanf("%d", &vertices);

    if (vertices <= 0) 
    {
        printf("Erro: a quantidade de vértices deve ser positiva.\n");
        return 1;
    }

    g = cria_grafo(vertices);

    if (g == NULL) 
    {
        printf("Erro: não foi possível alocar memória para o grafo.\n");
        return 1;
    }

    printf("\nOs vértices do seu grafo são numerados de 1 a %d.\n", vertices);
    printf("Digite os pares de vértices {u, v} para criar as arestas.\n");
    printf("Para encerrar, digite 0 0.\n\n");
    
    printf("Aresta {u, v}: ");
    scanf("%d %d", &u, &v);

    while (u != 0 || v != 0) 
    {
        if ((u < 1 || u > vertices) || (v < 1 || v > vertices))
            printf("Erro: Os vértices precisam estar no intervalo [1, %d]. Tente novamente.\n", vertices);

        else 
        {
            insere_aresta(g, u - 1, v - 1);
            printf(" -> Aresta {%d, %d} inserida.\n", u, v);
        }
        
        printf("Aresta {u, v}: ");
        scanf("%d %d", &u, &v);
    }

    printf("\nGrafo finalizado:\n");
    imprime(g);

    printf("\nAgora, digite o par de vértices (u, v) para encontrar o menor caminho.\n");
    printf("Vértice de origem u: ");
    scanf("%d", &u);
    printf("Vértice de destino v: ");
    scanf("%d", &v);

    // Validação da entrada
    if ((u < 1 || u > vertices) || (v < 1 || v > vertices))
        printf("Erro: Vértices inválidos. Devem estar no intervalo [1, %d].\n", vertices);
    else 
    {
        // Lembre-se de converter para índice 0-based!
        int distancia = encontra_menor_caminho(g, u - 1, v - 1);

        if (distancia != -1)
            printf("\nA menor quantidade de arestas para ir de %d até %d é: %d\n", u, v, distancia);
        else
            printf("\nNão foi possível encontrar um caminho de %d até %d.\n", u, v);
    }
    
    destroi_grafo(g);
    printf("\nGrafo liberado da memória.\n");

    return 0;
}