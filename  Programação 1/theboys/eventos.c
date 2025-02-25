#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "conjunto.h"
#include "fprio.h"
#include "entidades.h"
#include "fila.h"




#define CHEGADA 0
#define ESPERA 1
#define DESISTE 2
#define AVISA 3
#define ENTRADA 4
#define SAIDA 5
#define VIAGEM 6
#define MISSAO 7
#define MORRE 8
#define FIM 9


int missao_concluida = 0;
int missao_adiada = 0;





/*=====================================================================================================================================*/


//  FUNÇÃO AUXILIAR PARA GERAR NÚMERO ALEATORIO EM UM INTERVALO
int aleat(int min, int max)
{
    return min + rand() % (max - min + 1);
}


/*=====================================================================================================================================*/


//  FUNÇÃO AUXILIAR PARA COMPARAR DADOS
int compara(const void *a, const void *b) 
{
    struct distancia_base *baseA = (struct distancia_base *)a;
    struct distancia_base *baseB = (struct distancia_base *)b;

    if (baseA->distancia < baseB->distancia) 
        return -1;

    if (baseA->distancia > baseB->distancia) 
        return 1;
    
    return 0;
}


/*=====================================================================================================================================*/


//  CRIA UM EVENTO E RETORNA UM PORNTEIRO PARA O EVENTO OU NULL SE FALHAR
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *e;

    if(!(e = malloc(sizeof(struct evento_t))))
    {
        return NULL;
    }
        
    e->tempo = tempo;
    e->tipo = tipo;
    e->dado1 = dado1;   // id_heroi (h)
    e->dado2 = dado2;   // id_base  (b)

    return e;
}


/*=====================================================================================================================================*/


//  DESTRÓI EVENTO
struct evento_t *destroi_evento (struct evento_t *e)
{
    
    if(e)
    {
        free(e);
        return NULL;
    }

    return NULL;
}


/*=====================================================================================================================================*/


//  FUNÇÃO PARA CRIAR MUNDO - INICIALIZA HERÓIS, BASES, MISSÕES
struct mundo cria_mundo()
{
    struct mundo mundo;

    //  INICIALIAÇÕES
    mundo.NHerois = N_HEROIS;
    mundo.NBases = N_BASES;
    mundo.NMissoes = N_MISSOES;
    mundo.tamanho_mundo = N_TAMANHO_MUNDO;
    mundo.tempo = 0;
    mundo.NHabilidades = N_HABILIDADES;
    mundo.simulacao = NULL;
    mundo.simulacao = fprio_cria();
    mundo.tentativas_max = 0;
    mundo.total_tentativas = 0;
    mundo.eventos_tratados = 0;
    mundo.herois_mortos = 0;
    mundo.tentativas_min = 1;


    // INICIALIZANDO OS HERÓIS
    for (int i = 0; i < N_HEROIS; i++)
    {
        mundo.vetor_herois[i].id_heroi = i;
        mundo.vetor_herois[i].habilidade = cjto_aleat(aleat(1, 3), N_HABILIDADES);
        mundo.vetor_herois[i].paciencia = aleat(0, 100);
        mundo.vetor_herois[i].velocidade = aleat(50, 5000);
        mundo.vetor_herois[i].experiencia = 0;
        mundo.vetor_herois[i].base = -1;
        mundo.vetor_herois[i].vida = true;        
    }


    // INICIALIZANDO AS MISSOES
    for (int i = 0; i < N_MISSOES; i++)
    {
        mundo.vetor_missoes[i].id_missao = i;
        mundo.vetor_missoes[i].habilidade = cjto_aleat(aleat(0, 10), N_HABILIDADES);
        mundo.vetor_missoes[i].perigo = aleat(0, 100);
        mundo.vetor_missoes[i].local_missaoX = aleat(0, N_TAMANHO_MUNDO - 1);
        mundo.vetor_missoes[i].local_missaoY = aleat(0, N_TAMANHO_MUNDO - 1);
        mundo.vetor_missoes[i].tentativas = 0;
    }


