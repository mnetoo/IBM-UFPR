import networkx as nx
from networkx.algorithms.components.connected import connected_components
from networkx.algorithms import community
import matplotlib.pyplot as plt
from collections import Counter
import numpy as np


#=============================================================================================


def informacoes_basicas(G):
    """
    Exibe informações básicas do grafo G.
    """

    n_nos = G.number_of_nodes()
    n_arestas = G.number_of_edges()
    
    print(f"\nInformações Básicas do Grafo:\n")
    print(f"  - Número de vértices (nós): {n_nos}")
    print(f"  - Número de arestas: {n_arestas}\n")
    print("-" * 100)


#=============================================================================================


def analisar_ciclos(G):
    """
    Encontra e retorna uma base de ciclos do grafo G.
    """

    try:
        # A função cycle_basis funciona para grafos não-direcionados.
        ciclos = nx.cycle_basis(G)
        print(f"\nAnálise de Ciclos: Uma base com {len(ciclos)} ciclos foi encontrada.\n")
        print("-" * 100)
        return ciclos

    except Exception as e:
        print(f"\nOcorreu um erro ao analisar os ciclos: {e}\n")
        return []


#=============================================================================================


def analisar_componentes_conexas(G):
    """
    Verifica se o grafo é conexo e, se não for, retorna seus componentes.
    Diferencia a análise para grafos direcionados e não-direcionados.
    """

    print("\nAnálise de Componentes Conexas:\n")

    # Para grafos não-direcionados
    if nx.is_connected(G):
        print("O grafo não-direcionado é conexo.\n")
        print("-" * 100)
    else:
        print("O grafo não-direcionado não é conexo.")
        n_comp = nx.number_connected_components(G)
        componentes = list(nx.connected_components(G))
        tamanhos = [len(c) for c in componentes]
        print(f"Ele possui {n_comp} componentes conexos.")
        print(f"Tamanho do maior componente: {max(tamanhos)} vértices.\n")
        print("-" * 100)


#=============================================================================================


def analisar_raio_diametro(G):
    """
    Calcula o raio e o diâmetro do grafo.
    Essas métricas só se aplicam a grafos (ou componentes) conexos.
    O raio é a menor excentricidade, e o diâmetro é a maior.
    A excentricidade de um nó é a maior distância dele para todos os outros nós.
    """

    print("\nAnálise de Raio e Diâmetro:\n")
    # Essas métricas exigem que o grafo seja conexo.
    # Se não for, a análise pode ser feita no maior componente.
    if not nx.is_connected(G):
        print("O grafo não é conexo. As métricas serão calculadas para o maior componente conectado.")
        # Encontra o maior componente conectado
        componentes = sorted(connected_components(G), key=len, reverse=True)
        maior_componente = G.subgraph(componentes[0])
        try:
            raio = nx.radius(maior_componente)
            diametro = nx.diameter(maior_componente)
            print(f"  - Raio do maior componente: {raio}")
            print(f"  - Diâmetro do maior componente: {diametro}\n")
            print("-" * 100)
            return {"raio": raio, "diâmetro": diametro}
        except Exception as e:
            print(f"\nNão foi possível calcular o raio e o diâmetro: {e}\n")
            print("-" * 100)
            return None
    else:
        # Se o grafo for conexo, calcula diretamente
        try:
            raio = nx.radius(G)
            diametro = nx.diameter(G)
            print(f"  - Raio do grafo: {raio}")
            print(f"  - Diâmetro do grafo: {diametro}\n")
            print("-" * 100)
            return {"raio": raio, "diâmetro": diametro}
        except Exception as e:
            print(f"Não foi possível calcular o raio e o diâmetro: {e}\n")
            print("-" * 100)
            return None
        

#=============================================================================================


