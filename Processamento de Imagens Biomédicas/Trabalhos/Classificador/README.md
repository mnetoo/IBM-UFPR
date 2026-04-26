# Classificador de Pneumothorax por Comparação de Histogramas

Classificador Leave-One-Out (LOO) usando 4 métodos de
comparação de histogramas do OpenCV sobre imagens DICOM do dataset `siim_small`.

---

## Requisitos

- Python 3.8+
- Jupyter Notebook ou JupyterLab
- Pacotes Python:

```
pip install pydicom opencv-python numpy matplotlib scikit-learn notebook
```

---

## Como Baixar o Dataset

```bash
wget -c https://s3.amazonaws.com/fast-ai-imagelocal/siim_small.tgz
tar -xzf siim_small.tgz
```

Ou com curl:

```bash
curl -LO https://s3.amazonaws.com/fast-ai-imagelocal/siim_small.tgz
tar -xzf siim_small.tgz
```

---

### Ajuste de Caminho (se necessário)

Na **Célula 1** há a variável `BASE_PATH`:

```python
BASE_PATH = "./siim_small/"  # Caminho base onde a pasta train/ está localizada
```

Se a pasta `train/` estiver em outro local, altere o valor. Exemplo:

```python
BASE_PATH = "/home/usuario/datasets/siim_small"
```

Os caminhos nos arquivos `.txt` já são relativos (ex.: `train/Pneumothorax/000001.dcm`),
portanto `BASE_PATH` é apenas o prefixo a ser concatenado.

Você deve fazer o upload dos arquivos `.txt` no Colab para o programa ler cada um deles para ler as imagens.

---

## Saídas Geradas

| Arquivo                  | Descrição                                              |
|--------------------------|--------------------------------------------------------|
| `resultados.txt`         | Matrizes de confusão e métricas de todos os métodos   |
| `confusion_matrices.png` | Visualização gráfica das 4 matrizes de confusão       |

---

## Metodologia

### Leave-One-Out (LOO)

Para cada uma das 30 imagens:
1. A imagem é usada como **teste**.
2. Seu histograma é comparado com os **29 histogramas restantes**.
3. A imagem é classificada com a **mesma classe do vizinho mais similar** (1-NN).

Esse processo se repete até que todas as imagens tenham sido testadas.

### Métodos de Comparação

| Constante OpenCV         | Nome            | Similaridade          |
|--------------------------|-----------------|-----------------------|
| `cv2.HISTCMP_CORREL`     | Correlação      | Maior = mais similar  |
| `cv2.HISTCMP_CHISQR`     | Qui-Quadrado    | Menor = mais similar  |
| `cv2.HISTCMP_INTERSECT`  | Interseção      | Maior = mais similar  |
| `cv2.HISTCMP_BHATTACHARYYA` | Bhattacharyya | Menor = mais similar  |

### Métricas

- **Classe Positiva:** Pneumothorax
- **Classe Negativa:** No Pneumothorax

```
Sensibilidade  = TP / (TP + FN)
Especificidade = TN / (TN + FP)
Acurácia       = (TP + TN) / Total
```

| Sigla | Significado                                                   |
|-------|---------------------------------------------------------------|
| TP    | Pneumothorax classificado corretamente como Pneumothorax      |
| FN    | Pneumothorax classificado erroneamente como No Pneumothorax   |
| FP    | No Pneumothorax classificado erroneamente como Pneumothorax   |
| TN    | No Pneumothorax classificado corretamente como No Pneumothorax|
