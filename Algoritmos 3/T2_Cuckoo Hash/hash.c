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
    
    if (h->Tabela1[pos1] == k)
        return 1; // Encontrado em T1
    
    // Se encontrou VAZIO em T1, sabemos que não está na tabela (não existe)
    if (h->Tabela1[pos1] == VAZIO)
        return 0; // Não encontrado

    // Se for REMOVIDO em T1, continuar procurando em T2
    int pos2 = h2(k);

    if (h->Tabela2[pos2] == k)
        return 1; // Encontrado em T2
    
    return 0; // Não encontrado
}


//=====================================================================================


// Insere a chave k na tabela, tratando colisões estilo Cuckoo Hash
void inserir(struct HashTable *h, int k) 
{
    int pos1 = h1(k);

    // Verifica se já existe
    if (busca(h, k)) return;

    // Se posição em Tabela1 estiver vazia ou marcada como REMOVIDA
    if (h->Tabela1[pos1] == VAZIO || h->Tabela1[pos1] == REMOVIDO)
        h->Tabela1[pos1] = k;
    else 
    {
        // Colisão: mover chave antiga ki para Tabela2
        int ki = h->Tabela1[pos1];
        int pos2 = h2(ki);

        // Assumimos que Tabela2 nunca colide (como informado)
        h->Tabela2[pos2] = ki;

        // Inserir a nova chave na Tabela1
        h->Tabela1[pos1] = k;
    }
}


//=====================================================================================


// Remove a chave k (marca como REMOVIDO se for encontrada)
void remover(struct HashTable *h, int k)
{
    int pos2 = h2(k);

    if (h->Tabela2[pos2] == k) 
    {
        // Exclusão direta em T2
        h->Tabela2[pos2] = REMOVIDO;
        return;
    }

    int pos1 = h1(k);

    if (h->Tabela1[pos1] == k)
        // Exclusão em T1 marca como REMOVIDO
        h->Tabela1[pos1] = REMOVIDO;

}


//=====================================================================================


// Imprime as duas tabelas Tabela1 e Tabela2
void imprime(struct HashTable *h)
{
    printf("Tabela 1:\n");
    for (int i = 0; i < M; i++) 
    {
        if (h->Tabela1[i] == VAZIO)
            printf("[%2d] : VAZIO\n", i);
        else if (h->Tabela1[i] == REMOVIDO)
            printf("[%2d] : REMOVIDO\n", i);
        else
            printf("[%2d] : %d\n", i, h->Tabela1[i]);
    }

    printf("\nTabela 2:\n");
    for (int i = 0; i < M; i++) 
    {
        if (h->Tabela2[i] == VAZIO)
            printf("[%2d] : VAZIO\n", i);
        else if (h->Tabela2[i] == REMOVIDO)
            printf("[%2d] : REMOVIDO\n", i);
        else
            printf("[%2d] : %d\n", i, h->Tabela2[i]);
    }
    printf("\n");
}

//=====================================================================================


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

    // Ordenação simples: Bubble Sort
    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = 0; j < count - i - 1; j++) 
        {
            int troca = 0;

            if (lista[j].chave > lista[j + 1].chave) 
            {
                troca = 1;
            } 
            else if (lista[j].chave == lista[j + 1].chave) 
            {
                // mesma chave, T1 antes de T2
                if (strcmp(lista[j].tabela, "T1") > strcmp(lista[j + 1].tabela, "T1")) 
                {
                    troca = 1;
                } 
                else if (strcmp(lista[j].tabela, "T1") == strcmp(lista[j + 1].tabela, "T1")) 
                {
                    // mesma tabela, ordenar pela posição
                    if (lista[j].pos > lista[j + 1].pos) 
                    {
                        troca = 1;
                    }
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

    // Imprime no formato pedido
    for (int i = 0; i < count; i++) 
    {
        printf("%d,%s,%d\n", lista[i].chave, lista[i].tabela, lista[i].pos);
    }
}


//=====================================================================================