    // INICIALIZANDO AS BASES
    for (int i = 0; i < N_BASES; i++)
    {
        mundo.vetor_bases[i].id_base = i;
        mundo.vetor_bases[i].lotacao = aleat(6, 10);
        mundo.vetor_bases[i].presentes = cjto_cria(50);
        mundo.vetor_bases[i].espera = fila_cria();
        mundo.vetor_bases[i].espera->count = 0;
        mundo.vetor_bases[i].local_baseX = aleat(0, N_TAMANHO_MUNDO - 1);
        mundo.vetor_bases[i].local_baseY = aleat(0, N_TAMANHO_MUNDO - 1);
        mundo.vetor_bases[i].missoes_realizadas = 0;
    }

    return mundo;
}


/*=====================================================================================================================================*/


//  FUNÇÃO PARA DESTRUIR O MUNDO CRIADO
void destroi_mundo(struct mundo *mundo)
{
    for (int i = 0; i < N_HEROIS; i++)
        mundo->vetor_herois[i].habilidade = cjto_destroi(mundo->vetor_herois[i].habilidade);

    for (int i = 0; i < N_BASES; i++)
    {
        cjto_destroi(mundo->vetor_bases[i].presentes);
        mundo->vetor_bases[i].espera = fila_destroi(mundo->vetor_bases[i].espera);
    }

    for (int i = 0; i < N_MISSOES; i++)
        mundo->vetor_missoes[i].habilidade = cjto_destroi(mundo->vetor_missoes[i].habilidade);
}



/*=====================================================================================================================================*/


//  TIRA O HEROI DO CONJUNTO DE PRESENTES DA BASE E RETORNA UMA BASE ALEATÓRIA
int sai (int tempo, struct mundo *mundo, int h, int b)
{
    cjto_retira(mundo->vetor_bases[b].presentes, mundo->vetor_herois[h].id_heroi);

    printf("%6d: SAI    HEROI %2d BASE %d (%2d/%2d)\n", tempo, mundo->vetor_herois[h].id_heroi, mundo->vetor_bases[b].id_base, cjto_card(mundo->vetor_bases[b].presentes),
                                                            mundo->vetor_bases[b].lotacao);

    int base_aleat = aleat(0, N_BASES - 1);
    
    return base_aleat;
}


/*=====================================================================================================================================*/


//  CALCULA O TPB E RETORNA O VALOR
int entra (int tempo, struct mundo *mundo, int h, int b)
{
    int TPB;

    TPB = 15 + (mundo->vetor_herois[h].paciencia * aleat(1, 20));

    cjto_insere(mundo->vetor_bases[b].presentes, h);

    printf("%6d: ENTRA  HEROI %2d BASE %d (%2d/%2d) SAI %d\n", tempo, mundo->vetor_herois[h].id_heroi, mundo->vetor_bases[b].id_base, cjto_card(mundo->vetor_bases[b].presentes),
                                                                    mundo->vetor_bases[b].lotacao, tempo + TPB);

    return TPB;
}


/*=====================================================================================================================================*/


//  FUNÇÃO QUE AVISA O ESTADO DE UMA BASE PARA O PORTEIRO
void avisa (int tempo, struct mundo mundo, int b)
{
    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", tempo, mundo.vetor_bases[b].id_base,
           cjto_card(mundo.vetor_bases[b].presentes), mundo.vetor_bases[b].lotacao);

    //  IMPRIME A FILA DE ESPERA
    printf(" FILA ESPERA: [ ");
    
    // VERIFICA SE A FILA DE ESPERA NÃO ESTÁ VAZIA
    if (mundo.vetor_bases[b].espera != NULL && fila_tamanho(mundo.vetor_bases[b].espera) > 0) 
        fila_imprime(mundo.vetor_bases[b].espera);
    else 
        printf(" ");

    printf(" ]\n");
}


