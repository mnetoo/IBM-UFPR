# Porta OR com Perceptron Simples

import numpy as np

# Vetor X:
entradas = [ [0, 0], [0, 1], [1, 0], [1, 1] ]

# Targets
saidas_esperadas = [0, 1, 1, 1]
# Para porta AND, use: [0, 0, 0, 1]

# Configurações do Perceptron
pesos = [0.0, 0.0]
bias = 0.0            
taxa_aprendizado = 0.1
epocas = 100   


def prever(entrada_atual, pesos, bias):
    a = np.dot(entrada_atual, pesos) + bias
    if a >= 0:
        return 1
    else:
        return 0
    
print("Iniciando Treinamento do Perceptron\n")
for epoca in range(epocas):
    erro_total = 0
    
    # loop para passar por cada amostra de dados
    for i in range(len(entradas)):
        entrada_atual = entradas[i]
        alvo = saidas_esperadas[i]
        
        # chuta valor inicial
        previsao = prever(entrada_atual, pesos, bias)
        
        # calcula o erro (real - chute)
        erro = alvo - previsao
        
        # se teve erro, atualizamos os pesos e o bias
        if erro != 0:
            erro_total += 1
            bias = bias + (taxa_aprendizado * erro)
            
            # atualiza cada peso individualmente com loop
            for j in range(len(pesos)):
                pesos[j] = pesos[j] + (taxa_aprendizado * erro * entrada_atual[j])
                
            print(f"  - Ajuste na amostra {entrada_atual}: Erro={erro}. Novos Pesos: {pesos}, Novo Bias: {bias:.2f}")

    print(f"Época {epoca+1}: Total de erros = {erro_total}")

    # se não houver erros convergiu
    if erro_total == 0:
        print("\n Treinamento concluído!")
        break

print("\n Testando o Modelo Treinado:")
for i in range(len(entradas)):
    res = prever(entradas[i], pesos, bias)
    print(f"Entrada: {entradas[i]} -> Previsão: {res} (Esperado: {saidas_esperadas[i]})")