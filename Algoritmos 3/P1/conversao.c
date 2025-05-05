#include <stdio.h>
#include <stdlib.h>





#define PRETO 0
#define VERMELHO 1

struct rb_node 
{
    int chave;
    int cor; // 0 = PRETO, 1 = VERMELHO
    struct rb_node *esquerda;
    struct rb_node *direita;
    struct rb_node *pai;
};





struct no234 
{
    int num_chaves;
    int chaves[3]; // até 3 chaves
    struct no234 *filhos[4]; // não usados aqui
};






struct rb_node* cria_no_rb(int chave, int cor) 
{
    struct rb_node *n = (struct rb_node*) malloc(sizeof(struct rb_node));

    n->chave = chave;
    n->cor = cor;
    n->esquerda = NULL;
    n->direita = NULL;
    n->pai = NULL;
    return n;
}

struct rb_node* converter_rb(struct no234 *no) 
{
    if (!no) return NULL;

    if (no->num_chaves == 1) 
    {
        return cria_no_rb(no->chaves[0], PRETO);
    }

    else if (no->num_chaves == 2) 
    {
        struct rb_node *pai = cria_no_rb(no->chaves[1], PRETO);
        struct rb_node *filho = cria_no_rb(no->chaves[0], VERMELHO);
        pai->esquerda = filho;
        filho->pai = pai;
        return pai;
    }

    else if (no->num_chaves == 3) 
    {
        struct rb_node *pai = cria_no_rb(no->chaves[1], PRETO);
        struct rb_node *esq = cria_no_rb(no->chaves[0], VERMELHO);
        struct rb_node *dir = cria_no_rb(no->chaves[2], VERMELHO);
        pai->esquerda = esq;
        pai->direita = dir;
        esq->pai = pai;
        dir->pai = pai;
        return pai;
    }

    return NULL;
}




int main() 
{
    // Alocação correta do nó exemplo
    struct no234 *exemplo = (struct no234*) malloc(sizeof(struct no234));

    // Inicializando dados do nó 2-3-4
    exemplo->num_chaves = 3;
    exemplo->chaves[0] = 1;
    exemplo->chaves[1] = 2;
    exemplo->chaves[2] = 3;

    // Conversão para rubro-negra
    struct rb_node *raiz = converter_rb(exemplo);

    // Impressão dos dados
    printf("Raiz: %d [%s]\n", raiz->chave, raiz->cor == PRETO ? "PRETO" : "VERMELHO");
    if (raiz->esquerda)
        printf("Esq: %d [%s] Pai: %d\n", raiz->esquerda->chave, raiz->esquerda->cor == PRETO ? "PRETO" : "VERMELHO", raiz->esquerda->pai->chave);
    if (raiz->direita)
        printf("Dir: %d [%s] Pai: %d\n", raiz->direita->chave, raiz->direita->cor == PRETO ? "PRETO" : "VERMELHO", raiz->direita->pai->chave);

    // Liberação de memória (opcional)
    free(raiz->esquerda);
    free(raiz->direita);
    free(raiz);
    free(exemplo);

    return 0;
}