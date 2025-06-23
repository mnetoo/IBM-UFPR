#include "arvore.h"



struct tNo *criaNo ()
{
    struct tNo *n = (struct tNo *)malloc(sizeof (struct tNo));
    n->tam = 0;

    for (int i=0; i < GRAU_MAXIMO ;i++)
        n->p[i] = NULL;

    return n;
}

//====================================================================================

int token_to_num(const char *str, int *indice)
{    
    char token[100];
    int i = 0;
    while (str[*indice] != '\0' && str[*indice] != ' ')
    {
        token[i] = str[*indice];
        i++;
        (*indice)++;
    }
    token[i] = '\0';
    (*indice)++;    
    return atoi(token);
}

//====================================================================================

void emordem(struct tNo *no)
{    
    if (no != NULL) 
    {
        for (int i=0; i < no->tam; i++)
        {
            emordem(no->p[i]);
            printf("%d ", no->chave[i]);
        }
        emordem(no->p[no->tam]);
    }
}

//====================================================================================

int contaNos(struct tNo *no)
{
    int nos = 0; 
    if (no != NULL) 
    {
        for (int i=0; i < no->tam; i++)        
            nos += contaNos(no->p[i]);
            
        nos += contaNos(no->p[no->tam]);
        nos += 1;
    }
    return nos;
}

//====================================================================================

int contaChaves(struct tNo *no)
{
    int chaves = 0; 
    if (no != NULL) 
    {
        for (int i=0; i < no->tam; i++)          
            chaves += contaChaves(no->p[i]) + 1;

        chaves += contaChaves(no->p[no->tam]);
    }
    return chaves;
}

//====================================================================================

int altura(struct tNo *p) 
{
    int i = 0;
    while (p->p[0] != NULL)
    {
        p = p->p[0];
        i ++;
    }
    return i;
}

//====================================================================================

void splitNo(struct tNo *pai, int indice, struct tNo *no) 
{
    struct tNo *novo = criaNo();
    novo->tam = GRAU_MINIMO - 1;
    //atribui chaves da segunda metade para o novo nó
    for (int i=0; i < GRAU_MINIMO-1; i++)
        novo->chave[i] = no->chave[i+GRAU_MINIMO];

    //atribui os pointeiros da segunda metade, se não é folha
    if (no->p[0]  != NULL) 
    {//novo->chave[i]
        for (int i=0; i <= GRAU_MINIMO-1; i++)
            novo->p[i] = no->p[i + GRAU_MINIMO];
    }

    no->tam = GRAU_MINIMO - 1;

    //desloca os ponteiros do nó pai para a direita
    for (int i = pai->tam;  i > indice; i--)
        pai->p[i+1] = pai->p[i];

    //ultimo indice aponta para o novo nó
    pai->p[indice+1] = novo;

    //desloca as chaves do pai para a direita
    for (int i = pai->tam-1; i >= indice; i--)
        pai->chave[i+1] = pai->chave[i];

    //sobe a chave
    pai->chave[indice] = no->chave[GRAU_MINIMO-1];
    pai->tam = pai->tam +1;
}

//====================================================================================

struct tNo *splitRaiz(struct tNo * raiz)
{
    struct tNo *novaRaiz = criaNo();

    splitNo(novaRaiz, 0, raiz);

    novaRaiz->p[0]=raiz;
    novaRaiz->p[0]->tam = GRAU_MINIMO - 1;

    return novaRaiz;
}

//====================================================================================

struct tNo* inclui(struct tNo *no, int chave, struct tNo* raiz)
{
    int i = no->tam -1;
    struct tNo *filho;

    if (no->tam == GRAU_MAXIMO - 1 && no == raiz) 
    {//split na raiz, tratamento específico
        raiz = splitRaiz(raiz);
        no = raiz;
        i = no->tam - 1;
    }   