/*=====================================================================================================================================*/


//  FUNÇÃO PARA ADICIONAR O HEROI NA FILA DE ESPERA DA BASE
void espera (int tempo, struct mundo mundo, int h, int b)
{   
    int controle = fila_insere(mundo.vetor_bases[b].espera, mundo.vetor_herois[h].id_heroi); 
    if (controle == -1)
    {
        printf("Erro ao inserir na fila de espera!\n");
        exit(EXIT_FAILURE);
    }
    else
        // se foi possível inserir, atualiza o número max de ocupantes na fila
        if (mundo.vetor_bases[b].espera->num > mundo.vetor_bases[b].espera->count)
            mundo.vetor_bases[b].espera->count = mundo.vetor_bases[b].espera->num;

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", tempo, mundo.vetor_herois[h].id_heroi, mundo.vetor_bases[b].id_base, fila_tamanho(mundo.vetor_bases[b].espera));
}


/*=====================================================================================================================================*/


//  FUNÇÃO QUE CALCULA DISTÂNCIA DO HERIO ATEÉ A OUTRA BASE E RETORNA A DURAÇÃO
int viaja (int tempo, struct mundo *mundo, int h, int base_destino)
{
    double distancia;
    int duracao;

    //  SE HERÓI NAO PERTENCE A NENHUMA BASE
    if (mundo->vetor_herois[h].base == -1) 
    {
        distancia = N_TAMANHO_MUNDO*2;
        duracao = 0;
    }        
    else 
    {
        //  POSIÇÕES DAS BASES DE ORIGEM
        double pos_x_origem = mundo->vetor_bases[mundo->vetor_herois[h].base].local_baseX;
        double pos_y_origem = mundo->vetor_bases[mundo->vetor_herois[h].base].local_baseY;
        //  POSIÇÕES DAS BASES DE DESTINO
        double pos_x_destino = mundo->vetor_bases[base_destino].local_baseX;
        double pos_y_destino = mundo->vetor_bases[base_destino].local_baseY;

        //  CALCULA A DISTÂNCIA
        double distancia_x = (pos_x_destino - pos_x_origem) * (pos_x_destino - pos_x_origem);
        double distancia_y = (pos_y_destino - pos_y_origem) * (pos_y_destino - pos_y_origem);
        double distancia = sqrt(distancia_x + distancia_y);

        duracao = (int)ceil(distancia / mundo->vetor_herois[h].velocidade);
    }

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", tempo, mundo->vetor_herois[h].id_heroi, mundo->vetor_herois[h].base, base_destino, (int)distancia,
           mundo->vetor_herois[h].velocidade, tempo + duracao);

    return duracao;
}


/*=====================================================================================================================================*/


//  DEFINE UMA BASE DE DESTINO ALEATÓRIA
int desiste (int tempo, struct mundo *mundo, int h, int b)
{
    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, mundo->vetor_herois[h].id_heroi, mundo->vetor_bases[b].id_base);

    int base_destino;
    return base_destino = aleat(0, N_BASES - 1);
}


/*=====================================================================================================================================*/


