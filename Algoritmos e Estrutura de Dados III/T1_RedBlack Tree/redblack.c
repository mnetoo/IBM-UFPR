/*
    Disciplina: Algoritmos e Estrutura de Dados III.
    Professor: Prof. Dr. Eduardo Cunha de Almeida.
    Aluno: Marcus Sebastião Adriano Rocha Neto.
    GRR: 20240710.
    Curso: Informática Biomédica.
    Descrição: Trabalho 1, implementação Árvore Rubro Negra.
*/

#include <stdlib.h>
#include <stdio.h>
#include "redblack.h"

// Estrutura para simular folha nulas
struct nodo *NILL;


//==========================================================================================


// Função para inicializar o nó sentinela NILL
void inicializa_nill() 
{
    // Aloca memória para o nó NILL
    NILL = malloc(sizeof(struct nodo));
    
    // Define as propriedades do nó sentinela:
    NILL->cor = BLACK;          // NILL é sempre preto
    NILL->esquerda = NILL;      // Aponta para si mesmo
    NILL->direita = NILL;       // Aponta para si mesmo
    NILL->pai = NILL;           // Aponta para si mesmo
}


//==========================================================================================


// Função para criar uma árvore
struct arvore* cria_arvore()
{
    inicializa_nill();

	struct arvore *tree = (struct arvore*) malloc(sizeof(struct arvore));
	tree->raiz = NILL;

    return tree;
}


//==========================================================================================


// Função para criar um novo nó na árvore
struct nodo *cria_nodo(struct nodo *pai, int chave) 
{
    // Aloca memória para o novo nó
    struct nodo *no = malloc(sizeof(struct nodo));

    // Inicializa os campos básicos do nó
    no->chave = chave;          // Armazena o valor da chave
    no->esquerda = NILL;        // Filho esquerdo aponta para NILL
    no->direita = NILL;         // Filho direito aponta para NILL
    no->nivel = 0;              // Inicializa o nível como 0 (pode ser usado para balanceamento)

    // Se o pai for NILL, significa que este é o nó raiz
    if (pai == NILL) 
    {
        no->pai = NILL;         // Raiz não tem pai
        no->cor = BLACK;        // Raiz é sempre preta
    } 
    else 
    {
        // Para nós não-raiz:
        no->cor = RED;          // Novo nó começa como vermelho (propriedade Red-Black Tree)
        no->pai = pai;          // Define o pai do novo nó
    
        // Insere o novo nó como filho esquerdo ou direito do pai
        if (pai->chave > no->chave)
            pai->esquerda = no;  // Se a chave for menor, vai para a esquerda
    
        else if (pai->chave < no->chave)
            pai->direita = no;   // Se a chave for maior, vai para a direita
    }
    
    return no;  // Retorna o novo nó criado
}


//==========================================================================================


// Função para encontrar o nó com a maior chave em uma subárvore
struct nodo *maximum(struct nodo *x)
{
    // Percorre continuamente para a direita até encontrar o nó mais extremo
    while(x->direita != NILL)  // Enquanto houver filho direito
        x = x->direita;        // Avança para o filho direito
        
    // Retorna o nó que não tem mais filhos à direita (o máximo)
    return x;
}


//==========================================================================================


// Função para realizar uma rotação à direita em um nó y
void rot_direita(struct arvore *tree, struct nodo *y)
{
    // x será o filho esquerdo de y (o pivô da rotação)
    struct nodo *x = y->esquerda;
    
    // A subárvore direita de x se torna a subárvore esquerda de y
    y->esquerda = x->direita;
    
    // Se existir a subárvore direita de x, atualiza seu pai para y
    if(x->direita != NILL)
        x->direita->pai = y;
    
    // O pai de x agora é o antigo pai de y
    x->pai = y->pai;
    
    // Atualiza a raiz da árvore se y era a raiz
    if(y->pai == NILL)
        tree->raiz = x;
    
    // Se y era filho esquerdo, atualiza o filho esquerdo do pai
    else if(y == y->pai->esquerda)
        y->pai->esquerda = x;
    
    // Se y era filho direito, atualiza o filho direito do pai
    else
        y->pai->direita = x;
    
    // y se torna filho direito de x
    x->direita = y;
    y->pai = x;
}

// Função para realizar uma rotação à esquerda em um nó x
void rot_esquerda(struct arvore *tree, struct nodo *x)
{
    // y será o filho direito de x (o pivô da rotação)
    struct nodo *y = x->direita;
    
    // A subárvore esquerda de y se torna a subárvore direita de x
    x->direita = y->esquerda;
    
    // Se existir a subárvore esquerda de y, atualiza seu pai para x
    if(y->esquerda != NILL)
        y->esquerda->pai = x;
    
    // O pai de y agora é o antigo pai de x
    y->pai = x->pai;
    
    // Atualiza a raiz da árvore se x era a raiz
    if(x->pai == NILL)
        tree->raiz = y;
    
    // Se x era filho esquerdo, atualiza o filho esquerdo do pai
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    
    // Se x era filho direito, atualiza o filho direito do pai
    else
        x->pai->direita = y;
    
    // x se torna filho esquerdo de y
    y->esquerda = x;
    x->pai = y;
}