def analisar_distribuicao_graus(G):
    """
    Calcula, analisa e plota a distribuição de graus do grafo.
    Diferencia a análise para grafos direcionados (graus de entrada e saída)
    e não-direcionados.
    """

    print("\nAnálise de Distribuição de Graus:")

    if G.is_directed():
        # Para grafos direcionados, analisamos 3 tipos de grau
        in_degrees = [d for n, d in G.in_degree()]
        out_degrees = [d for n, d in G.out_degree()]
        
        # Análise do Grau de Entrada (In-Degree)
        if in_degrees:
            print("\n--- Graus de Entrada (In-Degree) ---")
            print(f"  - Grau de Entrada Médio: {np.mean(in_degrees):.2f}")
            print(f"  - Grau de Entrada Máximo: {np.max(in_degrees)}")
            print(f"  - Grau de Entrada Mínimo: {np.min(in_degrees)}")
            plotar_histograma_graus(in_degrees, 'Distribuição de Graus de Entrada (In-Degree)', 'distribuicao_graus_entrada.png')

        # Análise do Grau de Saída (Out-Degree)
        if out_degrees:
            print("\n--- Graus de Saída (Out-Degree) ---")
            print(f"  - Grau de Saída Médio: {np.mean(out_degrees):.2f}")
            print(f"  - Grau de Saída Máximo: {np.max(out_degrees)}")
            print(f"  - Grau de Saída Mínimo: {np.min(out_degrees)}")
            plotar_histograma_graus(out_degrees, 'Distribuição de Graus de Saída (Out-Degree)', 'distribuicao_graus_saida.png')
    
    else:
        # Para grafos não-direcionados, temos apenas um tipo de grau
        degrees = [d for n, d in G.degree()]
        
        if degrees:
            print("\n--- Graus (Grafo Não-Direcionado) ---")
            print(f"  - Grau Médio: {np.mean(degrees):.2f}")
            print(f"  - Grau Máximo: {np.max(degrees)}")
            print(f"  - Grau Mínimo: {np.min(degrees)}")
            plotar_histograma_graus(degrees, 'Distribuição de Graus', 'distribuicao_graus.png')




def plotar_histograma_graus(graus_lista, titulo, nome_arquivo):
    """
    Função auxiliar que gera e salva um histograma da distribuição de graus
    com escala linear no eixo X e logarítmica no eixo Y (Linear-Log).
    
    Este tipo de gráfico é ideal para identificar distribuições exponenciais,
    características de redes aleatórias (modelo Erdös-Rényi).
    """

    if not graus_lista:
        print("Lista de graus está vazia. Gráfico não gerado.")
        return

    contagem = Counter(graus_lista)
    # Separa os graus (x) e suas frequências (y)
    graus, frequencias = zip(*sorted(contagem.items()))
    
    # --- Gráfico Linear-Log (Semi-log Y) ---
    plt.figure(figsize=(12, 7))
    
    # Usamos um gráfico de barras, que é intuitivo para graus discretos.
    plt.bar(graus, frequencias, color='seagreen', width=0.8)
    
    # A mudança principal está aqui: aplicamos a escala log apenas no eixo Y.
    plt.yscale('log')
    
    plt.title(f"{titulo} (Escala Linear-Log)")
    plt.xlabel("Grau (k) - [Escala Linear]")
    plt.ylabel("Número de Vértices (Frequência) - [Escala Log]")
    plt.grid(True, which="major", axis='y', ls="--", linewidth=0.5)
    
    try:
        plt.savefig(nome_arquivo)
        print(f"  - Gráfico salvo como '{nome_arquivo}'\n")
        print("-" * 100)
    except Exception as e:
        print(f"  - Ocorreu um erro ao salvar o gráfico: {e}\n")
        print("-" * 100)
        
    plt.close() # Evita que a figura fique aberta na memória



#=============================================================================================