//  EVENTO CHEGA HEROI (H) CHEGA NA BASE (B) NO TEMPO (T), (H) ANALISA O TAMANHO DA FILA E DECIDE SE ESPERA
int chega (int tempo, struct mundo mundo, int h, int b)
{
    int vagas, tamanho_fila;
    int espera = 0;

    //  ATUALIZA A BASE DO HERÓI
    mundo.vetor_herois[h].base = mundo.vetor_bases[b].id_base;


    //  VERIFICAÇÃO SE HÁ VAGAS NA BASE
    vagas = mundo.vetor_bases[b].lotacao > cjto_card(mundo.vetor_bases[b].presentes);


    //  VERIFICAÇÃO SE A FILA DE ESPERA ESTÁ VAZIA
    tamanho_fila = fila_tamanho(mundo.vetor_bases[b].espera);

    
    //  DECISÃO DO HEROI (H)
    if (vagas && tamanho_fila == 0)
        espera = 1; // ESPERA
    else if (mundo.vetor_herois[h].paciencia > (10 * tamanho_fila))
        espera = 1; // ESPERA
    else
        espera = 0; // NÃO ESPERA



    if (espera == 1)
    {
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA \n", tempo, mundo.vetor_herois[h].id_heroi, mundo.vetor_bases[b].id_base, 
                                            cjto_card(mundo.vetor_bases[b].presentes), mundo.vetor_bases[b].lotacao);
        return ESPERA; // ADD LEF (EVENTO ESPERA)
    }

    else
    {
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE \n", tempo, mundo.vetor_herois[h].id_heroi, mundo.vetor_bases[b].id_base, 
                                            cjto_card(mundo.vetor_bases[b].presentes), mundo.vetor_bases[b].lotacao);
        return DESISTE; // ADD LEF (EVENTO DESISTE)
    }

}


/*=====================================================================================================================================*/


// FUNÇÃO EVENTO FIM - APRESENTA AS ESTATÍSTICAS
void fim (int tempo, struct mundo *mundo)
{
    printf("%6d: FIM \n", tempo);
    printf("\n");


    //  EXIBE OS HERÓIS
    for (int i = 0; i < N_HEROIS; i++) 
    {
        printf("HEROI %2d    %s    PAC %3d    VEL %4d     EXP %4d     HABS [ ", 
                        mundo->vetor_herois[i].id_heroi, mundo->vetor_herois[i].vida ? "VIVO " : "MORTO", 
                        mundo->vetor_herois[i].paciencia, mundo->vetor_herois[i].velocidade, mundo->vetor_herois[i].experiencia);
        cjto_imprime(mundo->vetor_herois[i].habilidade);
        printf("]\n");
    }
    printf("\n");

   
    //  EXIBE AS BASES
    for (int i = 0; i < N_BASES; i++)  
    {
        printf("BASE %2d    LOT %2d     FILA MAX %2d     MISSOES %d\n", mundo->vetor_bases[i].id_base, mundo->vetor_bases[i].lotacao, 
                                                                        mundo->vetor_bases[i].espera->count, mundo->vetor_bases[i].missoes_realizadas);
    }   
    printf("\n");   

    


    //  ESTATÍSTICAS DOS EVENTOS
    printf("EVENTOS TRATADOS: %d\n", mundo->eventos_tratados);



    //  ESTATÍSTICAS DAS MISSÕES
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", missao_concluida, N_MISSOES, ((double)missao_concluida / N_MISSOES) * 100.0);
    


    // CAĹCULA A MÉDIA DAS TENTATIVAS
    double media_tentativas = (double)mundo->total_tentativas / N_MISSOES;
    //  ESTATÍSTICAS DAS TENTATIVAS
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", mundo->tentativas_min, mundo->tentativas_max, media_tentativas);



    //  CALCULA A TAXA DE MORTALIDADE
    double taxa_mortalidade = (double)mundo->herois_mortos / N_HEROIS * 100.0;
    //  ESTATÍSTICAS DAS MORTES
    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mortalidade);
}


/*=====================================================================================================================================*/


