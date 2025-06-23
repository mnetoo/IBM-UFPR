#include <stdio.h>
#include <stdlib.h>

#define GRAU_MAXIMO 4
#define GRAU_MINIMO 2



struct tNo 
{
    int chave [GRAU_MAXIMO-1];
    struct tNo *p [GRAU_MAXIMO];
    int tam; 
};

struct tNo *criaNo ();
int token_to_num(const char *str, int *indice);
void emordem(struct tNo *no);
int contaNos(struct tNo *no);
int contaChaves(struct tNo *no);
int altura(struct tNo *p) ;
void splitNo(struct tNo *pai, int indice, struct tNo *no) ;
struct tNo *splitRaiz(struct tNo * raiz);
struct tNo* inclui(struct tNo *no, int chave, struct tNo* raiz);
struct tNo* montaarvore(const char *str);
int indiceChave(struct tNo *no, int chave);
int posicaoSubArvore(struct tNo *no, int chave);
void deslocaDireita(struct tNo *no);
void deslocaEsquerda(struct tNo *no, int indice);
struct tNo* fusionaNo(struct tNo *esq, int chave, struct tNo * dir);
struct tNo *busca (struct tNo *no, int chave) ;
struct tNo* exclui (struct tNo *no, int chave, struct tNo* raiz);
void iniciaprograma();