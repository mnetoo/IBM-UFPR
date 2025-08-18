#include "grafos.h"
#include <stdio.h>  // Adicionado para printf
#include <stdlib.h> // Adicionado para malloc, calloc e free

//===========================================================

//
struct grafo* cria_grafo(int numVertices) 
{
    // Verifica se o número de vértices é válido
    if (numVertices <= 0) {
        return NULL;
    }

    struct grafo* g = (struct grafo*) malloc(sizeof(struct grafo));
    if (g == NULL) {
        return NULL; // Falha na alocação
    }
    
    g->numVertices = numVertices;

    // Aloca as linhas da matriz
    g->matriz = (int**) malloc(numVertices * sizeof(int*));
    if (g->matriz == NULL) {
        free(g);
        return NULL; // Falha na alocação
    }

    // CORREÇÃO: O loop deve ir de 0 a numVertices - 1
    for (int i = 0; i < numVertices; i++) {
        // Aloca as colunas para cada linha e inicializa com 0
        g->matriz[i] = (int*) calloc(numVertices, sizeof(int));
        if (g->matriz[i] == NULL) {
            // Em caso de falha, libera toda a memória já alocada
            for(int j = 0; j < i; j++) {
                free(g->matriz[j]);
            }
            free(g->matriz);
            free(g);
            return NULL;
        }
    }

    return g;
}

//===========================================================

//
void insere_aresta(struct grafo* g, int origem, int destino) 
{
    // A verificação está correta para índices baseados em 0 (de 0 a numVertices-1)
    if (g == NULL || origem < 0 || origem >= g->numVertices || destino < 0 || destino >= g->numVertices) {
        return;
    }

    g->matriz[origem][destino] = 1;
    g->matriz[destino][origem] = 1; // Grafo não-direcionado
}

//===========================================================

//
void remove_aresta(struct grafo* g, int origem, int destino) 
{
    // A verificação está correta para índices baseados em 0
    if (g == NULL || origem < 0 || origem >= g->numVertices || destino < 0 || destino >= g->numVertices) {
        return;
    }

    g->matriz[origem][destino] = 0;
    g->matriz[destino][origem] = 0;
}

//===========================================================

//
int verifica_aresta(struct grafo* g, int origem, int destino) 
{
    if (g == NULL || origem < 0 || origem >= g->numVertices || destino < 0 || destino >= g->numVertices) {
        return 0; // Retorna 0 se os vértices forem inválidos
    }

    return g->matriz[origem][destino];
}

//===========================================================

//
void imprime(struct grafo* g) 
{
    if (g == NULL || g->matriz == NULL) {
        printf("Grafo inválido ou não inicializado.\n");
        return;
    }

    printf("Matriz de Adjacência:\n");
    printf("   ");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d ", i + 1);
    }
    printf("\n--+");
    for (int i = 0; i < g->numVertices; i++) {
        printf("--");
    }
    printf("\n");

    // CORREÇÃO: Os loops devem ir de 0 a numVertices - 1
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d | ", i + 1); // Imprime o índice da linha para melhor visualização
        for (int j = 0; j < g->numVertices; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

//===========================================================

//
void destroi_grafo(struct grafo* g) 
{
    if (g == NULL) {
        return;
    }

    // CORREÇÃO: O loop deve corresponder ao loop de alocação (0 a numVertices-1)
    // O loop original já estava correto, mas agora ele é consistente com a alocação corrigida.
    if (g->matriz != NULL) {
        for (int i = 0; i < g->numVertices; i++) {
            free(g->matriz[i]); // Libera cada linha (vetor de colunas)
        }
        free(g->matriz); // Libera o vetor de linhas
    }
    
    free(g); // Libera a estrutura do grafo
}

//===========================================================


// NOVA FUNÇÃO: Multiplica duas matrizes quadradas de tamanho n x n
int** multiplica_matrizes(int** mat1, int** mat2, int n) 
{
    // 1. Aloca memória para a nova matriz que será o resultado
    int** resultado = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        resultado[i] = (int*) calloc(n, sizeof(int));
    }

    // 2. Executa a multiplicação (três loops aninhados)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Para cada célula [i][j] do resultado...
            resultado[i][j] = 0; // Inicia com zero
            for (int k = 0; k < n; k++) {
                // ...somamos os produtos de mat1[i][k] * mat2[k][j]
                resultado[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    // 3. Retorna a matriz resultante
    return resultado;
}


//===========================================================


// Encontra o menor caminho usando multiplicações
int encontra_menor_caminho(struct grafo* g, int origem, int destino)
{
    // Caso especial: se a origem e o destino são os mesmos, a distância é 0.
    if (origem == destino) {
        return 0;
    }

    int n = g->numVertices;
    int** matriz_potencia = NULL;
    int** matriz_temporaria = NULL;

    // Aloca e copia a matriz de adjacência original (A¹) para começar
    matriz_potencia = (int**) malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        matriz_potencia[i] = (int*) malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            matriz_potencia[i][j] = g->matriz[i][j];
        }
    }

    // Loop para calcular as potências A¹, A², A³, ...
    // O maior caminho simples possível em um grafo tem n-1 arestas.
    for (int k = 1; k < n; k++) 
    {
        // Passo 1: Verifica se na matriz da potência atual (A^k) já existe um caminho.
        // Se matriz_potencia[origem][destino] > 0, significa que encontramos
        // um ou mais caminhos de comprimento 'k'. Como estamos indo em ordem (k=1, 2, 3...),
        // o primeiro que encontrarmos será o menor.
        if (matriz_potencia[origem][destino] > 0) {
            // Limpamos a memória alocada antes de retornar
            for (int i = 0; i < n; i++) free(matriz_potencia[i]);
            free(matriz_potencia);
            return k; // Retorna o comprimento do caminho
        }

        // Passo 2: Se não encontramos, preparamos a próxima potência (A^(k+1)).
        // Calculamos A^(k+1) = A^k * A
        matriz_temporaria = multiplica_matrizes(matriz_potencia, g->matriz, n);

        // Passo 3: Liberamos a memória da matriz de potência antiga (A^k)
        for (int i = 0; i < n; i++) free(matriz_potencia[i]);
        free(matriz_potencia);

        // Passo 4: A nossa "matriz_potencia" agora é o resultado do cálculo (A^(k+1))
        matriz_potencia = matriz_temporaria;
    }

    // Se o loop terminar, significa que não foi encontrado um caminho
    // (mas o enunciado garante que sempre há um).
    // Liberamos a última matriz calculada.
    for (int i = 0; i < n; i++) free(matriz_potencia[i]);
    free(matriz_potencia);
    
    return -1; // Retorno para caso de erro/não encontrar
}