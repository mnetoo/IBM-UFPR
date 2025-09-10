/*******************************************
 * Implementação de biblioteca para grafos.
 * Versão: lista + matriz interna (matriz dinâmica)
 *
 * Mantém interface original (não altera grafo.h).
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>


//=================================================================================


/* ---------------------------------------------------------------------
   Estrutura interna para mapear cada grafo (ponteiro) para sua matriz
   e arrays auxiliares (mapeamento id <-> índice).
   ------------------------------------------------------------------ */
typedef struct matinfo 
{
  grafo G;               // ponteiro para o grafo correspondente
  int capacidade;        // capacidade (linhas/colunas alocadas)
  int *mapa_indice_para_id;  // tamanho = capacidade; -1 indica vaga livre
  int **matriz;          // capacidade x capacidade
  struct matinfo *prox;  // lista ligada de matinfos
} MatInfo;

// lista ligada de MatInfo
static MatInfo *cabeca_matriz = NULL;


//=================================================================================


//  Procura MatInfo pelo grafo G 
static MatInfo *procura_matinfo(grafo G) 
{
  for (MatInfo *m = cabeca_matriz; m; m = m->prox)
    if (m->G == G) return m;

  return NULL;
}


//=================================================================================


//  Cria e adiciona MatInfo para um grafo recém-criado
static MatInfo *cria_matinfo(grafo G, int capacidade_inicial) 
{
  MatInfo *m = (MatInfo *) malloc(sizeof(MatInfo));
  if (!m) 
    exit(_ERRO_MALLOC_);

  m->G = G;

  if (capacidade_inicial < 4) 
    capacidade_inicial = 4;

  m->capacidade = capacidade_inicial;
  m->mapa_indice_para_id = (int *) malloc(sizeof(int) * m->capacidade);

  if (!m->mapa_indice_para_id) 
    exit(_ERRO_MALLOC_);

  for (int i = 0; i < m->capacidade; ++i) 
    m->mapa_indice_para_id[i] = -1;

  m->matriz = (int **) malloc(sizeof(int *) * m->capacidade);

  if (!m->matriz) 
    exit(_ERRO_MALLOC_);

  for (int i = 0; i < m->capacidade; ++i) 
  {
    m->matriz[i] = (int *) malloc(sizeof(int) * m->capacidade);
    if (!m->matriz[i]) 
    {
      exit(_ERRO_MALLOC_);
    }
    
      for (int j = 0; j < m->capacidade; ++j) 
      m->matriz[i][j] = 0;
  }

  m->prox = cabeca_matriz;
  cabeca_matriz = m;
  return m;
}


//=================================================================================


//  Libera MatInfo associado a G
static void destroi_matinfo(grafo G) 
{
  MatInfo **pp = &cabeca_matriz;

  while (*pp) 
  {
    if ((*pp)->G == G) 
    {
      MatInfo *m = *pp;
      *pp = m->prox;

      for (int i = 0; i < m->capacidade; ++i)
        free(m->matriz[i]);
  
      free(m->matriz);
      free(m->mapa_indice_para_id);
      free(m);
      return;
    }
    pp = &((*pp)->prox);
  }
}


//=================================================================================


// Encontra índice livre ou existente para dado id
static int indice_de_id(MatInfo *m, int id) 
{
  for (int i = 0; i < m->capacidade; ++i)
    if (m->mapa_indice_para_id[i] == id) 
      return i;

  return -1;
}


//=================================================================================


//  Encontra uma vaga livre
static int procura_indice_livre(MatInfo *m) 
{
  for (int i = 0; i < m->capacidade; ++i)
    if (m->mapa_indice_para_id[i] == -1) 
      return i;

  return -1;
}


//=================================================================================


//  Expande a capacidade da MatInfo (dobrando)
static void expande_matinfo(MatInfo *m) 
{
  int nova_cap = m->capacidade * 2;
  int **nova_matriz = (int **) malloc(sizeof(int *) * nova_cap);

  if (!nova_matriz) 
    exit(_ERRO_MALLOC_);
  
  for (int i = 0; i < nova_cap; ++i) 
  {
    nova_matriz[i] = (int *) malloc(sizeof(int) * nova_cap);
    if (!nova_matriz[i]) 
      exit(_ERRO_MALLOC_);
  }

  // inicializa novo com zeros
  for (int i = 0; i < nova_cap; ++i)
    for (int j = 0; j < nova_cap; ++j)
      nova_matriz[i][j] = 0;

  // copia a matriz antiga
  for (int i = 0; i < m->capacidade; ++i)
    for (int j = 0; j < m->capacidade; ++j)
      nova_matriz[i][j] = m->matriz[i][j];

  // libera a antiga
  for (int i = 0; i < m->capacidade; ++i)
    free(m->matriz[i]);
  free(m->matriz);

  // expande mapa
  m->mapa_indice_para_id = (int *) realloc(m->mapa_indice_para_id, sizeof(int) * nova_cap);
  
  if (!m->mapa_indice_para_id)
  {
    exit(_ERRO_MALLOC_);
  } 
  
    for (int i = m->capacidade; i < nova_cap; ++i) 
      m->mapa_indice_para_id[i] = -1;

  m->matriz = nova_matriz;
  m->capacidade = nova_cap;
}


