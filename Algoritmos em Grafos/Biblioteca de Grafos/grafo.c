/*******************************************
 * Implementação de biblioteca para grafos.
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>



//---------------------------------------------------------
// getters:

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





//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:



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

}




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
}



//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:




// calcula e devolve o grau do vertice v
int grau(vertice v) 
{
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}




// imprime o grafo G
void imprime_grafo(grafo G) 
{
  no n;

  printf("\n--- IMPRESSÃO DO GRAFO ---\n");

  // Seção de Vértices
  printf("VÉRTICES:\n");
  if (vazio(vertices(G))) {
    printf("  (O grafo não possui vértices)\n");
  } else {
    // Itera pela lista de vértices e chama a nova imprime_vertice para cada um
    for (n = primeiro_no(vertices(G)); n; n = proximo(n)) {
      imprime_vertice((vertice) conteudo(n));
    }
  }

  // Seção de Arestas
  printf("\nARESTAS:\n");
  if (vazio(arestas(G))) {
    printf("  (O grafo não possui arestas)\n");
  } else {
    // Itera pela lista de arestas e chama a nova imprime_aresta para cada uma
    for (n = primeiro_no(arestas(G)); n; n = proximo(n)) {
      imprime_aresta((aresta) conteudo(n));
    }
  }
  
  printf("--- FIM DO GRAFO ---\n\n");
}




// imprime o vertice v
void imprime_vertice(vertice v) 
{
  // Imprime a informação base: "  Vértice 1 [grau 2]:"
  printf("  Vértice %d [grau %d]:", vertice_id(v), grau(v));
  
  no n = primeiro_no(fronteira(v));
  
  // Se o vértice não tem vizinhos, informa que ele está isolado.
  if (!n) {
    printf(" (isolado)\n");
    return;
  }
  
  printf(" vizinhos -> ");
  
  // Itera por todas as arestas na fronteira do vértice v
  while (n) {
    aresta e = (aresta) conteudo(n);
    
    // Descobre quem é o vizinho na outra ponta da aresta
    vertice vizinho = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);
    
    // Imprime o vizinho e a aresta que os conecta: "2 (aresta 101)"
    printf("%d (aresta %d)", vertice_id(vizinho), aresta_id(e));
    
    // Adiciona uma vírgula se houver um próximo vizinho a ser listado
    if (proximo(n)) {
      printf(", ");
    }
    
    n = proximo(n);
  }
  
  printf("\n"); // Quebra de linha no final
}




// imprime a aresta e
void imprime_aresta(aresta e) 
{
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  
  // Formato: "  Aresta 101: {1, 2}"
  printf("  Aresta %d: {%d, %d}\n", aresta_id(e), u_id, v_id);
}





// --- FUNÇÕES AUXILIARES ---

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





/**
 * @brief Monta e retorna um novo grafo que é o subgrafo de G induzido
 *        pelos vértices cujos IDs estão no conjunto X.
 * 
 * @param G O grafo original.
 * @param X Um array de inteiros com os IDs dos vértices que formarão o subgrafo.
 * @param n_X O número de elementos no array X.
 * @return Um novo grafo (subgrafo induzido).
 */
grafo subgrafo_induzido_por_vertices(grafo G, int *X, int n_X) {
  // 1. Cria um novo grafo vazio que será o nosso subgrafo.
  grafo H = cria_grafo();

  // 2. Adiciona todos os vértices do conjunto X ao novo grafo H.
  for (int i = 0; i < n_X; i++) {
    int id_vertice = X[i];
    // Verifica se o vértice realmente existe no grafo original antes de adicioná-lo.
    if (busca_chave(id_vertice, vertices(G), get_vertice_id)) {
      adiciona_vertice(id_vertice, H);
    }
  }

  // 3. Itera sobre todas as arestas do grafo original G.
  for (no n = primeiro_no(arestas(G)); n; n = proximo(n)) {
    aresta e = (aresta) conteudo(n);
    int u_id = vertice_id(vertice_u(e));
    int v_id = vertice_id(vertice_v(e));

    // 4. Verifica se AMBOS os vértices da aresta 'e' pertencem ao conjunto X.
    if (pertence_ao_conjunto(u_id, X, n_X) && pertence_ao_conjunto(v_id, X, n_X)) {
      // Se ambos pertencem, a aresta faz parte do subgrafo induzido.
      // Adiciona a aresta ao novo grafo H.
      adiciona_aresta(aresta_id(e), u_id, v_id, H);
    }
  }

  return H;
}