//==========================================================================================

//  FUNÇÕES PARA INSERIR VALORS NA ÁRVORE REDBLACK  


// Função para corrigir a árvore após inclusão de novo nó
void inserir_fixup(struct arvore *t, struct nodo *z) 
{
    // Enquanto o pai for vermelho (violação)
    while (z->pai != NILL && z->pai->cor == RED) 
    {
        // Caso 1: Pai é filho esquerdo do avô
        if (z->pai == z->pai->pai->esquerda) 
        {
            struct nodo *y = z->pai->pai->direita;  // Tio
            int cor_y = (y != NILL) ? y->cor : BLACK;

            // Subcaso: Tio vermelho
            if (cor_y == RED) 
            {
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;  // Move o problema para cima
            } 
            // Subcaso: Tio preto
            else 
            {
                // Subcaso 1.2.1: Nó é filho direito (forma de linha)
                if (z == z->pai->direita) 
                {
                    z = z->pai;
                    rot_esquerda(t, z);  // Transforma em forma de gancho
                }
                // Subcaso: Nó é filho esquerdo (forma de gancho)
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rot_direita(t, z->pai->pai);
            }
        } 
        // Caso 2: Pai é filho direito do avô (simétrico ao Caso 1)
        else 
        {
            struct nodo *y = z->pai->pai->esquerda;  // Tio
            int cor_y = (y != NILL) ? y->cor : BLACK;

            if (cor_y == RED) 
            {
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            } 
            else 
            {
                if (z == z->pai->esquerda) 
                {
                    z = z->pai;
                    rot_direita(t, z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rot_esquerda(t, z->pai->pai);
            }
        }
    }
    t->raiz->cor = BLACK;  // Garante que a raiz seja sempre preta
    ajustar_nivel(t->raiz, 0);
}

// Função para inserir mum valor na árvore BST
void inserir(struct arvore *t, struct nodo *z) 
{
    // Encontrar a posição de inserção
    struct nodo *y = NILL;  // Nó pai do novo nó
    struct nodo *x = t->raiz;  // Nó atual para busca
    
    while (x != NILL) 
    {
        y = x;
        if (z->chave < x->chave)
            x = x->esquerda;
        else
            x = x->direita;
    }

    // Inserir o novo nó
    z->pai = y;
    
    if (y == NILL)  // Árvore vazia
        t->raiz = z;
    else if (z->chave < y->chave)
        y->esquerda = z;
    else
        y->direita = z;

    // Inicializar propriedades do novo nó
    z->esquerda = NILL;
    z->direita = NILL;
    z->cor = RED;  // Novo nó sempre começa como vermelho
    
    // Aplicar correções se necessário
    if (z != t->raiz)
        inserir_fixup(t, z);  // Corrigir violações de propriedade
    else
        z->cor = BLACK;  // Raiz sempre preta
}


//==========================================================================================

//  FUNÇÕES PARA REMOVER VALORES DA ÁRVORE REDBLACK


// Função para buscar um nó com uma chave específica em uma árvore binária
struct nodo *busca_no(struct nodo *n, int no_procurado) 
{
    // Caso base 1: chegou a um nó folha (nó não existe)
    if (n == NILL)
        return NILL;

    // Caso base 2: encontrou o nó com a chave correspondente
    if (n->chave == no_procurado)
        return n;

    // Caso recursivo 1: busca primeiro na subárvore esquerda
    // (Implementa uma abordagem de busca em profundidade - DFS)
    struct nodo *resultado = busca_no(n->esquerda, no_procurado);

    // Se encontrou na subárvore esquerda, retorna imediatamente
    // (Otimiza a busca parando quando encontra)
    if (resultado != NILL) 
        return resultado;
    
    // Caso recursivo 2: se não encontrou na esquerda, busca na direita
    // (Só busca na direita se a busca na esquerda não teve sucesso)
    return busca_no(n->direita, no_procurado);
}

// Função para transplantar (substituir) uma subárvore por outra
void transplante(struct arvore *tree, struct nodo *u, struct nodo *v)
{
    // Caso 1: 'u' é a raiz da árvore
    if(u->pai == NILL)
        tree->raiz = v;  // 'v' se torna a nova raiz

    // Caso 2: 'u' é filho esquerdo de seu pai
    else if(u == u->pai->esquerda)
        u->pai->esquerda = v;  // Substitui 'u' por 'v' na esquerda
    
    // Caso 3: 'u' é filho direito de seu pai
    else
        u->pai->direita = v;  // Substitui 'u' por 'v' na direita
    
    // Atualiza o pai de 'v' para ser o pai de 'u'
    // (Nota: isso funciona mesmo quando v é NILL)
    v->pai = u->pai;
}

// Função para corrigir a árvore após a exclusão de um nó
void remover_fixup(struct arvore *t, struct nodo *x) 
{
    struct nodo *w; // Irmão de x

    while (x != t->raiz && x->cor == BLACK) 
    {
        // Caso esquerdo
        if (x == x->pai->esquerda) 
        {
            w = x->pai->direita;

            // Caso 1: Irmão vermelho -> transforma no caso 2, 3 ou 4
            if (w->cor == RED) 
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_esquerda(t, x->pai);
                w = x->pai->direita;
            }

            // Caso 2: Irmão preto com filhos pretos
            if (w->esquerda->cor == BLACK && w->direita->cor == BLACK) 
            {
                w->cor = RED;
                x = x->pai; // Propaga o problema para cima
            }
            else 
            {
                // Caso 3: Irmão preto com filho esquerdo vermelho e direito preto
                if (w->direita->cor == BLACK) 
                {
                    w->esquerda->cor = BLACK;
                    w->cor = RED;
                    rot_direita(t, w);
                    w = x->pai->direita;
                }

                // Caso 4: Irmão preto com filho direito vermelho
                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->direita->cor = BLACK;
                rot_esquerda(t, x->pai);
                x = t->raiz; // Termina o loop
            }
        }
        else 
        { // Caso direito (simétrico)
            w = x->pai->esquerda;

            if (w->cor == RED) 
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                rot_direita(t, x->pai);
                w = x->pai->esquerda;
            }

            if (w->direita->cor == BLACK && w->esquerda->cor == BLACK) 
            {
                w->cor = RED;
                x = x->pai;
            }
            else 
            {
                if (w->esquerda->cor == BLACK) 
                {
                    w->direita->cor = BLACK;
                    w->cor = RED;
                    rot_esquerda(t, w);
                    w = x->pai->esquerda;
                }

                w->cor = x->pai->cor;
                x->pai->cor = BLACK;
                w->esquerda->cor = BLACK;
                rot_direita(t, x->pai);
                x = t->raiz;
            }
        }
    }
    x->cor = BLACK; // Garante propriedade da raiz
    ajustar_nivel(t->raiz, 0);
}