    if (no->p[0] == NULL)
    { //encontrou um nó folha para inclusão
        while(i >= 0 && chave < no->chave[i]) 
        {
            no->chave[i+1] = no->chave[i];
            i--;
        }

        no->chave[i+1] = chave;
        no->tam = no->tam+1;
    } 
    else 
    { //desce na árvore e faz o split se necessário
        while (i >= 0 && chave < no->chave[i])
            i--;

        i++;
        filho = no->p[i];

        if (filho->tam == GRAU_MAXIMO - 1)
        {
            splitNo(no, i, filho);

            if (chave > no->chave[i]) 
                i ++;
        }
        inclui( no->p[i], chave, raiz);    
    }
    return raiz;
}

//====================================================================================

struct tNo* montaarvore(const char *str)
{
    struct tNo *raiz = NULL;
    int i = 0, v =0;

    raiz = criaNo();

    while (str[i]!='\0')
        raiz = inclui (raiz, token_to_num(str, &i), raiz);

    return raiz;        
}

//====================================================================================

int indiceChave(struct tNo *no, int chave)
{
    int i;
    for (i = 0; i < no->tam && no->chave[i] != chave; i++);
    return i;
}

//====================================================================================

int posicaoSubArvore(struct tNo *no, int chave)
{
    int i = no->tam -1;

    while (i >= 0 && chave < no->chave[i])
        i--;

    i++;    
    return i;
}

//====================================================================================

void deslocaDireita(struct tNo *no)
{
    int i;
    for (i=no->tam ; i > 0 ; i--)
    {
        no->chave[i] = no->chave[i-1];
        no->p[i+1] = no->p[i];
    }

    no->p[i+1] = no->p[i];
}

//====================================================================================

void deslocaEsquerda(struct tNo *no, int indice)
{
    int i;
    for (i=indice ; i < no->tam ; i++)
    {
        no->chave[i] = no->chave[i+1];
        no->p[i] = no->p[i+1];
    }

    no->p[i] = no->p[i+1];
}

//====================================================================================

struct tNo* fusionaNo(struct tNo *esq, int chave, struct tNo * dir)
{
    int tamEsq = esq->tam;
    esq->chave[tamEsq] = chave;
    int i;
    tamEsq++;
    esq->tam ++;

    for (i=0; i < dir->tam; i++)
    {//copia chaves e ponteiros da direita para no esquerdo
        esq->chave[tamEsq + i] = dir->chave[i];
        esq->p[tamEsq + i] = dir->p[i];
    }

    esq->p[tamEsq + i] = dir->p[i];
    esq->tam = esq->tam + dir->tam;
    free(dir);

    return esq;
}

//====================================================================================

struct tNo *busca (struct tNo *no, int chave) 
{
    if( no != NULL )
    { 
        for(int i=0; i < no->tam; i++) 
        {
            if( no->chave[i] == chave ) 
                return no; 
            else 
                if( chave < no->chave[i] ) 
                    return busca( no->p [i], chave ); 
        }
        return busca( no->p[ no->tam ], chave ); 
    }
    else
        return NULL;
}

//====================================================================================

struct tNo* exclui (struct tNo *no, int chave, struct tNo* raiz)
{
    int j, i = no->tam -1;
    int aux=0, excluiuCaso2 = 0;
    struct tNo *filho, *irmao, *sucessor, *antecessor;

    if (indiceChave(no, chave) == 0 && no->tam == 1 && no == raiz) 
    {//split na raiz
        printf("\nExcluiu nó raiz");
        free(no);
        return NULL;
    }   

