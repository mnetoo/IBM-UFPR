/*

--------- PROGRAMA PRINCIPAL - TRABALHO FINAL DE PROGRAMAÇÃO 1 ---------
<<<<<<< Updated upstream
-------- ALUNO: MARCUS SEBASTIÃO ADRIANO ROCHA NETO - 20240710 --------
=======
-------- ALUNO: MARCUS SEBASTIÃO ADRIANO ROCHA NETO - 20240710 ---------
>>>>>>> Stashed changes
----------------- PROFESSOR DAVID MENOTTI GOMES ------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "conjunto.h"
#include "fprio.h"
#include "fila.h"
#include "entidades.h"
#include "eventos.h"




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

#define PRIORIDADE 1


int main ()
{
    srand(100000);   
    struct mundo m = cria_mundo();
    struct evento_t *evento;
    struct evento_t *novo_evento;
    int xtipo;
    int xtempo;



/* ======================================================================================================================================= */


    //  CHEGADA DE CADA HERÓIS NUMA BASE ALEATÓRIA
    for (int i = 0; i < N_HEROIS; i++) 
    {
        int tempo = aleat(0, 4320);
        int baseAleat= aleat(0, N_BASES- 1);
     	
        evento = cria_evento(tempo, CHEGADA, m.vetor_herois[i].id_heroi, m.vetor_bases[baseAleat].id_base);

	    if (evento == NULL) 
        {
	        fprintf(stderr, "Erro ao criar evento de CHEGADA!\n");
	        exit(EXIT_FAILURE);
        }

        fprio_insere(m.simulacao, evento, CHEGADA, tempo);
    }


/* ======================================================================================================================================= */


    //  EVENTOS INICIAIS PARA AS MISSOES
    for (int i = 0; i < N_MISSOES; i++) 
    {
        int tempo = aleat(4320, T_FIM_DO_MUNDO);

        evento = cria_evento(tempo, MISSAO, m.vetor_missoes[i].id_missao, 0);
 	    
        if (evento == NULL) 
        {
	        fprintf(stderr, "Erro ao criar evento de MISSAO!\n");
	        exit(EXIT_FAILURE);
        }
       
       fprio_insere(m.simulacao, evento, MISSAO, tempo);
    }


/* ======================================================================================================================================= */


    //  ADICIONA O EVENTO FINAL PARA O FIM DA SIMULAÇÃO
    int tempo_fim = T_FIM_DO_MUNDO;
    evento = cria_evento(tempo_fim, FIM, 0, 0);
    if (evento == NULL) 
    {
        fprintf(stderr, "Erro ao criar evento de FIM!\n");
        exit(EXIT_FAILURE);
    }
    fprio_insere(m.simulacao, evento, FIM, tempo_fim);


