#include "includes.h"


//============================================================================


bool tem_chao_abaixo(float x, float y) 
{
    if (x >= 0 && x <= 640)
        return y >= 400;

    return false;  // fora da área com chão
}


//============================================================================


// Simula plataformas fixas com base no fundo
bool tem_chao_visivel(float x) 
{
    // Cada faixa representa uma "plataforma" do chão principal
    return (
        (x >= 0 && x <= 450) ||
        (x >= 755 && x <= 865)
    );
}


//============================================================================