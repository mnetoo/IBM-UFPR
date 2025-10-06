# Algoritmos em Grafos e Otimização - Trabalho 2


**Autor:** Marcus Sebastião Adriano Rocha Neto
**GRR:** 20240710
**Código Utilizado:** Trabalho 1 - v1 (Lista de Adjacência)



### Estrutura do Projeto
 - **lista.h / lista.c:** TAD de lista para uso de lista de adjacência.
 - **grafo.h / grafo.c:** TAD de grafos, utilizando o TAD de lista para as listas de adjacência.
 - **main.c:** Arquivo principal que contém a lógica para ler o arquivo da rede, construir o grafo e realizar a análise.


### Alterações no TAD (v1)
Para atender aos requisitos do trabalho, realizei modificações no TAD de Grafo.
 - **Grafo:** Grafo direcionado. Criei a função **"cria_direcao"** para cumprir com o requisito do trabalho que exigia grafo  direcionado em "M -> R" e "R -> M". A função cria uma aresta e a insere apenas na lista de fronteira do vértice de origem (u).


### Main
Na main ocorre todo o processo, que pode ser dividido em três etapas principais:

**1. Mapeamento de Nomes e Construção do Grafo:** Como arquivo de entrada usa strings para reações e metabólitos e o TAD de Grafo opera com IDs que são inteiros, criei uma estrutura para associar cada nome com o ID do vértice **"mapa_vertices"**. Criei a função **"obtem_ou_cria_id_vertice"** que faz essa busca, ao encontrar um novo nome (não existe), cria um novo vértice no grafo e guarda a nome-ID; se o nome já existe, ela apenas retorna o ID do vértice.

O arquivo de entrada é lido linha por linha. A função strtok_r é usada para quebrar a linha em **"tokens"**. Para cada linha o primeiro token é a Reação.
- Tokens entre a Reação e a seta são Substratos. Um arco do Metabólito para a Reação (M -> R) é criado para cada um.
- Tokens após a seta são Produtos. Um arco da Reação para o Metabólito (R -> M) é criado para cada um.


**2. Detecção de Ciclos com Busca em Profundidade (DFS):** A análise da rede é feita com o algoritmo de Busca em Profundidade **(DFS)**. Para detectar ciclos, utilizei estados dos vértices, para cada vértice:

 - **ABERTO:** O vértice ainda não foi visitado.
 - **PROCESSANDO:** O vértice está atualmente na pilha de recursão da DFS (busca no seus vizinhos).
 - **FECHADO:** Já visitamos este vértices e seus vizinhos.

Detecção: Um ciclo é detectado se, estando em um vértice **"u"** que seu estado atual é **"PROCESSANDO"**, a DFS encontra um vizinho **"v"** que também está **"PROCESSANDO"**, isso caracteriza uma um ciclo.


**3. Ordenação Topológica**

Se a busca em profundida terminar de percorrer todo o grafo sem encontrar nenhum ciclo, uma ordenação topológica é possível. A ordenação topológica é obtida a partir da ordem inversa da finalização dos vértices na busca. A função de busca em profundidade, assim que termina de explorar o vértice e seus vizinhos, empilha este vértice em uma lista **"resultado_ordenado"**. Para obter a ordenação topológica, basta imprimir a lista do início ao fim, pois dessa forma representa uma ordenação topológica válida, então itera sobre essa lista, imprimindo apenas os nomes dos vértices que são do tipo **"METABOLITO"**.