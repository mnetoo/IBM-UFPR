import utils
import networkx as nx
import analyzer
import config


#=================================================================================


def main():

    # Carrega grafo
    G_original = utils.carregar_rede(config.caminho_do_arquivo)


    # Converte para um grafo simples e não-direcionado
    G = utils.converter_simples_nao_direcionado(G_original)

    if G:
        # Exibe informações básicas do grafo
        analyzer.informacoes_basicas(G)

        # 1 - Análise de Ciclos, Componentes, Raio e Diâmetro
        analyzer.analisar_ciclos(G)
        analyzer.analisar_componentes_conexas(G)
        analyzer.analisar_raio_diametro(G)

        # 2 - Análise de Distribuição de Graus e Centralidades
        analyzer.analisar_distribuicao_graus(G)
        analyzer.analisar_centralidades(G)

        # 3 - Análise de Árvores Geradoras, Clusters e Cliques
        analyzer.arvores_geradoras(G)
        analyzer.analisar_clusters(G)
        analyzer.analisar_cliques(G)

        # 4 - Análise de Modelo de grafo
        analyzer.analisar_modelo(G)


#=================================================================================


if __name__ == "__main__":
    main()