//=================================================================================


//  Garante que exista um índice para o id
static int garante_indice_para_id(MatInfo *m, int id) 
{
  int idx = indice_de_id(m, id);

  if (idx != -1) 
    return idx;

  int livre = procura_indice_livre(m);

  if (livre == -1) 
  {
    expande_matinfo(m);
    livre = procura_indice_livre(m);

    if (livre == -1) 
      exit(_ERRO_MALLOC_);
  }

  m->mapa_indice_para_id[livre] = id;
  return livre;
}


//=================================================================================


//  Remove id da tabela (marca vaga livre) e zera linhas/colunas
static void remove_indice_para_id(MatInfo *m, int id) 
{
  int idx = indice_de_id(m, id);

  if (idx == -1) 
    return;

  for (int j = 0; j < m->capacidade; ++j) 
  {
    m->matriz[idx][j] = 0;
    m->matriz[j][idx] = 0;
  }
  m->mapa_indice_para_id[idx] = -1;
}


//=================================================================================


//  Seta peso na matriz (0 remove)
static void matriz_set_peso(MatInfo *m, int u_id, int v_id, int peso) 
{
  int iu = indice_de_id(m, u_id);
  int iv = indice_de_id(m, v_id);

  if (iu == -1 || iv == -1) 
  {
    return;
  }
  
  m->matriz[iu][iv] = peso;
  m->matriz[iv][iu] = peso;
}


//=================================================================================


int vertice_id(vertice v) {
  return v->id;
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

static int get_vertice_id(obj v) {
  return vertice_id((vertice) v);
}

static int get_aresta_id(obj e) {
  return aresta_id((aresta) e);
}


//=================================================================================


//  Verifica se um id pertence a um conjunto de inteiros X.
int pertence_ao_conjunto(int id, int *X, int n_X) 
{
  for (int i = 0; i < n_X; i++) 
    if (X[i] == id)
      return 1;

  return 0;
}


//=================================================================================


//  Transforma o grafo G no seu subgrafo induzido G[X].
void induzir_subgrafo(grafo G, int *X, int n_X) 
{
  no n_vert = primeiro_no(vertices(G));
  
  // Passa pela lista de vértices de forma segura para remoção
  while (n_vert) 
  {
    no proximo_n = proximo(n_vert);

    vertice v = (vertice) conteudo(n_vert);
    int v_id = vertice_id(v);

    // Verifica se o vértice atual deve ser removido
    if (!pertence_ao_conjunto(v_id, X, n_X)) 
    {
      // Se não pertence a X, remove do grafo
      printf("-> Removendo vértice %d (não pertence a X).\n", v_id);
      remove_vertice(v_id, G);
    }

    n_vert = proximo_n;
  }
}


//=================================================================================


//  Funções para lidar com os pesos
static void atualiza_pesos_incidentes(vertice v) 
{
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n)) 
  {
    aresta e = (aresta) conteudo(n);

    // peso = grau(u) + grau(v)
    e->peso = grau(vertice_u(e)) + grau(vertice_v(e));
  }
}


//=================================================================================



void atualiza_pesos(grafo G)
{
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n))
  {
    vertice v = (vertice)conteudo(n);
    atualiza_pesos_incidentes(v);
  }

  // após recalcular pesos nas arestas atualiza matriz
  MatInfo *m = procura_matinfo(G);

  if (!m) 
    return;

  for (no na = primeiro_no(arestas(G)); na; na = proximo(na)) 
  {
    aresta e = (aresta) conteudo(na);
    int uid = vertice_id(vertice_u(e));
    int vid = vertice_id(vertice_v(e));
    matriz_set_peso(m, uid, vid, e->peso);
  }
}


//=================================================================================


//  Cria grafo vazio e o retorna
grafo cria_grafo()
{
  grafo G = (grafo) malloc(sizeof(t_grafo));

  if (!G) 
    exit(_ERRO_MALLOC_);

  G->vertices = cria_lista();
  G->arestas = cria_lista();

  // cria matriz associada ao grafo
  cria_matinfo(G, 4);

  return G;
}


//=================================================================================


//  Destroi grafo G
void destroi_grafo(grafo G)
{
  MatInfo *m = procura_matinfo(G);

  // Passa a lista de arestas, removendo uma a uma e liberando a memória
  while (!vazio(arestas(G)))
  {
    aresta e = (aresta) desempilha(arestas(G));
    free(e);
  }

  // Passa a lista de vertices, fazendo o mesmo. 
  // Para cada vértice, primeiro esvaziamos sua lista de fronteira
  while (!vazio(vertices(G)))
  {
    vertice v = (vertice) desempilha(vertices(G));

    // esvazia a lista de fronteira
    while (!vazio(fronteira(v)))
    {
      // desempilha apenas o conteúdo
      (void) desempilha(fronteira(v));
    }

    free(fronteira(v));
    free(v);
  }

  // libera as estruturas das listas principais
  free(arestas(G));
  free(vertices(G));

  if (m) 
    destroi_matinfo(G);

  free(G);
}

