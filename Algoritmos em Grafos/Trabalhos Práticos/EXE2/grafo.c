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