/* ======================================================================================================================================= */


    evento = fprio_retira(m.simulacao, &xtipo, &xtempo);
        
    if (m.tempo < T_FIM_DO_MUNDO)
        m.eventos_tratados++;   


    while (evento->tempo <= T_FIM_DO_MUNDO)
    {
        m.tempo = evento->tempo;

        switch (evento->tipo) 
        {    

            case CHEGADA:
            //if (m.vetor_herois[evento->dado1].vida)
            //{
                int decisao = chega(m.tempo, m, evento->dado1, evento->dado2);
                //  cria e insere evento espera
                if (decisao == 1) 
                {
                    novo_evento = cria_evento(m.tempo, ESPERA, evento->dado1, evento->dado2);
                    fprio_insere(m.simulacao, novo_evento, ESPERA, m.tempo);
                } 
                //  cria e insere evento desiste
                else
                {
                    novo_evento = cria_evento(m.tempo, DESISTE, evento->dado1, evento->dado2);
                    fprio_insere(m.simulacao, novo_evento, DESISTE, m.tempo);
                }
            //  }
                break;     

/* ======================================================================================================================================= */

            case ESPERA:
                espera(evento->tempo, m, evento->dado1, evento->dado2);
                novo_evento = cria_evento(m.tempo, AVISA, evento->dado1, evento->dado2);
                fprio_insere(m.simulacao, novo_evento, AVISA, m.tempo);
                break;

/* ======================================================================================================================================= */

            case DESISTE:
                int destino = desiste(evento->tempo, &m, evento->dado1, evento->dado2);
                novo_evento = cria_evento(m.tempo, VIAGEM, evento->dado1, destino);
                fprio_insere(m.simulacao, novo_evento, VIAGEM, m.tempo);
                break;

/* ======================================================================================================================================= */

            case AVISA:
                avisa(evento->tempo, m, evento->dado2);
                int heroiRemovido;
                while (m.vetor_bases[evento->dado2].lotacao > cjto_card(m.vetor_bases[evento->dado2].presentes) && fila_tamanho(m.vetor_bases[evento->dado2].espera) != 0) 
                {
                    fila_retira(m.vetor_bases[evento->dado2].espera, &heroiRemovido);
                    printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d \n", evento->tempo, m.vetor_bases[evento->dado2].id_base, heroiRemovido);
                    cjto_insere(m.vetor_bases[evento->dado2].presentes, heroiRemovido);
                    novo_evento = cria_evento(m.tempo, ENTRADA, heroiRemovido, evento->dado2);
                    fprio_insere(m.simulacao, novo_evento, ENTRADA, m.tempo);
                }
                break;

/* ======================================================================================================================================= */

            case ENTRADA:
                int tpb = entra(evento->tempo, &m, evento->dado1, evento->dado2);
                novo_evento = cria_evento(m.tempo + tpb, SAIDA, evento->dado1, evento->dado2);
                fprio_insere(m.simulacao, novo_evento, SAIDA, m.tempo + tpb);  
                break;

/* ======================================================================================================================================= */

            case SAIDA:
            if (m.vetor_herois[evento->dado1].vida)
            {
                int aux = evento->dado2;    
                destino = sai(evento->tempo, &m, evento->dado1, evento->dado2);
                novo_evento = cria_evento(m.tempo, VIAGEM, evento->dado1, destino);
                fprio_insere(m.simulacao, novo_evento, VIAGEM, m.tempo);  
                                
                novo_evento = cria_evento(m.tempo, AVISA, evento->dado1, aux);
                fprio_insere(m.simulacao, novo_evento, AVISA, m.tempo);    
            }    
                break;

/* ======================================================================================================================================= */

            case VIAGEM:
                int duracao = viaja(evento->tempo, &m, evento->dado1, evento->dado2);
                novo_evento = cria_evento(m.tempo + duracao, CHEGADA, evento->dado1, evento->dado2);
                fprio_insere(m.simulacao, novo_evento, CHEGADA, m.tempo + duracao);
                break;

/* ======================================================================================================================================= */

            case MISSAO:
                int resultado_missao = missao(evento->tempo, evento->dado1, &m);
                if (resultado_missao == 0)
                {
                    novo_evento = cria_evento(m.tempo + 24 * 60, MISSAO, evento->dado1, 0);
                    fprio_insere(m.simulacao, novo_evento, MISSAO, novo_evento->tempo);
                }   
                break;

/* ======================================================================================================================================= */

            case MORRE:

                if (m.vetor_herois[evento->dado1].vida)
                        morre(evento->tempo, &m, m.simulacao, evento->dado1, evento->dado2);
                break;

/* ======================================================================================================================================= */

            case FIM:

                fim(evento->tempo, &m);
                destroi_evento(evento);
                m.simulacao = fprio_destroi(m.simulacao);
                destroi_mundo(&m);
                return 0;
        }

        destroi_evento(evento);
        evento = fprio_retira(m.simulacao, &xtipo, &xtempo);
        
        if (m.tempo < T_FIM_DO_MUNDO)
            m.eventos_tratados++;

        }

    m.simulacao = fprio_destroi(m.simulacao);
    destroi_mundo(&m);
    
    return 0;
}
