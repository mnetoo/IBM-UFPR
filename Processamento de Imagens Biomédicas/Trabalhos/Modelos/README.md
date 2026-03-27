# Avaliação de Modelos (YOLOv4)

Extrai métricas a partir de arquivos de resultado (.txt), calcula **Precisão, Recall, F1-Score** para múltiplos thresholds e gera a **curva Precision-Recall com AP (Area Under Curve)**.

**Avaliação de Modelos**
Aluno: Marcus Sebastião Adriano Rocha Neto
GRR: 20240710

## Como executar:

---

### 1. Acesse a pasta do projeto

```bash
cd caminho/para/o/projeto
```

### 2. Crie o ambiente virtual

```bash
python3 -m venv venv
```

### 3. Ative o ambiente virtual

```bash
source venv/bin/activate
```

### 4. Instalar dependências

```bash
python3 -m pip install -r requirements.txt
```

### 5. Executar

```bash
python3 metrics.py [input_dir]
python3 metrics.py 
```
**[input_dir]: diretório contendo os arquivos .txt.**
**Caso nenhum diretório seja fornecido, o programa considerará o diretório atual para leitura e gravação dos resultados.**

#### Exemplos:
```bash
python3 metrics.py
python3 metrics.py ./dados
```

## Como funciona:

O script lê os arquivos .txt de entrada e calcula as métricas. Gera e exibe em tela o gráfico Precision-Recall (AP) e arquivo .txt de recomendação. Os arquivos que são gerados serão salvos no mesmo diretório onde os arquivos de entrada estão, ou seja, [input_dir].