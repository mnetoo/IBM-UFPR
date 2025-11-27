import networkx as nx
caminho_da_rede = "kasthuri_graph_v4.graphml"


#=============================================================================================


def carregar_rede(caminho_da_rede):
    """
    Carrega uma rede a partir de um arquivo GraphML.

    Args:
        caminho_da_rede (str): O caminho para o arquivo .graphml.

    Returns:
        nx.Graph: O objeto do grafo NetworkX.
    """

    if(caminho_da_rede is None):
        print("Caminho do arquivo não fornecido.")
        return None
    
    else:
        print(f"\nRede '{caminho_da_rede}' carregada com sucesso.\n")
        return nx.read_graphml(caminho_da_rede)
    

#=============================================================================================


def converter_simples_nao_direcionado(G):
    """
    Converte um grafo para um grafo simples e não-direcionado se necessário.
    Args:
        G (nx.Graph): O grafo original.
    Returns:
        nx.Graph: O objeto do grafo NetworkX.
    """

    if G.is_multigraph() or G.is_directed():
        print(f"Tipo de grafo original: {'Multigrafo' if G.is_multigraph() else ''} {'Direcionado' if G.is_directed() else ''}")
        print("Convertendo para um grafo simples e não direcionado para a análise.\n")
        print("-" * 100)
        return nx.Graph(G)
    
    else:
        return G
    

#=============================================================================================