def analisar_centralidades(G, top_n=5):
    """
    Calcula as principais métricas de centralidade e exibe os 'top_n' vértices mais centrais.
    - Centralidade de Grau (Degree): Vértices com mais conexões.
    - Centralidade de Proximidade (Closeness): Vértices mais próximos de todos os outros.
    - Centralidade de Intermediação (Betweenness): Vértices que atuam como pontes.
    
    Aviso: Centralidade de Proximidade e Intermediação podem ser computacionalmente
    intensivas em grafos muito grandes.
    """

    print(f"\nAnálise de Centralidades (Top {top_n} Vértices):")
    
    # 1. Centralidade de Grau (Degree Centrality)
    print("\n--- Centralidade de Grau (Degree) ---")
    print("Mede o número de conexões diretas de um vértice (popularidade).")
    try:
        centralidade_grau = nx.degree_centrality(G)
        # Ordena o dicionário pelo valor da centralidade
        top_grau = sorted(centralidade_grau.items(), key=lambda item: item[1], reverse=True)
        
        for i, (vertice, valor) in enumerate(top_grau[:top_n], 1):
            print(f"  {i}. Vértice: {vertice}, Centralidade: {valor:.4f}")
            
    except Exception as e:
        print(f"Não foi possível calcular a Centralidade de Grau: {e}\n")

    # 2. Centralidade de Proximidade (Closeness Centrality)
    print("\n--- Centralidade de Proximidade (Closeness) ---")
    print("Mede a proximidade média de um vértice a todos os outros vértices da rede.")
    try:
        # Closeness é calculada para cada componente conexo
        if not nx.is_connected(G) and not G.is_directed():
             print("  (Aviso: O grafo não é conexo. O cálculo é feito dentro de cada componente)")
        
        centralidade_proximidade = nx.closeness_centrality(G)
        top_proximidade = sorted(centralidade_proximidade.items(), key=lambda item: item[1], reverse=True)
        
        for i, (vertice, valor) in enumerate(top_proximidade[:top_n], 1):
            print(f"  {i}. Vértice: {vertice}, Centralidade: {valor:.4f}")
            
    except Exception as e:
        print(f"Não foi possível calcular a Centralidade de Proximidade: {e}\n")

    # 3. Centralidade de Intermediação (Betweenness Centrality)
    print("\n--- Centralidade de Intermediação (Betweenness) ---")
    print("Mede a frequência com que um vértice aparece nos caminhos mais curtos entre outros.")
    try:
        # Para grafos grandes, o cálculo pode ser muito lento.
        # Uma aproximação pode ser usada com o parâmetro 'k'. Ex: k=int(G.number_of_nodes() * 0.1)
        # Por padrão, vamos calcular o valor exato.
        print("  (Aviso: Esta operação pode ser MUITO lenta para grafos grandes)")
        centralidade_intermediacao = nx.betweenness_centrality(G, normalized=True)
        top_intermediacao = sorted(centralidade_intermediacao.items(), key=lambda item: item[1], reverse=True)
        
        for i, (vertice, valor) in enumerate(top_intermediacao[:top_n], 1):
            print(f"  {i}. Vértice: {vertice}, Centralidade: {valor:.4f}")

        print("-" * 100)
            
    except Exception as e:
        print(f"  Não foi possível calcular a Centralidade de Intermediação: {e}\n")


#=============================================================================================


def arvores_geradoras(G):
    """
    Calcula a Árvore Geradora Mínima (AGM) do grafo.
    A AGM é a sub-rede que conecta todos os vértices com o menor custo total
    de arestas possível. Esta análise é válida para grafos não-direcionados e ponderados.
    """

    print("\nAnálise de Árvore Geradora Mínima (AGM):\n")

    # A AGM é um conceito para grafos não-direcionados.
    if G.is_directed():
        print("  - Esta análise é projetada para grafos não-direcionados e não será executada.")
        print("  - Para grafos direcionados, o conceito análogo é a 'Arborescência'.\n")
        print("-" * 100)
        return

    # A AGM funciona sobre grafos conectados. Se não for, calcula-se uma para cada componente.
    if not nx.is_connected(G):
        print("  - O grafo não é conexo. O algoritmo encontrará uma 'floresta geradora mínima' (uma AGM para cada componente).")

    print("  - Calculando a estrutura de conexão mais eficiente (menor custo total)...")
    print("  - (Se as arestas não tiverem 'peso', NetworkX assume peso 1 para todas).")

    try:
        # O algoritmo de Prim ou Kruskal é usado por baixo dos panos aqui.
        # 'weight' especifica qual atributo da aresta usar como custo.
        mst = nx.minimum_spanning_tree(G, weight='weight')
        
        # O custo total é a soma dos pesos das arestas na árvore gerada.
        custo_total = mst.size(weight='weight')
        
        print("\n  Resultados da AGM:")
        print(f"  - Número de Vértices na AGM: {mst.number_of_nodes()}") # Será igual ao do grafo original
        print(f"  - Número de Arestas na AGM: {mst.number_of_edges()}") # Será (Nós - 1) se o grafo for conexo
        print(f"  - Custo Total (Soma dos Pesos): {custo_total:.4f}\n")
        print("-" * 100)

    except Exception as e:
        print(f"  Ocorreu um erro ao calcular a AGM: {e}\n")
        print("-" * 100)


