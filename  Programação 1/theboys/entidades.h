#ifndef ENTIDADE
#define ENTIDADE

#include "fprio.h"
#include "conjunto.h"
#include "lista.h"
#include "fila.h"

    
#define T_INICIO          0
#define T_FIM_DO_MUNDO    525600    
#define N_TAMANHO_MUNDO   20000
#define N_HABILIDADES     10
#define N_HEROIS          (N_HABILIDADES * 5)
#define N_BASES           (N_HEROIS / 5)
#define N_MISSOES         (T_FIM_DO_MUNDO / 100)


/*=====================================================================================================================================*/


// Definindo as estruturas
struct heroi 
{
    int id_heroi;           
    struct cjto_t *habilidade;
    int paciencia;   
    int velocidade;   
    int experiencia;  
    int base;
    bool vida;
};


/*=====================================================================================================================================*/

struct base 
{
    int id_base;             
    int lotacao;         
    struct cjto_t *presentes;  
    struct fila_t *espera;  
    int local_baseX;         
    int local_baseY;     
    int missoes_realizadas;     
};

/*=====================================================================================================================================*/


struct missao 
{
    int id_missao;             
    struct cjto_t *habilidade;  
    int perigo;          
    int local_missaoX;          
    int local_missaoY;    
    int tentativas; 
};


/*=====================================================================================================================================*/


struct mundo 
{
    int NHerois;         
    struct heroi vetor_herois[N_HEROIS];    
    int NBases;          
    struct base vetor_bases[N_BASES];     
    int NMissoes;        
    struct missao vetor_missoes[N_MISSOES];  
    int NHabilidades;    
    int tamanho_mundo;         
    int tempo;
    struct fprio_t* simulacao;
    int eventos_tratados;
    int herois_mortos;
    int total_tentativas;
    int tentativas_max;
    int tentativas_min;
};


/*=====================================================================================================================================*/


struct evento_t 
{
    int tempo;  //  TEMPO DO EVENTO 
    int tipo;   //  TIPOS DE EVENTO
    int dado1;  //  DADOS DO EVENTO id heroi, se sequencial
    int dado2;  //  DADOS DO EVENTO id base, aleatório
};


/*=====================================================================================================================================*/


struct distancia_base 
{
    double distancia;
    int id_base;
};


/*=====================================================================================================================================*/


#endif
