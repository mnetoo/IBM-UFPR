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
#include <string.h>




/* ---------------------------------------------------------------------
   Estrutura interna para mapear cada 'grafo' (ponteiro) para sua matriz
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


// procura MatInfo pelo grafo G 
static MatInfo *procura_matinfo(grafo G) 
{
  for (MatInfo *m = cabeca_matriz; m; m = m->prox)
    if (m->G == G) return m;
  return NULL;
}


//=================================================================================


// cria e adiciona MatInfo para um grafo recém-criado
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
      exit(_ERRO_MALLOC_);
    
      for (int j = 0; j < m->capacidade; ++j) 
      m->matriz[i][j] = 0;
  }

  m->prox = cabeca_matriz;
  cabeca_matriz = m;
  return m;
}


//=================================================================================


// libera MatInfo associado a G
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


// encontra índice livre ou existente para dado id; retorna -1 se não achar
static int indice_de_id(MatInfo *m, int id) 
{
  for (int i = 0; i < m->capacidade; ++i)
    if (m->mapa_indice_para_id[i] == id) 
      return i;
  return -1;
}


//=================================================================================


// encontra uma vaga livre; se não houver, retorna -1
static int procura_indice_livre(MatInfo *m) 
{
  for (int i = 0; i < m->capacidade; ++i)
    if (m->mapa_indice_para_id[i] == -1) 
      return i;
  return -1;
}


//=================================================================================


/* expande a capacidade da MatInfo (dobrando) */
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

  /* inicializa novo com zeros */
  for (int i = 0; i < nova_cap; ++i)
    for (int j = 0; j < nova_cap; ++j)
      nova_matriz[i][j] = 0;

  /* copia a matriz antiga */
  for (int i = 0; i < m->capacidade; ++i)
    for (int j = 0; j < m->capacidade; ++j)
      nova_matriz[i][j] = m->matriz[i][j];

  /* libera a antiga */
  for (int i = 0; i < m->capacidade; ++i)
    free(m->matriz[i]);
  free(m->matriz);

  /* expande mapa */
  m->mapa_indice_para_id = (int *) realloc(m->mapa_indice_para_id, sizeof(int) * nova_cap);
  
  if (!m->mapa_indice_para_id) 
    exit(_ERRO_MALLOC_);
  
    for (int i = m->capacidade; i < nova_cap; ++i) 
    m->mapa_indice_para_id[i] = -1;

  m->matriz = nova_matriz;
  m->capacidade = nova_cap;
}


//=================================================================================


