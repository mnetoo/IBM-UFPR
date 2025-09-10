#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"



int pertence_ao_conjunto(int id, int *X, int n_X);
void induzir_subgrafo(grafo G, int *X, int n_X);
void atualiza_pesos_incidentes(vertice v);
void atualiza_pesos(grafo G);



int main()
{
    //  PARTE 1 (Grafo Normal)

    // Cria grafo vazio
    grafo G = cria_grafo();

    // Lê n e adiciona vértices 1..n
    int n;
    scanf("%d", &n); // Qtd. vértices

    for (int i = 1; i <= n; ++i)
        adiciona_vertice(i, G);

    // Lê pares u v e adiciona arestas {u,v} e termina quando digitar 0 0
    int id = 1;
    int u, v;
    scanf("%d %d", &u, &v);
    while (u && v)
    {
        adiciona_aresta(id, u, v, G);
        ++id;
        scanf("%d %d", &u, &v);
    }
    
    atualiza_pesos(G);
    printf("\nGrafo:\n");
    imprime_grafo(G);



    //  PARTE 2 (Grafo Induzido)

    // Lê o conjunto X do usuário
    int X[100]; // Suporta até 100 vértices no conjunto X
    int n_X = 0;
    int id_lido;

    printf("\nDigite os IDs dos vértices para o subgrafo G[X]\n");
    printf("(separe com espaço ou enter, termine com -1): ");

    while (scanf("%d", &id_lido) == 1 && id_lido != -1)
        X[n_X++] = id_lido;

    printf("\nConjunto X inserido: { ");
    for (int i = 0; i < n_X; i++)
        printf("%d ", X[i]);
    printf("}\n");

    // Aplica a transformação
    printf("\nProcesso de indução do subgrafo:\n");
    induzir_subgrafo(G, X, n_X);


    printf("\nGrafo Resultante (G[X]):\n");
    imprime_grafo(G);
    destroi_grafo(G);

    return 0;
}