//  EVENTO MORRE 
//  MARCA A MORTE DE UM HEROI, LIBERA A VAGA E AVISA O PORTEIRO DA BASE
void morre (int tempo, struct mundo *mundo, struct fprio_t *f ,int h, int b)
{
    // RETIRA O HEROI DO CONJUNTO DE HEROIS PRESENTES NA BASE
    cjto_retira(mundo->vetor_bases[b].presentes, mundo->vetor_herois[h].id_heroi);
    mundo->vetor_herois[h].base = -1;


    // ATUALIZA HEROI COMO MORTO E INCREMENTA HERÓIS MORTOS NO MUNDO
    mundo->vetor_herois[h].vida = false;
    mundo->herois_mortos++;


    // IMPRIME MENSAGEM DE HEROI MORTO E LIBERA A VAGA
    printf("%6d: MORRE  HEROI %2d BASE %d (%2d/%2d)\n", tempo, mundo->vetor_herois[h].id_heroi, mundo->vetor_bases[b].id_base, 
           cjto_card(mundo->vetor_bases[b].presentes), mundo->vetor_bases[b].lotacao);


    // CRIA E INSERE NA LEF O EVENTO AVISA E INFORMA SOBRE NOVA VAGA
    struct evento_t *novo_evento = cria_evento(mundo->tempo, AVISA, mundo->vetor_herois[h].id_heroi, mundo->vetor_bases[b].id_base);
    fprio_insere(f , novo_evento, AVISA, mundo->tempo);
}


/*=====================================================================================================================================*/