    if (no->p[0] == NULL)
    { //Caso 1: chave está no nó e é folha
        printf("\nCaso 1: nó folha");

        //encontra o indice da chave
        j = indiceChave(no, chave);

        if (j == no->tam) return NULL; //não encontrou a chave

        while (j < no->tam) 
        { 
            no->chave[j] = no->chave[j+1];
            j++;
        }
        no->tam = no->tam-1;
    } 
    else 
    { //desce na árvore e faz o merge se necessário
        j = indiceChave(no, chave);
        i = posicaoSubArvore(no, chave); 

        if (j < no->tam) 
        {
            //Caso 2: encontrou a chave em nó interno
            if (no->p[j] != NULL && no->p[j]->tam >= GRAU_MINIMO) 
            {
                printf("\nCaso 2.antecessor");

                antecessor = no->p[j];

                while (antecessor->p[antecessor->tam - 1] != NULL)
                    antecessor = antecessor->p[antecessor->tam - 1];

                no->chave[j] = antecessor->chave[antecessor->tam -1];

                exclui(no->p[j], antecessor->chave[antecessor->tam-1],raiz);
            } 
            else 
            {
                if (no->p[j+1] != NULL && no->p[j+1]->tam >= GRAU_MINIMO) 
                {
                    printf("\nCaso 2.sucessor");

                    sucessor = no->p[j+1];

                    while (sucessor->p[0] != NULL)
                        sucessor = sucessor->p[0];

                    no->chave[j] = sucessor->chave[0];

                    exclui(sucessor, sucessor->chave[0], raiz);
                }
                else 
                {
                    printf("\nCaso 2.sem grau mínimo");

                    filho = fusionaNo(no->p[j], no->chave[j], no->p[j+1]);

                    no->chave[j] = no->chave[j+1];

                    deslocaEsquerda(no, j+1);

                    no->tam --;

                    exclui(filho, chave, raiz);              
                }
            } 
        }
        else 
        { //Caso 3: não encontrou a chave em nó interno
            filho = no->p[i]; //sub arvore da chave

            if (no->p[i]->tam == GRAU_MINIMO - 1)
            {
                if ( (i-1)>=0 && no->p[i-1]->tam >= GRAU_MINIMO)
                {
                    printf("\nCaso 3.a.esq)"); //filho esquerdo com ao menos t chaves
                    irmao = no->p[i-1];
                    aux = no->chave[i-1]; 
                    irmao->tam --;
                    no->chave[i-1] = irmao->chave[irmao->tam];

                    deslocaDireita(filho);

                    filho->tam ++;
                    filho->chave[0] = aux;
                    filho->p[0] = irmao->p[irmao->tam+1];
                }
                else 
                {
                    if ((i+1) <= no->tam && no->p[i+1]->tam >= GRAU_MINIMO)
                    {
                        printf("\nCaso 3.a.dir)"); //filho direito com ao menos t chaves

                        irmao = no->p[i+1];
                        aux = no->chave[i]; 
                        irmao->tam --;
                        no->chave[i] = irmao->chave[0];

                        deslocaEsquerda(irmao, 0);

                        filho->tam ++;
                        filho->chave[filho->tam-1] = aux;
                        filho->p[filho->tam] = irmao->p[0];                        
                    }
                    else 
                    { //fusao de nós
                        printf("\nCaso 3.b)");

                        if (i == 0)
                        {//primeiro nó, fusiona com o direito
                            filho = fusionaNo(filho, no->chave[0], no->p[i+1]);

                            no->chave[0] = no->chave[1];

                            deslocaEsquerda(no, i+1);
                        } 
                        else 
                        { //fusiona com o esquerdo
                            filho = fusionaNo(no->p[i-1], no->chave[i-1], filho);

                            no->chave[i-1] = no->chave[i];

                            deslocaEsquerda(no, i);
                            i--;
                        }
                        no->tam --;
                    }   
                }
                
            }
        exclui( no->p[i], chave, raiz);
        }
    }
    return raiz;
}

//====================================================================================

void iniciaprograma()
{
    struct tNo *raiz = NULL;

    //char entrada[] = "20 13 17 22 11 23 12 9 25 21 18 19\0";
    char entrada[] = "10 2 12 20 25 30\0";
    raiz=montaarvore(entrada); 


    exclui(raiz, 30, raiz);
    exclui(raiz, 10, raiz);

    printf("\nEm-ordem: \n");
    emordem(raiz); 
    printf("Total de nós: %d\n", contaNos(raiz));
    printf("Total de chaves: %d\n", contaChaves(raiz)); 
}

//====================================================================================