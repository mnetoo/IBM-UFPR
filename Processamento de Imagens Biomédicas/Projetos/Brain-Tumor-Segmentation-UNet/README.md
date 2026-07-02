# NeuroSeg: Segmentação de Tumores Cerebrais com U-Net 🧠

![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=GREEN&style=for-the-badge)
![Badge Python](https://img.shields.io/badge/Python-3.13-blue?style=for-the-badge&logo=python)
![Badge TensorFlow](https://img.shields.io/badge/TensorFlow-2.20-orange?style=for-the-badge&logo=tensorflow)

> **Projeto de Deep Learning aplicado à detecção e segmentação automática de Gliomas em imagens de Ressonância Magnética (MRI).**

---

## Demonstração 📸

<img src="https://raw.githubusercontent.com/mnetoo/mnetoo/main/assets/Brain-Tumor-Segmentation-UNet/img1.png">
<img src="https://raw.githubusercontent.com/mnetoo/mnetoo/main/assets/Brain-Tumor-Segmentation-UNet/img2.png">
---

## Sobre o Projeto 💻

A segmentação manual de tumores cerebrais é um processo lento e propenso a erros humanos. Este projeto visa automatizar a localização precisa de tumores **LGG (Low-Grade Glioma)** pixel por pixel.

O modelo foi construído do zero utilizando a arquitetura **U-Net**, famosa por sua eficiência em segmentação biomédica, capaz de aprender tanto o contexto ("o que é") quanto a localização ("onde está") com poucos dados de treinamento.

## Principais Funcionalidades:
- **Segmentação Semântica:** Gera uma máscara binária indicando a área exata da lesão.
- **Pipeline de Dados Robusto:** Utiliza `tf.data` e **Data Augmentation** para evitar overfitting.
- **Web App Interativo:** Interface desenvolvida com **Streamlit** para uso médico simulado (upload e análise em tempo real).
- **Métricas Relevantes:** Avaliado pelo **Dice Coefficient** (focado na sobreposição da máscara), superior à acurácia comum para dados desbalanceados.

---

## Tecnologias Utilizadas 🛠️

*   **Python 3.13.10**
*   **TensorFlow / Keras:** Construção e treinamento da Rede Neural.
*   **OpenCV:** Processamento de imagens e leitura de arquivos `.tif`.
*   **Streamlit:** Interface web para deploy do modelo.
*   **NumPy & Pandas:** Manipulação de dados matriciais e tabulares.
*   **Scikit-Learn:** Divisão de dados e métricas.

---

## Arquitetura e Treinamento 📊

O modelo segue a estrutura **Encoder-Decoder** da U-Net:

1.  **Pré-processamento:** Imagens redimensionadas para `256x256` e normalizadas `[0,1]`.
2.  **Encoder:** 4 blocos convolucionais com **BatchNormalization** e **Dropout** para extração de características profundas.
3.  **Decoder:** Camadas de `Conv2DTranspose` com *skip connections* para recuperar a resolução espacial.
4.  **Otimização:** Uso de *EarlyStopping*, *ReduceLROnPlateau* e *Mixed Precision* para performance em GPU.

---

## Como Rodar Localmente 🚀

Siga os passos para rodar o projeto na sua máquina:

### 1. Clone o repositório
```bash
git clone https://github.com/mnetoo/Brain-Tumor-Segmentation-UNet
cd Brain-Tumor-Segmentation-UNet
```

### 2. Crie um ambiente virtual (Recomendado)
```bash
python -m venv venv
# Windows:
venv\Scripts\activate
# Linux/Mac:
source venv/bin/activate
```

### 3. Instale as dependências
```bash
pip install -r requirements.txt
```

### 4. Mova `app.py`, `main.ipynb` (e `model.keras` caso queira usar modelo pronto) para dentro do ambiente criado.
```bash
Brain-Tumor-Segmentation-UNet/             
├── venv/
   ├── kaggle_3m         # Dataset (não enviado no git)
   ├── app.py            # Aplicação Streamlit
   ├── main.ipynb        # Jupyter Notebook com o treinamento
   ├── model.keras       # Modelo treinado salvo
├── requirements.txt     # Dependências do projeto
└── README.md            # Documentação
```

### 5. Treine o Modelo (Opcional)
Se quiser treinar do zero, certifique-se de ter a pasta kaggle_3m baixada dentro do diretório e rode:
```bash
# Rode o notebook
python main.ipynb
```
#### (Download DataSet: https://www.kaggle.com/datasets/mateuszbuda/lgg-mri-segmentation) 

### 6. Execute o App Web
Para testar a interface:
```bash
streamlit run app.py
```

## Estrutura de Arquivos 📂
```bash
Brain-Tumor-Segmentation-UNet/             
├── venv/
   ├── kaggle_3m         # Dataset (não enviado no git)
   ├── app.py            # Aplicação Streamlit
   ├── main.ipynb        # Jupyter Notebook com o treinamento
   ├── model.keras       # Modelo treinado salvo
├── requirements.txt     # Dependências do projeto
└── README.md            # Documentação
```
#### (Download DataSet: https://www.kaggle.com/datasets/mateuszbuda/lgg-mri-segmentation)

## Resultados Obtidos 📈
A rede demonstrou capacidade de ignorar tecido saudável e focar especificamente nas anomalias de textura do tumor.

## Autor
Desenvolvido por Marcus S. A. R. Neto

Nota: Este repositório foi criado após a conclusão do desenvolvimento local. Como resultado, o commit inicial já contém a implementação completa do projeto.

## Licença ⚖️
Este dataset pertence a The Cancer Imaging Archive (TCIA) e foi obtido via Kaggle (LGG MRI Segmentation). O código neste repositório está sob licença MIT.
