/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>


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


static void atualiza_pesos_incidentes(vertice v) 
{
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n)) 
  {
    aresta e = (aresta) conteudo(n);

    // A regra: peso = grau(u) + grau(v)
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
}




//=================================================================================


// cria grafo vazio e o retorna
grafo cria_grafo() 
{
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}


//=================================================================================


// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) 
{
  // 1. Percorre a lista de arestas, removendo uma a uma e liberando a memória.
  while (!vazio(arestas(G))) 
  {
      // desempilha retorna um obj (void *), então fazemos o cast para aresta.
      aresta e = (aresta) desempilha(arestas(G));
      // Agora que temos o ponteiro para a aresta, liberamos a memória dela.
      free(e);
  }


  // 2. Percorre a lista de vertices, fazendo o mesmo.
  while (!vazio(vertices(G))) 
  {
      // Pega o primeiro vértice da lista, removendo-o.
      vertice v = (vertice) desempilha(vertices(G));

      // IMPORTANTE: Antes de liberar o vértice 'v', liberamos a lista 'fronteira' dele.
      // A função 'cria_lista' foi chamada para criar esta fronteira,
      // então precisamos liberar a estrutura da lista.
      free(fronteira(v));
      
      // Agora sim, liberamos a memória da estrutura do vértice.
      free(v);
  }

  // Passo 3: Libera as estruturas das listas principais
  free(arestas(G));
  free(vertices(G));

  // Passo 4: Libera a estrutura do grafo
  free(G);
}


//=================================================================================


// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) 
{
  // 1. Aloca memória para a estrutura do novo vértice.
  vertice v = (vertice) malloc(sizeof(t_vertice));

  // Verifica se a alocação de memória foi bem sucedida.
  if (!v)
    exit(_ERRO_MALLOC_); // Encerra o programa se malloc falhar.

  
  // 2. Inicializa os campos da estrutura do vértice.
  v->id = id;
  v->fronteira = cria_lista(); // Um novo vértice começa com uma lista de fronteira vazia.


  // 3. Adiciona (empilha) o novo vértice na lista de vértices do grafo.
  // Usamos o getter 'vertices(G)' para acessar a lista.
  empilha(v, vertices(G));
}


//=================================================================================


// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) 
{
  // 1. Busca o vértice com o 'id' fornecido na lista de vértices do grafo.
  vertice v = (vertice) busca_chave(id, vertices(G), get_vertice_id);

  // Se a busca não encontrar o vértice (retornar NULL), não há nada a fazer.
  if (!v)
    return;


  // 2. Itera sobre todas as arestas na fronteira do vértice 'v', destruindo-as.
  while (!vazio(fronteira(v))) 
  {
    // Pega e remove a primeira aresta da fronteira de 'v'.
    aresta e = (aresta) desempilha(fronteira(v));
    
    // a) Encontra o outro vértice conectado pela aresta 'e'.
    // Usamos um operador ternário: se u for 'v', pegue v, senão pegue u.
    vertice outro_v = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);

    // b) Remove a aresta 'e' da fronteira do outro vértice.
    // A função remove_chave retorna o obj removido, mas aqui não precisamos guardar.
    remove_chave(aresta_id(e), fronteira(outro_v), get_aresta_id);

    // c) Remove a aresta 'e' da lista principal de arestas do grafo.
    remove_chave(aresta_id(e), arestas(G), get_aresta_id);

    // d) Libera a memória da estrutura da aresta.
    free(e);
  }


  // 3. Remove o vértice 'v' da lista de vértices do grafo.
  remove_chave(id, vertices(G), get_vertice_id);

  // 4. Libera a memória alocada para a lista de fronteira do vértice 'v'.
  free(fronteira(v));

  // 5. Libera a memória da estrutura do próprio vértice.
  free(v);

}


//=================================================================================


// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) 
{
  // 1. Busca pelos ponteiros dos vértices u e v usando seus IDs.
  vertice u = (vertice) busca_chave(u_id, vertices(G), get_vertice_id);
  vertice v = (vertice) busca_chave(v_id, vertices(G), get_vertice_id);

  // Se um dos vértices (ou ambos) não for encontrado, a aresta não pode
  // ser criada. A função simplesmente retorna sem fazer nada.
  if (!u || !v)
    return;


  // 2. Aloca memória para a nova aresta.
  aresta e = (aresta) malloc(sizeof(t_aresta));
  if (!e)
    exit(_ERRO_MALLOC_); // Encerra se a alocação falhar.

  // 3. Preenche os atributos da nova aresta.
  e->id = id;
  e->u = u; // 'u' é o ponteiro para o primeiro vértice encontrado.
  e->v = v; // 'v' é o ponteiro para o segundo vértice encontrado.


  // 4. "Conecta" a aresta ao grafo, adicionando-a a todas as listas relevantes.
  empilha(e, arestas(G));       // Adiciona na lista principal de arestas.
  empilha(e, fronteira(u));   // Adiciona na fronteira do vértice u.
  empilha(e, fronteira(v));   // Adiciona na fronteira do vértice v.

  // calcula peso baseado nos graus dos vértices >>>
  e->peso = grau(u) + grau(v);
}


//=================================================================================


// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) 
{
  // 1. Usa remove_chave para encontrar a aresta pelo 'id' e já removê-la da lista G->arestas.
  aresta e = (aresta) remove_chave(id, arestas(G), get_aresta_id);

  // 2. Se 'e' for NULL, a aresta não foi encontrada. Fim da função.
  if (!e)
    return;


  // 3. Pega os ponteiros para os vértices que a aresta conectava.
  vertice u = vertice_u(e);
  vertice v = vertice_v(e);

  // 4. Remove a mesma aresta das listas de fronteira de u e v.
  // Não precisamos guardar o valor de retorno aqui, pois já temos 'e'.
  remove_chave(id, fronteira(u), get_aresta_id);
  remove_chave(id, fronteira(v), get_aresta_id);


  // 5. Libera a memória da estrutura da aresta.
  free(e);

  atualiza_pesos_incidentes(u);
  atualiza_pesos_incidentes(v);
}


//=================================================================================
// funcoes para operacoes com o grafo pronto:


// calcula e devolve o grau do vertice v
int grau(vertice v) 
{
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}


//=================================================================================


// imprime o grafo G
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


// imprime o vertice v
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