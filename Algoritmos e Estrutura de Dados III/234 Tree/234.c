#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "234.h"

#define MAX_NOS_POR_NIVEL 1000







// Cria um novo nó
No234* criarNo(int chave, int folha) 
{
    No234 *novo = (No234*)malloc(sizeof(No234));
    novo->num_chaves = 1;
    novo->chaves[0] = chave;
    novo->folha = folha;

    for (int i = 0; i < ORDEM; i++)
        novo->filhos[i] = NULL;

    return novo;
}



// Divide um filho cheio em dois
void dividirFilho(No234 *pai, int i) 
{
    No234 *cheio = pai->filhos[i];
    No234 *novo = (No234*)malloc(sizeof(No234));

    novo->folha = cheio->folha;
    novo->num_chaves = 1;
    novo->chaves[0] = cheio->chaves[2]; // terceira chave vai para o novo

    if (!cheio->folha) 
    {
        for (int j = 0; j < 2; j++)
            novo->filhos[j] = cheio->filhos[j + 2];
    }

    cheio->num_chaves = 1;

    // Move filhos do pai
    for (int j = pai->num_chaves; j >= i + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];

    pai->filhos[i + 1] = novo;

    // Move chaves do pai
    for (int j = pai->num_chaves - 1; j >= i; j--)
        pai->chaves[j + 1] = pai->chaves[j];

    pai->chaves[i] = cheio->chaves[1]; // chave do meio sobe
    pai->num_chaves++;
}



