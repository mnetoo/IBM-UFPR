#include "hash.h"


//=====================================================================================


// Inicializa as duas tabelas com o valor VAZIO
void inicializa_hash(struct HashTable *h) 
{
    for (int i = 0; i < M; i++) 
    {
        h->Tabela1[i] = VAZIO;
        h->Tabela2[i] = VAZIO;
    }
}


//=====================================================================================


// Função hash 1
int h1(int k) 
{
    return k % M;
}


//=====================================================================================


// Função hash 2
int h2(int k) 
{
    double mult = k * 0.9;
    double fracao = mult - floor(mult);

    return (int)(floor(M * fracao));
}


//=====================================================================================


// Busca a chave k nas tabelas Tabela1 e Tabela2
int busca(struct HashTable *h, int k) 
{
    int pos1 = h1(k);
    
    // Se a chave está em Tabela1 na posição pos1
    if (h->Tabela1[pos1] == k)
        return pos1; // Encontrado em T1, retorna posição em T1
    
    // Se posição em T1 estiver vazia, sabemos que não está na tabela
    if (h->Tabela1[pos1] == VAZIO)
        return -1; // Não encontrado

    // Se for REMOVIDO em T1 ou outra chave, tenta em T2
    int pos2 = h2(k);

    if (h->Tabela2[pos2] == k)
        return pos2; // Encontrado em T2, retorna posição em T2

    return -1; // Não encontrado
}


//=====================================================================================


// Insere a chave k na tabela, tratando colisões estilo Cuckoo Hash
int inserir(struct HashTable *h, int k) 
{
    int pos1 = h1(k);

    // Se a chave já existe, não insere novamente
    if (busca(h, k) != -1)
        return -1;

    // Se a posição em T1 está vazia ou foi removida
    if (h->Tabela1[pos1] == VAZIO || h->Tabela1[pos1] == REMOVIDO) 
    {
        h->Tabela1[pos1] = k;
        return pos1; // Inserido em T1
    } 
    else 
    {
        // Colisão: chave ki já está na posição de T1
        int ki = h->Tabela1[pos1];
        int pos2 = h2(ki);

        // Move ki para T2 (assumindo que nunca colide em T2)
        h->Tabela2[pos2] = ki;

        // Agora T1[pos1] está livre para nova chave k
        h->Tabela1[pos1] = k;
        return pos1; // Inserido em T1 após mover ki para T2
    }
}

//=====================================================================================


// Remove a chave k (marca como REMOVIDO se for encontrada)
int remover(struct HashTable *h, int k)
{
    int pos2 = h2(k);

    if (h->Tabela2[pos2] == k) 
    {
        // Exclusão direta em T2
        h->Tabela2[pos2] = REMOVIDO;
        return 1;
    }

    int pos1 = h1(k);

    if (h->Tabela1[pos1] == k)
    {
        // Exclusão em T1: marcar como REMOVIDO (não usar VAZIO)
        h->Tabela1[pos1] = REMOVIDO;
        return 1;
    }

    // Se não encontrou em nenhuma tabela
    return 0;
}


//=====================================================================================

//  Função para imprimir saída formatada
void imprimeHash(struct HashTable *h) 
{
    struct EntradaHash 
    {
        int chave;
        char tabela[3];
        int pos;
    };

    struct EntradaHash lista[2 * M];
    int count = 0;

    // Copia chaves de T1
    for (int i = 0; i < M; i++) 
    {
        if (h->Tabela1[i] != VAZIO && h->Tabela1[i] != REMOVIDO) 
        {
            lista[count].chave = h->Tabela1[i];
            lista[count].pos = i;
            strcpy(lista[count].tabela, "T1");
            count++;
        }
    }

    // Copia chaves de T2
    for (int i = 0; i < M; i++) 
    {
        if (h->Tabela2[i] != VAZIO && h->Tabela2[i] != REMOVIDO) 
        {
            lista[count].chave = h->Tabela2[i];
            lista[count].pos = i;
            strcpy(lista[count].tabela, "T2");
            count++;
        }
    }

    // Ordenação usando bubble Sort
    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = 0; j < count - i - 1; j++) 
        {
            int troca = 0;

            if (lista[j].chave > lista[j + 1].chave) 
                troca = 1;
            else if (lista[j].chave == lista[j + 1].chave) 
            {
                // mesma chave, T1 antes de T2
                if (strcmp(lista[j].tabela, "T1") > strcmp(lista[j + 1].tabela, "T1")) 
                    troca = 1;
                else if (strcmp(lista[j].tabela, "T1") == strcmp(lista[j + 1].tabela, "T1")) 
                {
                    // mesma tabela, ordenar pela posição
                    if (lista[j].pos > lista[j + 1].pos) 
                        troca = 1;
                }
            }

            if (troca) 
            {
                struct EntradaHash temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }

    // Imprime no formatado
    for (int i = 0; i < count; i++) 
        printf("%d,%s,%d\n", lista[i].chave, lista[i].tabela, lista[i].pos);
}


//=====================================================================================