// EVENTO MISSÃO    
int missao (int tempo, int indice_missao, struct mundo *mundo)
{
    int h, b;
    double distancia[N_BASES];
    struct distancia_base distanciasBases[N_BASES];


    //  INCREMENTA O TOTAL DE TENTATIVAS NO MUNDO E TENTATIVA DA MISSÃO EM ESPECÍFICO
    mundo->total_tentativas++;
    mundo->vetor_missoes[indice_missao].tentativas++;
    
    //  ATUALIZA A TENTATIVA MAX
    if (mundo->vetor_missoes[indice_missao].tentativas > mundo->tentativas_max)
        mundo->tentativas_max = mundo->vetor_missoes[indice_missao].tentativas;   



    //  CALCULA A DISTÂNCIA DE TODAS AS BASES DO MUNDO PARA A MISSÃO
    for(int i = 0; i < N_BASES; i++) 
    {
        distancia[i] = sqrt((mundo->vetor_bases[i].local_baseX - mundo->vetor_missoes[indice_missao].local_missaoX) *
                        (mundo->vetor_bases[i].local_baseX - mundo->vetor_missoes[indice_missao].local_missaoX) +
                        (mundo->vetor_bases[i].local_baseY - mundo->vetor_missoes[indice_missao].local_missaoY) *
                        (mundo->vetor_bases[i].local_baseY - mundo->vetor_missoes[indice_missao].local_missaoY));

        distanciasBases[i].distancia = distancia[i];
        distanciasBases[i].id_base = i;
    }


    //  ORDENA AS BASES USANDO QUICKSORT
    qsort(distanciasBases, N_BASES, sizeof(struct distancia_base), compara);


    printf("%6d: MISSAO %d TENT %d HAB REQ: ", tempo, mundo->vetor_missoes[indice_missao].id_missao, mundo->vetor_missoes[indice_missao].tentativas);
                                                cjto_imprime(mundo->vetor_missoes[indice_missao].habilidade);
    printf("\n");


    int base_localizada = -1;


    //  PROCURA A BASE MAIS PRÓXIMA QUE A UNIAO DAS HABILIDADES DO HEROIS CONTEM AS HABILIDADES NECESSARIAS
    for (b = 0; b < N_BASES; b++) 
    {
        //  conjunto para união das habilidades
        struct cjto_t *cjto_habilidades_base = cjto_cria(N_HABILIDADES);

        for (h = 0; h < N_HEROIS; h++) 
        {
            /* percorre todos os herois e verifica se estão na base mais proxima, se está faz a união das habilidades */
            if (cjto_pertence(mundo->vetor_bases[distanciasBases[b].id_base].presentes, mundo->vetor_herois[h].id_heroi)) 
            {   
                struct cjto_t * conj_uniao = cjto_uniao(cjto_habilidades_base, mundo->vetor_herois[h].habilidade);
                cjto_destroi(cjto_habilidades_base);
                cjto_habilidades_base = conj_uniao;
            }
        }

        
        /* se o conjunto das habilidades requeridas para a missao está contido na união das habilidades da base mais proxima, achou a base  */
         if (cjto_contem(cjto_habilidades_base, mundo->vetor_missoes[indice_missao].habilidade)) 
        {   
            base_localizada = distanciasBases[b].id_base;
            mundo->vetor_bases[base_localizada].missoes_realizadas++;
        }


        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS: ", tempo, mundo->vetor_missoes[indice_missao].id_missao, mundo->vetor_bases[distanciasBases[b].id_base].id_base, 
                                                            (int)distanciasBases[b].distancia);
        
        
/*        //  IMPRIME OS HERÓIS PRESENTES NA BASE
        for (h = 0; h < N_HEROIS; h++) 
        {
            if (cjto_pertence(mundo->vetor_bases[distanciasBases[b].id_base].presentes, mundo->vetor_herois[h].id_heroi)) 
            {
                printf("%2d ", mundo->vetor_herois[h].id_heroi);
            }
        }
        printf("\n");


        //  IMPRIME AS HABILIDADES DE CADA HEROI PRESENTE NA BASE QUE REALIZARÁ A MISSÃO
        for (h = 0; h < N_HEROIS; h++) 
        {
            if (cjto_pertence(mundo->vetor_bases[distanciasBases[b].id_base].presentes, mundo->vetor_herois[h].id_heroi)) 
            {
                printf("%6d: MISSAO %d HAB HEROI %2d: ", 
                    tempo, 
                    mundo->vetor_missoes[indice_missao].id_missao, 
                    mundo->vetor_herois[h].id_heroi);
                cjto_imprime(mundo->vetor_herois[h].habilidade);
                printf("\n");
            }
        }


        //  IMPRIME A UNIÃO DAS HABILIDADES DOS HERÓIS PRESENTES NA BASE
        printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", tempo, mundo->vetor_missoes[indice_missao].id_missao, distanciasBases[b].id_base);
                                                        cjto_imprime(cjto_habilidades_base);
        printf("\n");
*/

        cjto_destroi(cjto_habilidades_base);


        // SE ENCONTROU A BASE
        if (base_localizada != -1) 
        { 
            //  Itera sobre os heróis presentes na BMP para calcular o risco para cada um
            //  e determina se herói morre (cria e insere na LEF evento morre) ou incrementa experiência    
            for (int i = 0; i < N_HEROIS; i++) 
            {
                if (cjto_pertence(mundo->vetor_bases[base_localizada].presentes, mundo->vetor_herois[i].id_heroi)) 
                {
                    double paciencia = mundo->vetor_herois[i].paciencia;
                    double experiencia = mundo->vetor_herois[i].experiencia;
                    double risco = mundo->vetor_missoes[indice_missao].perigo / (paciencia + experiencia + 1.0);

                    int aleatorio = aleat(1, 30);

                    if (risco > aleatorio)
                    {
                        struct evento_t *novo_evento = cria_evento(tempo, MORRE, mundo->vetor_herois[i].id_heroi, mundo->vetor_bases[base_localizada].id_base);
                        fprio_insere(mundo->simulacao, novo_evento , MORRE, mundo->tempo);
                    }
                    else 
                        mundo->vetor_herois[i].experiencia += 1;
                }
            }

            missao_concluida++;
            printf("%6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", tempo, mundo->vetor_missoes[indice_missao].id_missao, mundo->vetor_bases[base_localizada].id_base);
            cjto_imprime(mundo->vetor_bases[base_localizada].presentes);
            printf("\n");
            return 1;
        }
        else
        {
            missao_adiada++;
            printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, mundo->vetor_missoes[indice_missao].id_missao);
            return 0;
        }
    }

    return 0;
}


/*=====================================================================================================================================*/