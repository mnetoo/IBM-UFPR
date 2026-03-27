import os
import sys
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import auc

#===============================================================================================

def extrair_metricas(caminho_arquivo):

    """Lê o arquivo de texto e faz o parse manual dos dados"""

    dados = []
    if not os.path.exists(caminho_arquivo):
        return None
        
    with open(caminho_arquivo, 'r') as f:

        for linha in f:

            if "conf_thresh" in linha:
                # quebra a linha nas vírgulas e depois no '='
                partes = linha.split(',')
                
                t = float(partes[0].split('=')[1].strip())
                tp = int(partes[1].split('=')[1].strip())
                fp = int(partes[2].split('=')[1].strip())
                fn = int(partes[3].split('=')[1].strip())
                
                # cálculos das métricas de precisão, recall e F1-Score
                prec = tp / (tp + fp) if (tp + fp) > 0 else 0.0
                rec = tp / (tp + fn) if (tp + fn) > 0 else 0.0
                f1 = (2 * prec * rec) / (prec + rec) if (prec + rec) > 0 else 0.0
                
                dados.append({ 'thresh': t, 'prec': prec, 'rec': rec, 'f1': f1 })
    
    return sorted(dados, key=lambda x: x['thresh'])

#===============================================================================================

def calcular_ap(recalls, precisions):

    """Calcula a área sob a curva"""

    r = np.array(recalls)
    p = np.array(precisions)
    
    # ordenar pelo recall para o cálculo da área funcionar
    indices = np.argsort(r)
    r = r[indices]
    p = p[indices]
    
    # adiciona os pontos extremos para fechar a curva adequadamente
    r = np.concatenate([[0.0], r, [1.0]])
    p = np.concatenate([[p[0]], p, [0.0]])
    
    return auc(r, p)

#===============================================================================================

def main():

    # verifica se o usuário passou o diretório se não usa o atual
    if len(sys.argv) > 1:
        diretorio = sys.argv[1]
    else:
        diretorio = "."

    tamanhos = [512, 608, 800]
    cores = {512: 'blue', 608: 'orange', 800: 'green'}
    
    melhor_f1_global = -1
    config_campea = {}

    plt.figure(figsize=(8, 5))

    for sz in tamanhos:

        # tenta localizar o arquivo correto no diretório informado
        arquivo_nome = ""
        for f in os.listdir(diretorio):
            if str(sz) in f and f.endswith(".txt"):
                arquivo_nome = f
                break
        
        if not arquivo_nome:
            print(f"Arquivo de {sz}px não achado em {diretorio}")
            continue

        # caminho completo para leitura
        caminho_completo = os.path.join(diretorio, arquivo_nome)
        registros = extrair_metricas(caminho_completo)
        
        if not registros:
            continue

        recs = [d['rec'] for d in registros]
        precs = [d['prec'] for d in registros]
        
        # calculo do AP
        valor_ap = calcular_ap(recs, precs)
        
        # encontra a melhor configuração baseada no f1
        for r in registros:
            if r['f1'] > melhor_f1_global:
                melhor_f1_global = r['f1']
                config_campea = r
                config_campea['tamanho'] = sz

        plt.plot(recs, precs, color=cores[sz], label=f"Tamanho {sz} (AP={valor_ap:.4f})")

    # configurações do gráfico
    plt.title("Curva Precision-Recall")
    plt.xlabel("Recall")
    plt.ylabel("Precision")
    plt.legend(loc="lower left")
    plt.grid(alpha=0.2)
    
    caminho_grafico = os.path.join(diretorio, 'grafico.png')
    plt.savefig(caminho_grafico)
    
    plt.show()

#===============================================================================================

if __name__ == "__main__":
    main()