// Insere chave em nó não cheio, fazendo split top-down
void inserirNaoCheio(No234 *no, int chave) 
{
    int i = no->num_chaves - 1;

    if (no->folha) 
    {
        // Move as chaves para abrir espaço
        while (i >= 0 && chave < no->chaves[i]) 
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }

        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } 
    else 
    {
        // Encontra o filho correto
        while (i >= 0 && chave < no->chaves[i])
            i--;

        i++;

        // Se o filho estiver cheio, divide antes de descer
        if (no->filhos[i]->num_chaves == ORDEM - 1) 
        {
            dividirFilho(no, i);
            // Após dividir, pode haver mudança na direção de descida
            if (chave > no->chaves[i]) 
                i++;

        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}



// Insere e faz split se o nó ficar com 3 chaves após inserção
void inserirComSplit(No234 **raiz, No234 *pai, int indice_filho, int chave) 
{
    No234 *no = *raiz;

    // Se for folha, insere normalmente
    int i = no->num_chaves - 1;

    if (no->folha) 
    {
        while (i >= 0 && chave < no->chaves[i]) 
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->num_chaves++;
    } 
    else 
    {
        // Encontra o filho onde deve inserir
        while (i >= 0 && chave < no->chaves[i])
            i--;

        i++;
        inserirComSplit(&no->filhos[i], no, i, chave);
    }

    // Se após a inserção o nó ficou com 3 chaves, faz split
    if (no->num_chaves == ORDEM - 1) 
    {
        if (pai == NULL) 
        {
            // Split da raiz
            No234 *novaRaiz = (No234 *)malloc(sizeof(No234));
            novaRaiz->folha = 0;
            novaRaiz->num_chaves = 0;
            novaRaiz->filhos[0] = no;

            dividirFilho(novaRaiz, 0);
            *raiz = novaRaiz;
        } 
        else
            dividirFilho(pai, indice_filho);
    }
}




void inserir(No234 **raiz, int chave) 
{
    if (*raiz == NULL)
        *raiz = criarNo(chave, 1);
    else
        inserirComSplit(raiz, NULL, 0, chave);
}



// Imprime a árvore (por nível)
void imprimir(No234 *raiz, int nivel) 
{
    if (raiz == NULL) return;

    printf("Nível %d: ", nivel);
    for (int i = 0; i < raiz->num_chaves; i++) 
    {
        printf("%d ", raiz->chaves[i]);
    }
    printf("\n");

    for (int i = 0; i <= raiz->num_chaves; i++)
        imprimir(raiz->filhos[i], nivel + 1);

}



// Libera memória
void liberarArvore(No234 *raiz) 
{
    if (raiz == NULL) return;

    for (int i = 0; i <= raiz->num_chaves; i++)
        liberarArvore(raiz->filhos[i]);

    free(raiz);
}



// Imprime a árvore em formato hierárquico
void imprimirArvoreFormatada(No234 *no, int nivel) 
{
    if (no == NULL) return;

    // Espaçamento por nível
    for (int i = 0; i < nivel; i++)
        printf("  ");

    // Imprime o nó atual
    printf("[");

    for (int i = 0; i < no->num_chaves; i++) 
    {
        printf("%d", no->chaves[i]);
        if (i < no->num_chaves - 1)
            printf(" ");
    }
    printf("]\n");

    // Recursivamente imprime os filhos
    for (int i = 0; i <= no->num_chaves; i++)
        imprimirArvoreFormatada(no->filhos[i], nivel + 1);
}


// Imprime a árvore 2-3-4 no estilo "deitado", com filhos à direita acima
void imprimirArvoreHorizontal(No234 *no, int nivel) {
    if (no == NULL) return;

    for (int i = no->num_chaves; i >= 0; i--) {
        if (no->filhos[i])
            imprimirArvoreHorizontal(no->filhos[i], nivel + 1);

        if (i < no->num_chaves) {
            for (int j = 0; j < nivel; j++)
                printf("       "); // espaçamento entre níveis

            printf("[");
            for (int k = 0; k < no->num_chaves; k++) {
                printf("%d", no->chaves[k]);
                if (k < no->num_chaves - 1)
                    printf(" ");
            }
            printf("]\n");
            break;  // imprime o nó apenas uma vez
        }
    }
}




int alturaArvore(No234 *no) {
    if (no == NULL) return 0;
    int max = 0;
    for (int i = 0; i <= no->num_chaves; i++) {
        int h = alturaArvore(no->filhos[i]);
        if (h > max) max = h;
    }
    return max + 1;
}

void imprimirNivel(No234 *nivel[], int num_nos, int nivel_atual, int altura_total) {
    if (num_nos == 0) return;
    
    // Cálculo dinâmico dos espaços baseado na altura e nível
    int espaco_antes = (1 << (2*(altura_total - nivel_atual - 1))) - 1;
    int espaco_entre = (1 << (2*(altura_total - nivel_atual))) - 1;
    
    // Imprime os nós do nível atual com espaçamento correto
    for (int i = 0; i < num_nos; i++) {
        printf("%*s", (i == 0) ? espaco_antes : espaco_entre, "");
        
        if (nivel[i] != NULL) {
            printf("[");
            for (int j = 0; j < nivel[i]->num_chaves; j++) {
                printf("%d", nivel[i]->chaves[j]);
                if (j < nivel[i]->num_chaves - 1) printf(",");
            }
            printf("]");
        } else {
            printf("[ ]");
        }
    }
    printf("\n");
}

void imprimirArvoreVertical(No234 *raiz) {
    if (!raiz) {
        printf("Árvore vazia.\n");
        return;
    }

    int altura = alturaArvore(raiz);
    No234 *nivel_atual[MAX_NOS_POR_NIVEL];
    No234 *proximo_nivel[MAX_NOS_POR_NIVEL];
    int num_nivel = 1;
    
    nivel_atual[0] = raiz;

    for (int i = 0; i < altura; i++) {
        imprimirNivel(nivel_atual, num_nivel, i, altura);
        
        int idx = 0;
        for (int j = 0; j < num_nivel; j++) {
            if (nivel_atual[j] != NULL) {
                // Adiciona todos os filhos (2, 3 ou 4)
                for (int k = 0; k <= nivel_atual[j]->num_chaves; k++) {
                    proximo_nivel[idx++] = nivel_atual[j]->filhos[k];
                }
            } else {
                // Adiciona NULLs para manter a estrutura
                for (int k = 0; k < 4; k++) {
                    proximo_nivel[idx++] = NULL;
                }
            }
        }
        
        memcpy(nivel_atual, proximo_nivel, idx * sizeof(No234*));
        num_nivel = idx;
    }
}