/**
 * @brief Monta e retorna um novo grafo que é o subgrafo de G induzido
 *        pelas arestas cujos IDs estão no conjunto E_X.
 *
 * @param G O grafo original.
 * @param E_X Um array de inteiros com os IDs das arestas que formarão o subgrafo.
 * @param n_E_X O número de elementos no array E_X.
 * @return Um novo grafo (subgrafo induzido).
 */
grafo subgrafo_induzido_por_arestas(grafo G, int *E_X, int n_E_X) {
  // 1. Cria um novo grafo vazio.
  grafo H = cria_grafo();
  
  // Lista para rastrear os IDs dos vértices que já foram adicionados a H.
  // Isso evita tentar adicionar o mesmo vértice múltiplas vezes.
  lista vertices_adicionados_ids = cria_lista();

  // 2. Itera sobre o conjunto de IDs de arestas fornecido.
  for (int i = 0; i < n_E_X; i++) {
    int id_aresta = E_X[i];
    
    // Busca a aresta correspondente no grafo original G.
    aresta e = (aresta) busca_chave(id_aresta, arestas(G), get_aresta_id);

    // Se a aresta existir...
    if (e) {
      vertice u = vertice_u(e);
      vertice v = vertice_v(e);
      int u_id = vertice_id(u);
      int v_id = vertice_id(v);

      // 3. Adiciona os vértices da aresta ao novo grafo H, se ainda não estiverem lá.
      
      // Verifica se o vértice 'u' já foi adicionado.
      if (!busca_chave(u_id, vertices(H), get_vertice_id)) {
        adiciona_vertice(u_id, H);
      }
      
      // Verifica se o vértice 'v' já foi adicionado.
      if (!busca_chave(v_id, vertices(H), get_vertice_id)) {
        adiciona_vertice(v_id, H);
      }

      // 4. Adiciona a aresta ao novo grafo H.
      adiciona_aresta(id_aresta, u_id, v_id, H);
    }
  }
  
  // Libera a lista auxiliar usada para rastreamento (a lista em si, não seu conteúdo).
  free(vertices_adicionados_ids);

  return H;
}




/**
 * @brief Encontra um conjunto independente maximal de vértices em G.
 *        Um conjunto independente é um subconjunto de vértices em um grafo
 *        em que não há dois vértices adjacentes. Um conjunto independente
 *        maximal não pode ser estendido adicionando qualquer outro vértice.
 *
 *        Esta função usa um algoritmo guloso:
 *        1. Inicializa um conjunto de candidatos C com todos os vértices de G.
 *        2. Enquanto C não estiver vazio:
 *           a. Escolhe um vértice 'v' de C (aqui, o primeiro que encontrar).
 *           b. Adiciona 'v' ao conjunto independente S.
 *           c. Remove 'v' e todos os seus vizinhos de C.
 *        3. Retorna S.
 *
 * @param G O grafo.
 * @return Uma lista contendo os IDs dos vértices no conjunto independente.
 */
lista conjunto_independente_maximal(grafo G) {
  lista S = cria_lista(); // O conjunto independente a ser retornado (de IDs).
  lista C = cria_lista(); // O conjunto de vértices candidatos.

  // 1. Preenche a lista de candidatos C com todos os vértices de G.
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    empilha(conteudo(n), C);
  }

  // 2. Itera enquanto houver candidatos.
  while (!vazio(C)) {
    // a. Pega um vértice 'v' do conjunto de candidatos (aqui, o primeiro da lista).
    vertice v = (vertice) topo(C);
    int v_id = vertice_id(v);

    // b. Adiciona o ID de 'v' ao nosso conjunto independente S.
    // Usamos um truque: como a lista genérica armazena void*, podemos alocar
    // um int* para guardar o ID e empilhá-lo.
    int *id_ptr = (int*) malloc(sizeof(int));
    *id_ptr = v_id;
    empilha(id_ptr, S);

    // c. Remove 'v' e seus vizinhos do conjunto de candidatos C.
    
    // Primeiro, remove o próprio 'v'.
    remove_chave(v_id, C, get_vertice_id);
    
    // Agora, itera sobre a fronteira de 'v' para encontrar seus vizinhos.
    for (no n_aresta = primeiro_no(fronteira(v)); n_aresta; n_aresta = proximo(n_aresta)) {
      aresta e = (aresta) conteudo(n_aresta);
      
      // Identifica quem é o vizinho.
      vertice vizinho = (vertice_u(e) == v) ? vertice_v(e) : vertice_u(e);
      int vizinho_id = vertice_id(vizinho);
      
      // Remove o vizinho do conjunto de candidatos C, se ele estiver lá.
      remove_chave(vizinho_id, C, get_vertice_id);
    }
  }

  // Libera a lista de candidatos (apenas a estrutura, não seu conteúdo, pois
  // os vértices pertencem ao grafo original G).
  free(C);
  
  return S;
}