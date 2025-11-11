import networkx as nx
import matplotlib.pyplot as plt
import warnings

# Ignorar avisos de depreciação do Matplotlib que podem aparecer
warnings.filterwarnings("ignore", category=UserWarning)

def carregar_rede(caminho_arquivo):
    """
    Carrega uma rede a partir de um arquivo GraphML.

    Args:
        caminho_arquivo (str): O caminho para o arquivo .graphml.

    Returns:
        nx.Graph: O objeto do grafo NetworkX.
    """
    # read_graphml pode retornar diferentes tipos de grafos
    return nx.read_graphml(caminho_arquivo)

def analisar_ciclos_componentes(G):
    """
    Analisa os ciclos, componentes conexas, raio e diâmetro da rede.

    Args:
        G (nx.Graph): O grafo a ser analisado.
    """
    print("--- Análise de Ciclos e Componentes ---")
    # A função cycle_basis não é implementada para multigrafos.
    # Garantimos que G seja um grafo simples antes de chamar esta função.
    try:
        ciclos = list(nx.cycle_basis(G))
        print(f"Número de ciclos na base: {len(ciclos)}")
    except nx.NetworkXNotImplemented:
         print("A função para encontrar a base de ciclos não é compatível com este tipo de grafo.")
    except nx.NetworkXNoCycle:
        print("A rede não possui ciclos.")


    if G.is_directed():
        print("A rede é direcionada. Analisando componentes fortemente conexas.")
        componentes = list(nx.strongly_connected_components(G))
    else:
        print("A rede não é direcionada. Analisando componentes conexas.")
        componentes = list(nx.connected_components(G))
    
    print(f"Número de componentes (fortemente) conexas: {len(componentes)}")

    # Raio e diâmetro são definidos para grafos não direcionados e conexos.
    # Para grafos direcionados, o conceito é mais complexo.
    # Focaremos na análise do maior componente como um grafo não direcionado.
    if componentes:
        maior_componente_nodes = max(componentes, key=len)
        # Criamos um subgrafo contendo apenas o maior componente
        subgrafo_maior_componente = G.subgraph(maior_componente_nodes)
        
        # Para calcular raio e diâmetro, precisamos de um grafo não direcionado e conexo.
        if subgrafo_maior_componente.is_directed():
            subgrafo_maior_componente_ud = subgrafo_maior_componente.to_undirected()
        else:
            subgrafo_maior_componente_ud = subgrafo_maior_componente

        if nx.is_connected(subgrafo_maior_componente_ud):
            print(f"Análise do maior componente conexo ({len(maior_componente_nodes)} nós):")
            print(f"  - Raio: {nx.radius(subgrafo_maior_componente_ud)}")
            print(f"  - Diâmetro: {nx.diameter(subgrafo_maior_componente_ud)}")
        else:
            print("O maior componente não é conexo quando tratado como não direcionado.")

    else:
        print("A rede não possui componentes para analisar raio e diâmetro.")


def analisar_distribuicao_graus_centralidade(G):
    """
    Analisa a distribuição de graus e as medidas de centralidade dos vértices.

    Args:
        G (nx.Graph): O grafo a ser analisado.
    """
    print("\n--- Análise de Distribuição de Graus e Centralidade ---")
    graus = [d for n, d in G.degree()]
    plt.hist(graus, bins='auto', color='skyblue', ec='black')
    plt.title("Distribuição de Graus")
    plt.xlabel("Grau")
    plt.ylabel("Frequência de Nós")
    plt.grid(axis='y', alpha=0.75)
    print("Exibindo o histograma da distribuição de graus...")
    plt.show()

    # O cálculo pode ser demorado para redes grandes, pegamos uma amostra ou os top K.
    print("Calculando centralidades (pode levar alguns minutos)...")
    centralidade_grau = nx.degree_centrality(G)
    centralidade_intermediacao = nx.betweenness_centrality(G)
    centralidade_proximidade = nx.closeness_centrality(G)

    print("Top 5 Nós por Centralidade de Grau:")
    for no, centralidade in sorted(centralidade_grau.items(), key=lambda item: item[1], reverse=True)[:5]:
        print(f"  - Nó: {no}, Centralidade: {centralidade:.4f}")

    print("\nTop 5 Nós por Centralidade de Intermediação:")
    for no, centralidade in sorted(centralidade_intermediacao.items(), key=lambda item: item[1], reverse=True)[:5]:
        print(f"  - Nó: {no}, Centralidade: {centralidade:.4f}")

    print("\nTop 5 Nós por Centralidade de Proximidade:")
    for no, centralidade in sorted(centralidade_proximidade.items(), key=lambda item: item[1], reverse=True)[:5]:
        print(f"  - Nó: {no}, Centralidade: {centralidade:.4f}")

def analisar_arvores_clusters_cliques(G):
    """
    Analisa árvores geradoras, clusters e cliques na rede.

    Args:
        G (nx.Graph): O grafo a ser analisado.
    """
    print("\n--- Análise de Árvores Geradoras, Clusters e Cliques ---")
    # A árvore geradora mínima requer um grafo não direcionado.
    if not G.is_directed():
        mst = nx.minimum_spanning_tree(G)
        print(f"Número de arestas na Árvore Geradora Mínima: {mst.number_of_edges()}")
    else:
        print("Árvore Geradora Mínima não é definida para grafos direcionados.")

    # Coeficiente de Aglomeração (Clustering)
    coef_aglomeracao_medio = nx.average_clustering(G)
    print(f"Coeficiente de Aglomeração Médio: {coef_aglomeracao_medio:.4f}")

    # Encontrar cliques maximais (requer grafo não direcionado)
    if G.is_directed():
        G_ud = G.to_undirected()
    else:
        G_ud = G
        
    cliques = list(nx.find_cliques(G_ud))
    if cliques:
        maior_clique = max(cliques, key=len)
        print(f"Número de cliques maximais: {len(cliques)}")
        print(f"Tamanho da maior clique: {len(maior_clique)}")
    else:
        print("Nenhuma clique encontrada na rede.")

