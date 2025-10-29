#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#define MAX_VERTICES 2048
#define MAX_NOME_LEN 100
#define MAX_LINE_LEN 1024


//===========================================================================================================


//  tipo do vértice: reação ou metabólito
typedef enum { REACAO, METABOLITO } tipo_vertice;

//  estrutura para associar nomes, IDs e tipos de vértices
typedef struct {
    char nome[MAX_NOME_LEN];
    int id;
    tipo_vertice tipo;
} mapa_vertices;


//  vetor global para nomes e IDs
static mapa_vertices vetor_vertices[MAX_VERTICES];

//  contador para o próximo ID disponível de vértice
static int proximo_id_disponivel = 0;

//  estados para a busca em profundidade
#define ABERTO 0
#define PROCESSANDO 1
#define FECHADO 2


//=====================================================================================================================================


//  procura vértice por um nome no mapa se não encontrar cria um novo vértice no grafo, se encontrar retorna o ID existente
int obtem_ou_cria_id_vertice(char *nome, tipo_vertice tipo, grafo G) 
{
    //  verifica se o vértice já existe
    for (int i = 0; i < proximo_id_disponivel; i++) 
    {
        if (strcmp(vetor_vertices[i].nome, nome) == 0)
            return vetor_vertices[i].id;
    }


    //  se não existe cria novo vértice
    int id = proximo_id_disponivel++;
    if (id >= MAX_VERTICES) 
    {
        fprintf(stderr, "Erro: Número máximo de vértices excedido.\n");
        exit(1);
    }
    
    //  adiociona o novo vértice no vetor global de vértices
    strcpy(vetor_vertices[id].nome, nome);
    vetor_vertices[id].id = id;
    vetor_vertices[id].tipo = tipo;

    //  adiciona no grafo
    adiciona_vertice(id, G);

    return id;
}


//=====================================================================================================================================


//  retorna 1 se achar ciclo e 0 se não
//  se não achar ciclo empilha na lista para a ornemação topológica
int DFS(vertice u, grafo G, int *status, lista ordenacao)
{
    int u_id = vertice_id(u);
    status[u_id] = PROCESSANDO;     //  marca o vértice

    //  passa por todos os vizinhos de u
    for (no n = primeiro_no(fronteira(u)); n; n = proximo(n)) 
    {
        aresta arco = (aresta) conteudo(n);
        vertice v = vertice_v(arco);    //  v é o destino
        int v_id = vertice_id(v);

        //  se encontrar um vizinho que está sendo PROCESSADO encontrou um ciclo
        if (status[v_id] == PROCESSANDO) 
            return 1;
        
        if (status[v_id] == ABERTO) 
        {
            //  visita o vizinho recursivamente
            if (DFS(v, G, status, ordenacao))
                return 1; 
        }
    }

    status[u_id] = FECHADO;     //  marca o vértice
    
    //  para a ordenação topológica empilha o vértice na lista
    empilha(u, ordenacao);

    return 0;
}


//=====================================================================================================================================



int main(int argc, char *argv[]) 
{
    //  verifica argumentos
    if (argc != 2) 
    {
        printf("Uso: %s <arquivo.met>\n", argv[0]);
        return 1;
    }

    //  abre o arquivo
    FILE *arquivo = fopen(argv[1], "r");
    if (!arquivo) 
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    //  inicializa o grafo e variáveis
    grafo G = cria_grafo();
    char buffer_linha[MAX_LINE_LEN];
    int proximo_id_arco = 0;

    //  lê arquivo e constrói grafo
    while (fgets(buffer_linha, sizeof(buffer_linha), arquivo)) 
    {
        //  remove quebra de linha se tiver
        buffer_linha[strcspn(buffer_linha, "\r\n")] = 0;

        char *token;
        char *rest = buffer_linha;

        //  pega o nome da reação
        char *nome_reacao_str = strtok_r(rest, " ", &rest);
        if (!nome_reacao_str) continue;
        int id_reacao = obtem_ou_cria_id_vertice(nome_reacao_str, REACAO, G);

        //  processa substratos
        while ((token = strtok_r(rest, " ", &rest)) && strcmp(token, "->") != 0) 
        {
            if (strcmp(token, "+") != 0) 
            {
                int id_metabolito = obtem_ou_cria_id_vertice(token, METABOLITO, G);
                
                //  adiciona direção na aresta (METABÓLITO -> REAÇÃO)
                cria_direcao(proximo_id_arco++, id_metabolito, id_reacao, G);
            }
        }
        
        //  processa produtos
        while ((token = strtok_r(rest, " ", &rest))) 
        {
             if (strcmp(token, "+") != 0) 
             {
                int id_metabolito = obtem_ou_cria_id_vertice(token, METABOLITO, G);

                //  adiciona direção na aresta (REAÇÃO -> METABÓLITO)
                cria_direcao(proximo_id_arco++, id_reacao, id_metabolito, G);
            }
        }
    }

    fclose(arquivo);

    //  detecta ciclo faz ordenação topológica
    int status_visita[proximo_id_disponivel];
    for (int i = 0; i < proximo_id_disponivel; i++)
        status_visita[i] = ABERTO;
    
    int ciclo_encontrado = 0;
    lista resultado_ordenado = cria_lista();

    //  faz busca em profundidade para cada vértice não fechado
    for (no n_vert = primeiro_no(vertices(G)); n_vert; n_vert = proximo(n_vert)) 
    {
        vertice v = (vertice) conteudo(n_vert);

        if (status_visita[vertice_id(v)] == ABERTO)
        {
            if (DFS(v, G, status_visita, resultado_ordenado)) 
            {
                ciclo_encontrado = 1;
                break;
            }
        }
    }

    //  imprime do resultado
    if (ciclo_encontrado)
        printf("rede cíclica\n");
    else 
    {
        //  lista "resultado_ordenado" está na ordem inversa (porque empilhamos).
        //  imprimir do início ao fim da lista resulta em uma ordenação topológica válida.
        no no_atual = primeiro_no(resultado_ordenado);
        while(no_atual) 
        {
            vertice v_atual = (vertice) conteudo(no_atual);
            int id_v = vertice_id(v_atual);

            //  imprime apenas se for um metabólito
            if (vetor_vertices[id_v].tipo == METABOLITO)
                printf("%s ", vetor_vertices[id_v].nome);

            no_atual = proximo(no_atual);
        }
        printf("\n");
    }

    //  libera memória
    destroi_lista(resultado_ordenado);
    destroi_grafo(G);

    return 0;
}