/* garante que exista um índice para o id, criando novo se necessário */
static int garante_indice_para_id(MatInfo *m, int id) 
{
  int idx = indice_de_id(m, id);

  if (idx != -1) return idx;

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


/* remove id da tabela (marca vaga livre) e zera linhas/colunas */
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


/* retorna 1 se existe aresta entre ids (peso != 0), 0 caso contrário */
static int matriz_existe_aresta(MatInfo *m, int u_id, int v_id) 
{
  int iu = indice_de_id(m, u_id);
  int iv = indice_de_id(m, v_id);

  if (iu == -1 || iv == -1) 
    return 0;

  return m->matriz[iu][iv] != 0;
}


//=================================================================================


/* seta peso na matriz (0 remove) */
static void matriz_set_peso(MatInfo *m, int u_id, int v_id, int peso) 
{
  int iu = indice_de_id(m, u_id);
  int iv = indice_de_id(m, v_id);

  if (iu == -1 || iv == -1) 
    return;
  
    m->matriz[iu][iv] = peso;
  m->matriz[iv][iu] = peso;
}


//=================================================================================


/* getters simples */
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


/*
 * Verifica se um 'id' pertence a um conjunto de inteiros 'X'.
 * Retorna 1 se pertence, 0 caso contrário.
 */
int pertence_ao_conjunto(int id, int *X, int n_X)
{
  for (int i = 0; i < n_X; i++)
    if (X[i] == id)
      return 1;

  return 0;
}


//=================================================================================


/*
 * Transforma o grafo G no seu subgrafo induzido G[X].
 * Remove todos os vértices de G que não estão no conjunto X.
 */
void induzir_subgrafo(grafo G, int *X, int n_X)
{
  no n_vert = primeiro_no(vertices(G));

  // Itera pela lista de vértices de forma segura para remoção
  while (n_vert)
  {
    // 1. Salva o ponteiro para o próximo nó ANTES de qualquer modificação
    no proximo_n = proximo(n_vert);

    vertice v = (vertice) conteudo(n_vert);
    int v_id = vertice_id(v);

    // 2. Verifica se o vértice atual deve ser removido
    if (!pertence_ao_conjunto(v_id, X, n_X)) {
      // Se não pertence a X, remove do grafo
      printf("-> Removendo vértice %d (não pertence a X).\n", v_id);
      remove_vertice(v_id, G);
    }

    // 3. Avança para o próximo nó (que foi salvo anteriormente)
    n_vert = proximo_n;
  }
}


//=================================================================================


// atualiza pesos dos incidentes de um vertice  
static void atualiza_pesos_incidentes(vertice v)
{
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
  {
    aresta e = (aresta) conteudo(n);

    /* A regra: peso = grau(u) + grau(v) */
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

  /* Após recalcular pesos nas arestas (nas estruturas aresta), atualiza matriz */
  MatInfo *m = find_matinfo(G);

  if (!m) 
    return;

  for (no na = primeiro_no(arestas(G)); na; na = proximo(na)) 
  {
    aresta e = (aresta) conteudo(na);
    int uid = vertice_id(vertice_u(e));
    int vid = vertice_id(vertice_v(e));
    mat_set_peso(m, uid, vid, e->peso);
  }
}


//=================================================================================


/* cria grafo vazio e o retorna */
grafo cria_grafo()
{
  grafo G = (grafo) malloc(sizeof(t_grafo));

  if (!G) 
    exit(_ERRO_MALLOC_);

  G->vertices = cria_lista();
  G->arestas = cria_lista();

  /* cria MatInfo (matriz) associada ao grafo */
  create_matinfo(G, 4);

  return G;
}


//=================================================================================


/* destroi grafo G (desaloca toda a memoria) */
void destroi_grafo(grafo G)
{
  MatInfo *m = find_matinfo(G);

  /* 1. Percorre a lista de arestas, removendo uma a uma e liberando a memória. */
  while (!vazio(arestas(G)))
  {
    aresta e = (aresta) desempilha(arestas(G));
    free(e);
  }

  /* 2. Percorre a lista de vertices, fazendo o mesmo. */
  while (!vazio(vertices(G)))
  {
    vertice v = (vertice) desempilha(vertices(G));
    free(fronteira(v));
    free(v);
  }

  /* 3. Libera as estruturas das listas principais */
  free(arestas(G));
  free(vertices(G));

  /* 4. Libera MatInfo (matriz) associada */
  if (m) 
    destroy_matinfo(G);

  /* 5. Libera a estrutura do grafo */
  free(G);
}


//=================================================================================


/* cria novo vertice com id <id> e adiciona ao grafo G */
void adiciona_vertice(int id, grafo G)
{
  /* evita duplicatas: se já existe, não adiciona */
  vertice existente = (vertice) busca_chave(id, vertices(G), get_vertice_id);
  if (existente) 
    return;

  /* 1. Aloca memória para a estrutura do novo vértice. */
  vertice v = (vertice) malloc(sizeof(t_vertice));
  if (!v) 
    exit(_ERRO_MALLOC_);

  /* 2. Inicializa os campos da estrutura do vértice. */
  v->id = id;
  v->fronteira = cria_lista();

  /* 3. Adiciona (empilha) o novo vértice na lista de vértices do grafo. */
  empilha(v, vertices(G));

  /* 4. Cria índice na matriz */
  MatInfo *m = find_matinfo(G);

  if (m)
    ensure_index_for_id(m, id);
}


//=================================================================================


/* remove vertice com id <id> do grafo G e o destroi
   [deve remover e destruir tambem as arestas incidentes] */
void remove_vertice(int id, grafo G)
{
  /* 1. Busca o vértice com o 'id' fornecido na lista de vértices do grafo. */
  vertice v = (vertice) busca_chave(id, vertices(G), get_vertice_id);

  /* Se a busca não encontrar o vértice (retornar NULL), não há nada a fazer. */
  if (!v)
    return;

  MatInfo *m = find_matinfo(G);

  /* 2. Itera sobre todas as arestas na fronteira do vértice 'v', destruindo-as. */
  while (!vazio(fronteira(v)))
  {
    aresta e = (aresta) desempilha(fronteira(v));

    /* encontra o outro vértice conectado pela aresta 'e' */
    vertice outro_v = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);

    /* Remove a aresta 'e' da fronteira do outro vértice e da lista principal */
    remove_chave(aresta_id(e), fronteira(outro_v), get_aresta_id);
    remove_chave(aresta_id(e), arestas(G), get_aresta_id);

    /* atualiza matriz: zera entrada */
    if (m) 
    {
      int u_id = vertice_id(vertice_u(e));
      int v_id = vertice_id(vertice_v(e));
      mat_set_peso(m, u_id, v_id, 0);
    }

    /* libera a memória da aresta */
    free(e);
  }

  /* 3. Remove o vértice 'v' da lista de vértices do grafo. */
  remove_chave(id, vertices(G), get_vertice_id);

  /* 4. Libera a memória alocada para a lista de fronteira do vértice 'v'. */
  free(fronteira(v));

  /* 5. Libera a memória da estrutura do próprio vértice. */
  free(v);

  /* 6. Remove índice da matriz */
  if (m) 
    remove_index_for_id(m, id);
}


//=================================================================================


/* cria aresta com id <id> incidente a vertices com ids <u_id> e <v_id> e adiciona ao grafo G */
void adiciona_aresta(int id, int u_id, int v_id, grafo G)
{
  /* 1. Busca pelos ponteiros dos vértices u e v usando seus IDs. */
  vertice u = (vertice) busca_chave(u_id, vertices(G), get_vertice_id);
  vertice v = (vertice) busca_chave(v_id, vertices(G), get_vertice_id);

  /* Se um dos vértices (ou ambos) não for encontrado, a aresta não pode ser criada. */
  if (!u || !v)
    return;

  /* Evita duplicatas de aresta pelo mesmo id (se já existir) */
  aresta ja = (aresta) busca_chave(id, arestas(G), get_aresta_id);
  if (ja) 
    return;

  /* 2. Aloca memória para a nova aresta. */
  aresta e = (aresta) malloc(sizeof(t_aresta));
  if (!e) 
    exit(_ERRO_MALLOC_);

  /* 3. Preenche os atributos da nova aresta. */
  e->id = id;
  e->u = u;
  e->v = v;

  /* 4. "Conecta" a aresta ao grafo, adicionando-a a todas as listas relevantes. */
  empilha(e, arestas(G));
  empilha(e, fronteira(u));
  empilha(e, fronteira(v));

  /* calcula peso baseado nos graus dos vértices >>>
     importante: grau() conta o tamanho das listas de fronteira, então
     fazemos isso após inserir a aresta nas listas (como código original) */
  e->peso = grau(u) + grau(v);

  /* atualiza matriz */
  MatInfo *m = find_matinfo(G);
  if (m) 
  {
    ensure_index_for_id(m, u_id);
    ensure_index_for_id(m, v_id);
    mat_set_peso(m, u_id, v_id, e->peso);
  }
}


//=================================================================================


/* remove aresta com id <id> do grafo G e a destroi */
void remove_aresta(int id, grafo G)
{
  /* 1. Usa remove_chave para encontrar a aresta pelo 'id' e já removê-la da lista G->arestas. */
  aresta e = (aresta) remove_chave(id, arestas(G), get_aresta_id);

  /* 2. Se 'e' for NULL, a aresta não foi encontrada. Fim da função. */
  if (!e)
    return;

  /* 3. Pega os ponteiros para os vértices que a aresta conectava. */
  vertice u = vertice_u(e);
  vertice v = vertice_v(e);

  /* 4. Remove a mesma aresta das listas de fronteira de u e v. */
  remove_chave(id, fronteira(u), get_aresta_id);
  remove_chave(id, fronteira(v), get_aresta_id);

  /* 5. Atualiza matriz (zera entrada) */
  MatInfo *m = find_matinfo(G);
  if (m) 
  {
    int uid = vertice_id(u);
    int vid = vertice_id(v);
    mat_set_peso(m, uid, vid, 0);
  }

  /* 6. Libera a memória da estrutura da aresta. */
  free(e);

  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
}


//=================================================================================


/* calcula e devolve o grau do vertice v */
int grau(vertice v)
{
  int d_v = 0;

  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;

  return d_v;
}


//=================================================================================


/* imprime o grafo G */
void imprime_grafo(grafo G)
{
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}


//=================================================================================


/* imprime o vertice v */
void imprime_vertice(vertice v)
{
  printf("ID: %d - GRAU: [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}


//=================================================================================


void imprime_aresta(aresta e)
{
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));

  printf("%d:{%d,%d}[PESO = %d]", aresta_id(e), u_id, v_id, e->peso);
}


//=================================================================================