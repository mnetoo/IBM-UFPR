#ifndef AVL_H
#define AVL_H



typedef struct No 
{
    int chave;
    int altura;
    struct No* esq;
    struct No* dir;
} No;


No* criar_no(int chave);

No* inserir(No* raiz, int chave);

No* remover(No* raiz, int chave);

void em_ordem(No* raiz);

void liberar_arvore(No* raiz);

#endif