#=============================================================================================


def analisar_clusters(G):
    """
    Detecta clusters na rede usando o método de Louvain.
    Comunidades são grupos de vértices mais conectados entre si do que com o resto da rede.
    Esta análise calcula também a modularidade, uma medida da qualidade da divisão.
    """

    print("\nAnálise de Clusters:\n")

    # O método de Louvain funciona em grafos não-direcionados.
    # Se o grafo for direcionado, usamos sua versão não-direcionada para a análise.
    G_para_analise = G
    if G.is_directed():
        print("  - O grafo é direcionado. A análise será feita na sua representação não-direcionada.")
        G_para_analise = G.to_undirected()
    
    # O grafo precisa ter arestas para encontrar comunidades
    if G_para_analise.number_of_edges() == 0:
        print("  - O grafo não possui arestas, não é possível detectar comunidades.\n")
        print("-" * 100)
        return

    try:
        print("  - Utilizando o algoritmo de Louvain para detectar comunidades...")
        
        # O resultado é uma lista de conjuntos, onde cada conjunto é uma comunidade
        comunidades = community.louvain_communities(G_para_analise, weight='weight')
        
        if not comunidades:
            print("  - Nenhuma comunidade foi detectada.\n")
            print("-" * 100)
            return

        # Calcular a modularidade da partição encontrada
        # A modularidade mede a força da divisão da rede em comunidades.
        # Valores > 0.3 indicam uma estrutura de comunidade significativa.
        modularity = community.modularity(G_para_analise, comunidades, weight='weight')
        
        # Estatísticas sobre as comunidades encontradas
        tamanhos = [len(c) for c in comunidades]
        
        print("\n  Resultados da Detecção de Comunidades:")
        print(f"  - Número de comunidades detectadas: {len(comunidades)}")
        print(f"  - Modularidade da partição: {modularity:.4f}")
        print("     (Valores acima de 0.3 geralmente indicam uma estrutura de comunidade significativa)")
        print(f"  - Tamanho da maior comunidade: {max(tamanhos)} vértices")
        print(f"  - Tamanho da menor comunidade: {min(tamanhos)} vértices")
        print(f"  - Tamanho médio das comunidades: {sum(tamanhos) / len(tamanhos):.2f} vértices\n")
        print("-" * 100)
        
    except Exception as e:
        print(f"  Ocorreu um erro ao detectar as comunidades: {e}\n")
        print("-" * 100)


#=============================================================================================