// Função para excluir um nó da árvore
void remover(struct arvore *t, struct nodo *z) 
{
    struct nodo *x;          // Nó que substituirá
    struct nodo *y = z;       // Nó a ser removido ou movido
    int yCorOriginal = y->cor; // Guarda a cor original para verificar violações

    // Caso 1: Nó tem no máximo um filho (direito)
    if(z->esquerda == NILL) 
    {
        x = z->direita;
        transplante(t, z, z->direita); // Substitui z por seu filho direito
    }

    // Caso 2: Nó tem no máximo um filho (esquerdo)
    else if(z->direita == NILL) 
    {
        x = z->esquerda;
        transplante(t, z, z->esquerda); // Substitui z por seu filho esquerdo
    }

    // Caso 3: Nó tem dois filhos
    else 
    { 
        // Encontra o predecessor (máximo da subárvore esquerda)
        y = maximum(z->esquerda);
        yCorOriginal = y->cor;
        x = y->esquerda;

        // Se y é filho direto de z
        if(y->pai == z)
            x->pai = y; // Atualiza o pai de x
    
        else 
        {
            // Transplanta y por seu filho esquerdo
            transplante(t, y, y->esquerda);
            // Ajusta os ponteiros da subárvore esquerda
            y->esquerda = z->esquerda;
            y->esquerda->pai = y;
        }

        // Transplanta z por y
        transplante(t, z, y);
        // Ajusta os ponteiros da subárvore direita
        y->direita = z->direita;
        y->direita->pai = y;
        y->cor = z->cor; // Mantém a cor original de z
    }

    // Se a cor original do nó removido/movido era preta, pode ter violações
    if(yCorOriginal == BLACK)
        remover_fixup(t, x); // Corrige possíveis violações
}


//==========================================================================================


// Função para ajustar níveis dos nós
void ajustar_nivel(struct nodo *no, int nivel) 
{
    if (no == NILL)
        return;

    no->nivel = nivel;

    ajustar_nivel(no->esquerda, nivel + 1);
    ajustar_nivel(no->direita, nivel + 1);
}


//==========================================================================================


// Função para imprimir a árvore (EM ORDEM)
void imprimir(struct nodo *no) 
{
    if (no == NILL)
        return;

    imprimir(no->esquerda);
    printf("%d,%d,%d\n", no->chave, no->nivel, no->cor);
    imprimir(no->direita);
}


//==========================================================================================


// Função auxiliar recursiva para liberar os nós
void libera_nos(struct nodo *no) 
{
    if (no == NILL || no == NULL)
        return;
    
    // Libera os filhos recursivamente
    libera_nos(no->esquerda);
    libera_nos(no->direita);
    
    // Libera o nó atual
    free(no);
}

// Função para destruir a árvore e liberar memória
void destruir_arvore(struct arvore *arvore) 
{
    if (arvore == NULL) 
        return;

    // Libera todos os nós a partir da raiz
    libera_nos(arvore->raiz);

    // Libera o nó NILL, se ele foi alocado dinamicamente
    if (NILL != NULL)
    {
        free(NILL);
        NILL = NULL;
    }
        

    // Libera a estrutura da árvore
    free(arvore);
}


//==========================================================================================