//=================================================================================


//  Cria novo vertice com id e adiciona ao grafo G
void adiciona_vertice(int id, grafo G)
{
  // evita duplicatas
  vertice existente = (vertice) busca_chave(id, vertices(G), get_vertice_id);
  if (existente) 
    return;

  vertice v = (vertice) malloc(sizeof(t_vertice));
  if (!v) 
    exit(_ERRO_MALLOC_);

  v->id = id;
  v->fronteira = cria_lista();

  // empilha o novo vértice na lista de vértices do grafo.
  empilha(v, vertices(G));

  // cria índice na matriz
  MatInfo *m = procura_matinfo(G);

  if (m)
    garante_indice_para_id(m, id);
}


//=================================================================================


//  Remove vertice com id do grafo G e o destroi
void remove_vertice(int id, grafo G)
{
  // Busca o vértice com o id fornecido na lista de vértices do grafo
  vertice v = (vertice) busca_chave(id, vertices(G), get_vertice_id);

  if (!v)
    return;

  MatInfo *m = procura_matinfo(G);

  // Passa sobre todas as arestas na fronteira do vértice v
  while (!vazio(fronteira(v)))
  {
    // remove a primeira aresta da fronteira de v
    aresta e = (aresta) desempilha(fronteira(v));

    // encontra o outro vértice conectado pela aresta e
    vertice outro_v = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);

    // remove a aresta e da fronteira do outro vértice.
    remove_chave(aresta_id(e), fronteira(outro_v), get_aresta_id);

    // remove a aresta e da lista principal de arestas do grafo.
    remove_chave(aresta_id(e), arestas(G), get_aresta_id);

    // atualiza matriz
    if (m) 
    {
      int u_id = vertice_id(vertice_u(e));
      int v_id = vertice_id(vertice_v(e));
      matriz_set_peso(m, u_id, v_id, 0);
    }

    free(e);
  }

  // remove o vértice v da lista de vértices do grafo.
  remove_chave(id, vertices(G), get_vertice_id);

  free(fronteira(v));
  free(v);

  // remove índice da matriz
  if (m) 
    remove_indice_para_id(m, id);
}


//=================================================================================


///  Cria aresta com id incidente a vertices
void adiciona_aresta(int id, int u_id, int v_id, grafo G)
{
  // busca pelos ponteiros dos vértices u e v usando seus IDs.
  vertice u = (vertice) busca_chave(u_id, vertices(G), get_vertice_id);
  vertice v = (vertice) busca_chave(v_id, vertices(G), get_vertice_id);

  if (!u || !v)
    return;

  aresta ja = (aresta) busca_chave(id, arestas(G), get_aresta_id);
  if (ja) 
    return;
  
  aresta e = (aresta) malloc(sizeof(t_aresta));
  if (!e) 
    exit(_ERRO_MALLOC_);

  e->id = id;
  e->u = u;
  e->v = v;

  // conecta a aresta ao grafo, adicionando-a a todas as listas relevantes.
  empilha(e, arestas(G));
  empilha(e, fronteira(u));
  empilha(e, fronteira(v));

  e->peso = grau(u) + grau(v);

  // atualiza matriz
  MatInfo *m = procura_matinfo(G);
  if (m) 
  {
    garante_indice_para_id(m, u_id);
    garante_indice_para_id(m, v_id);
    matriz_set_peso(m, u_id, v_id, e->peso);
  }
}


//=================================================================================


//  Remove aresta com id do grafo G e a destroi
void remove_aresta(int id, grafo G)
{
  // usa remove_chave para encontrar a aresta pelo id e já remove da lista de arestas. */
  aresta e = (aresta) remove_chave(id, arestas(G), get_aresta_id);

  if (!e)
    return;

  // pega os ponteiros para os vértices que a aresta conectava.
  vertice u = vertice_u(e);
  vertice v = vertice_v(e);

  // remove a mesma aresta das listas de fronteira de u e v.
  remove_chave(id, fronteira(u), get_aresta_id);
  remove_chave(id, fronteira(v), get_aresta_id);

  // atualiza matriz
  MatInfo *m = procura_matinfo(G);
  if (m) 
  {
    int uid = vertice_id(u);
    int vid = vertice_id(v);
    matriz_set_peso(m, uid, vid, 0);
  }

  free(e);

  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
}


//=================================================================================


//  Calcula e devolve o grau do vertice v
int grau(vertice v)
{
  int d_v = 0;

  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;

  return d_v;
}


//=================================================================================


//  Funções para impressão do Grafo
void imprime_grafo(grafo G)
{
  printf("\nVertices: <id> - [grau] - <fronteira> \n");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id> - {u,v} / [ PESO = X ]\n");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
}


void imprime_vertice(vertice v)
{
  printf(" VÉRTICE_ID: %d - GRAU: [%d] -", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
}


void imprime_aresta(aresta e)
{
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));

  printf(" ARESTA_ID: %d - {%d,%d} / [ PESO = %d ] ", aresta_id(e), u_id, v_id, e->peso);
}


//=================================================================================