def analisar_cliques(G):
    """
    Encontra os cliques maximais na rede e fornece um resumo estatístico.
    Um clique é um subgrupo onde todos os nós estão conectados entre si.
    Aviso: Esta é uma operação computacionalmente intensiva.
    """

    print("\nAnálise de Cliques:")

    # O conceito de clique é para grafos não-direcionados.
    if G.is_directed():
        print("  - Esta análise é projetada para grafos não-direcionados e não será executada.\n")
        print("-" * 100)
        return

    try:
        # Encontra todos os cliques maximais. Retorna um iterador.
        cliques_maximais = list(nx.find_cliques(G))
        
        if not cliques_maximais:
            print("  - Nenhum clique foi encontrado na rede.\n")
            print("-" * 100)
            return
            
        # O "número de clique" é o tamanho do maior clique no grafo.
        tamanho_max_clique = 0
        if cliques_maximais:
             tamanho_max_clique = max(len(c) for c in cliques_maximais)
        
        print("\n  Resultados da Análise de Cliques:")
        print(f"  - Número total de cliques maximais encontrados: {len(cliques_maximais)}")
        print(f"  - Tamanho do maior clique (Clique Máximo): {tamanho_max_clique} vértices")

        # Conta quantos cliques de cada tamanho existem
        tamanhos_cliques = [len(c) for c in cliques_maximais]
        contagem = Counter(tamanhos_cliques)
        
        print("\n  Distribuição dos Tamanhos dos Cliques:")
        for tamanho, quantidade in sorted(contagem.items()):
            print(f"    - Cliques de tamanho {tamanho}: {quantidade}")

        print("")
        print("-" * 100)
            
    except Exception as e:
        print(f"  Ocorreu um erro ao analisar os cliques: {e}\n")
        print("-" * 100)


#=============================================================================================


def analisar_modelo(G):
    """
    Executa todas as análises e gera um relatório-resumo no console
    com uma sugestão de modelo de grafo correspondente.
    """

    print("\nAnálise - Modelo de Grafo\n")
    
    # --- Coletando dados básicos ---
    num_nos = G.number_of_nodes()
    num_arestas = G.number_of_edges()
    e_direcionado = G.is_directed()

    # --- Análises estruturais ---
    componentes = list(nx.connected_components(G.to_undirected()))
    diametro = -1
    if len(componentes) > 0:
        maior_subgrafo = G.subgraph(max(componentes, key=len))
        if nx.is_connected(maior_subgrafo.to_undirected()):
            diametro = nx.diameter(maior_subgrafo)


    # --- Análise de Comunidades ---
    modularidade = -1
    if not e_direcionado and num_arestas > 0:
        comunidades = community.louvain_communities(G, weight='weight')
        modularidade = community.modularity(G, comunidades, weight='weight')
    
    # --- Análise de Distribuição de Graus ---
    graus = [d for n, d in G.degree()]
    grau_medio = sum(graus) / num_nos
    grau_maximo = max(graus)


    # 1. Teste de Mundo Pequeno
    tem_mundo_pequeno = (diametro > 0 and diametro < 10 * (num_nos**0.25)) # Heurística
    if tem_mundo_pequeno:
        print("- 'Mundo Pequeno': SIM.")
    else:
        print("- 'Mundo Pequeno': NÃO.")

    # 2. Teste de Estrutura de Comunidades
    tem_comunidades = modularidade > 0.3
    if tem_comunidades:
        print("- 'Estrutura de Comunidades': SIM (modularidade > 0.3).")
    else:
        print("- 'Estrutura de Comunidades': NÃO.")

    # 3. Teste de Lei de Potência (Livre de Escala) - se o grau máximo é muito maior que o médio.
    e_livre_de_escala = grau_maximo > 5 * grau_medio and grau_maximo > 100
    if e_livre_de_escala:
        print("- 'Livre de Escala': SIM (presença de hubs - grau máx >> grau méd).")
    else:
        print("- 'Livre de Escala': NÃO.")

    # Conclusão Final
    print("\nResultado")
    if e_livre_de_escala and tem_mundo_pequeno and tem_comunidades:
        print("- O modelo que melhor representa a rede é o de BARABÁSI-ALBERT (Livre de Escala).")
        print()
        print("-" * 100)
    elif tem_mundo_pequeno and tem_comunidades and not e_livre_de_escala:
        print("- O modelo que melhor representa a rede é o de WATTS-STROGATZ (Mundo Pequeno).")
        print()
        print("-" * 100)
    else:
        print("- A rede exibe características que se aproximam do modelo de ERDÖS-RÉNYI (Aleatório).")
        print()
        print("-" * 100)


#=============================================================================================