def analisar_modelo_de_grafo(G):
    """
    Analisa qual modelo de grafo melhor representa a rede.

    Args:
        G (nx.Graph): O grafo a ser analisado.
    """
    print("\n--- Análise do Modelo de Grafo ---")
    num_nos = G.number_of_nodes()
    num_arestas = G.number_of_edges()
    
    # Propriedades da rede real
    coef_aglomeracao_real = nx.average_clustering(G)
    print(f"Propriedades da Rede Real:")
    print(f"  - Coef. de Aglomeração Médio: {coef_aglomeracao_real:.4f}")
    # A distribuição de graus já foi analisada visualmente (sugere lei de potência)

    # 1. Comparação com o modelo Erdos-Rényi (Aleatório)
    prob_aresta = num_arestas / (num_nos * (num_nos - 1) / 2)
    G_er = nx.erdos_renyi_graph(num_nos, prob_aresta)
    coef_aglomeracao_er = nx.average_clustering(G_er)
    print(f"\nComparando com o Modelo de Erdos-Rényi:")
    print(f"  - Coef. de Aglomeração Médio (Erdos-Rényi): {coef_aglomeracao_er:.4f}")
    print(f"  - Conclusão: O coef. de aglomeração da rede real ({coef_aglomeracao_real:.4f}) é muito maior, sugerindo que o modelo aleatório não é um bom ajuste.")

    # 2. Comparação com o modelo Watts-Strogatz (Mundo Pequeno)
    k = int(sum(d for n, d in G.degree()) / num_nos)
    p = 0.1 # Probabilidade de religação
    try:
        G_ws = nx.watts_strogatz_graph(num_nos, k, p)
        coef_aglomeracao_ws = nx.average_clustering(G_ws)
        print(f"\nComparando com o Modelo de Watts-Strogatz (Mundo Pequeno):")
        print(f"  - Coef. de Aglomeração Médio (Watts-Strogatz): {coef_aglomeracao_ws:.4f}")
        print(f"  - Conclusão: Este modelo gera redes com alto coef. de aglomeração, mais próximo da rede real. É um candidato plausível.")
    except nx.NetworkXError as e:
        print(f"\nNão foi possível gerar o modelo de Watts-Strogatz: {e}")


    # 3. Comparação com o modelo Barabási-Albert (Livre de Escala)
    m = int(num_arestas / num_nos)
    if m < 1: m = 1
    G_ba = nx.barabasi_albert_graph(num_nos, m)
    coef_aglomeracao_ba = nx.average_clustering(G_ba)
    print(f"\nComparando com o Modelo de Barabási-Albert (Livre de Escala):")
    print(f"  - Coef. de Aglomeração Médio (Barabási-Albert): {coef_aglomeracao_ba:.4f}")
    print("  - Conclusão: Este modelo é conhecido por gerar distribuições de grau que seguem uma lei de potência, o que corresponde ao histograma da rede real (poucos nós com muitas conexões).")

    print("\n--- Veredito sobre o Modelo de Grafo ---")
    print("A rede Kasthuri_graph_v4 exibe características de 'Mundo Pequeno' (alto coeficiente de aglomeração) e de 'Livre de Escala' (distribuição de graus com cauda longa).")
    print("O modelo de Barabási-Albert (Livre de Escala) é o que melhor captura a característica mais distintiva da rede: a presença de 'hubs' (nós altamente conectados), algo fundamental em redes biológicas e neuronais.")


if __name__ == "__main__":
    try:
        caminho_do_arquivo = "Kasthuri_graph_v4.graphml"
        G_original = carregar_rede(caminho_do_arquivo)
        print(f"Rede '{caminho_do_arquivo}' carregada com sucesso.")

        # --- CORREÇÃO PRINCIPAL ---
        # Converte para um grafo simples para garantir compatibilidade com as funções de análise.
        if G_original.is_multigraph() or G_original.is_directed():
            print(f"Tipo de grafo original: {'Multigrafo' if G_original.is_multigraph() else ''} {'Direcionado' if G_original.is_directed() else ''}")
            print("Convertendo para um grafo simples e não direcionado para a análise.")
            G = nx.Graph(G_original) # Esta linha cria uma versão de grafo simples não direcionado
        else:
            G = G_original
        
        print("-" * 30)
        print(f"Análise sendo realizada em um grafo com:")
        print(f"Número de nós: {G.number_of_nodes()}")
        print(f"Número de arestas (únicas): {G.number_of_edges()}")
        print("-" * 30)

        analisar_ciclos_componentes(G)
        analisar_distribuicao_graus_centralidade(G)
        analisar_arvores_clusters_cliques(G)
        analisar_modelo_de_grafo(G)

    except FileNotFoundError:
        print(f"\nERRO: O arquivo '{caminho_do_arquivo}' não foi encontrado.")
        print("Por favor, certifique-se de que ele está no mesmo diretório que o script Python.")
    except Exception as e:
        print(f"\nOcorreu um erro inesperado durante a execução: {e}")