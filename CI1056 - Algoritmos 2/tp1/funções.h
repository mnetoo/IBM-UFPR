/*

--------    PROTOTIPAÇÃO DAS FUNÇÕES DE ORDENAÇÃO E BUSCA    --------
--------    Algoritmos de Ordenação: QuickSort, ShellSort, SelectionSort    --------
--------    Algoritmos de Busca: Sequencial, Binária    --------
--------    TRABALHO PRÁTICO - PROF. DR .ELIAS     --------

*/


#ifndef FUNCOES_H       // Define guardas para evitar inclusão múltipla do arquivo de cabeçalho
#define FUNCOES_H


#include <stdio.h>    // Biblioteca para funções de entrada e saída (ex: printf, scanf)
#include <stdlib.h>   // Biblioteca para alocação de memória, conversões e outras funções utilitárias
#include <string.h>   // Biblioteca para manipulação de strings
#include <time.h>     // Biblioteca para manipulação de data e hora (ex: função time)
#include <stdbool.h>  // Biblioteca para tipos booleanos (ex: true, false)
#include <math.h>     // Biblioteca para funções matemáticas (ex: sqrt, pow)


#define TAM 1024        // Define o tamanho máximo do vetor
#define MAX_VAL 2048    // Define o valor máximo dos números aleatórios no vetor
#define MAX_NUM 100000  // Define o valor máximo para números aleatórios em certas funções


// Variáveis globais que rastreiam o número de trocas e comparações realizadas em algoritmos de ordenação e busca
extern int contagemTrocas;
extern int contagemComparacoes;


/*================================================================================================================*/


//                       Funções utilitárias para operações comuns no programa


// Preenche um vetor de inteiros com valores aleatórios entre 0 e MAX_VAL
void geraVetor(int vetor[]);

// Exibe o menu de opções ao usuário e retorna a opção selecionada
int menu();

// Executa a operação correspondente à opção escolhida pelo usuário
void program(int opcao);

// Imprime todos os elementos de um vetor de inteiros
void imprimeVetor(int vetor[], int n);

// Troca o conteúdo de duas variáveis inteiras
void trocar(int *a, int *b);

// Exibe o número de trocas e comparações realizadas em um método de ordenação ou busca específico
void exibirContagens(char *metodo);

// Função auxiliar para calcular a média de um conjunto de valores
double calcularMedia(int valores[], int numExecucoes);

// Função auxiliar para calcular o desvio padrão de um conjunto de valores
double calcularDesvioPadrao(int valores[], int numExecucoes, double media);

// Função auxiliar para calcular o total de comparações realizadas
double calcularTotalComparacoes(int valores[], int numExecucoes);



/*================================================================================================================*/


                    /* QUICK SORT UTILIZANDO O ÚLTIMO ELEMENTO DO VETOR COMO PIVÔ */


// Particiona o vetor usando um elemento aleatório como pivô e retorna o índice do pivô
int particionarAleatorio(int vetor[], int inicio, int fim);

// Ordena o vetor usando Quick Sort com um elemento aleatório como pivô
void quickSortAleatorio(int vetor[], int inicio, int fim);



                    /* QUICK SORT UTILIZANDO A MEDIANA DE TRÊS ELEMENTOS DO VETOR */


// Particiona o vetor usando a mediana de três (primeiro, meio e último elementos) como pivô
int particionarMedianaDeTres(int vetor[], int inicio, int fim);

// Encontra a mediana de três elementos (primeiro, meio e último) e coloca o pivô no fim do intervalo
int medianaDeTres(int vetor[], int inicio, int fim);

// Ordena o vetor usando Quick Sort com a mediana de três como pivô
void quickSortMedianaDeTres(int vetor[], int inicio, int fim);


/*================================================================================================================*/


                    /* SHELL SORT UTILIZANDO A SEQUÊNCIA DE HIBBARD */ 


// Ordena o vetor usando Shell Sort com a sequência de Hibbard para o cálculo do gap
void shellSortHibbard(int vetor[], int n);



                    /* SHELL SORT UTILIZANDO A SEQUÊNCIA DE KNUTH */


// Ordena o vetor usando Shell Sort com a sequência de Knuth para o cálculo do gap
void shellSortKnuth(int vetor[], int n);


/*================================================================================================================*/


                                    /* SELECTION SORT */

// Ordena o vetor utilizando o método Selection Sort
void selectionSort(int vetor[], int n);



/*================================================================================================================*/


                                    /* BUSCA SEQUENCIAL */


// Realiza uma busca sequencial para encontrar um elemento no vetor, com contagem de comparações
int buscaSequencial(int vetor[], int tamanho, int elemento, int *contagemComparacoes);

// Função para realizar a busca sequencial com entrada do usuário ou número aleatório
void realizarBuscaSequencial(int vetor[], int tamanho);

// Realiza a busca sequencial para um número aleatório no vetor
void BuscaSequencialAleat(int vetor[], int tamanho, int *comparacoes);


/*================================================================================================================*/


                                    /* BUSCA BINÁRIA */            


// Realiza uma busca binária em um vetor ordenado, com contagem de comparações
int buscaBinaria(int vetor[], int tamanho, int elemento, int *contagemComparacoes);

// Função para realizar a busca binária com entrada do usuário ou número aleatório
void realizarBuscaBinaria(int vetor[], int tamanho);

// Realiza a busca binária para um número aleatório no vetor
void BuscaBinariaAleat(int vetor[], int tamanho, int *comparacoes);



/*================================================================================================================*/


#endif // Fim do define guardas para evitar inclusão múltipla