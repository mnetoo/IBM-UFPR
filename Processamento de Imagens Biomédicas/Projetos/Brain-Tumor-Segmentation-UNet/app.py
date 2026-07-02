import streamlit as st
import tensorflow as tf
import cv2
import numpy as np
from PIL import Image

# --- CONFIGURAÇÃO ---
IMG_SIZE = 256  

st.set_page_config(page_title="Detector de Tumor (Glioma)", page_icon="🧠")

st.title("Detector de Tumores por MRI 🧠")
st.write("Faça upload de uma imagem de ressonância magnética.")

# --- CARREGAMENTO DO MODELO ---
@st.cache_resource
def load_my_model():
    return tf.keras.models.load_model('model.h5', compile=False)

try:
    model = load_my_model()
except Exception as e:
    st.error(f"Erro ao carregar o modelo. {e}")
    st.stop()

uploaded_file = st.file_uploader("Escolha uma imagem TIF, JPG ou PNG", type=["tif", "jpg", "png", "jpeg"])

if uploaded_file is not None:
    # Carregar a imagem do Upload
    image = Image.open(uploaded_file)
    image_display = np.array(image.convert('RGB'))
    
    img_array = np.array(image.convert('RGB'))
    img_array = cv2.resize(img_array, (IMG_SIZE, IMG_SIZE))
    img_array = img_array / 255.0
    img_input = np.expand_dims(img_array, axis=0) # Adiciona batch dimension (1, 128, 128, 3)

    col_preview, col_result = st.columns(2)
    with col_preview:
        st.subheader("Sua Imagem")
        st.image(image_display, use_container_width=True)

    if st.button("Detectar Tumor"):
        with st.spinner('Analisando imagem...'):
            try:
                # Faz a previsão
                prediction = model.predict(img_input)
                
                # Transforma a probabilidade em máscara binária (0 ou 1)
                mask = (prediction > 0.5).astype(np.float32)[0]
                
                with col_result:
                    st.subheader("Resultado da Análise")
                    st.image(mask, caption="Área Segmentada...", clamp=True, use_container_width=True)

                pixels_tumor = np.sum(mask)
                total_pixels = IMG_SIZE * IMG_SIZE
                ocupacao = (pixels_tumor / total_pixels) * 100
                
                st.divider()
                if ocupacao > 0:
                    st.error(f"**Tumor Detectado!**")
                    st.write(f"A lesão ocupa aproximadamente **{ocupacao:.2f}%** da área da imagem analisada.")
                else:
                    st.success("**Nenhum tumor detectado** nesta fatia.")

            except Exception as e:
                st.error(f"Ocorreu um erro no processamento: {e}")