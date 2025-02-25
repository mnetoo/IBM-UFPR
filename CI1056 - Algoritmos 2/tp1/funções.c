/*

--------    IMPLEMENTAÇÃO DAS FUNÇÕES DE ORDENAÇÃO E BUSCA    --------
--------    Algoritmos de Ordenação: QuickSort, ShellSort, SelectionSort    --------
--------    Algoritmos de Busca: Sequencial, Binária    --------
--------    TRABALHO PRÁTICO - PROF. DR .ELIAS     --------


*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include "funções.h" 

int v[TAM];
int v1[TAM];
int copiav [TAM];
int copiav1 [TAM];
bool vetorGerado = false;  // Variável para controlar se o vetor foi gerado


/*===========================================================================================================*/


//                                              GERA VETOR ALEATORIO

// Função que preenche um vetor de inteiros com valores aleatórios entre 0 e MAX_VAL
void geraVetor(int vetor[]) 
{
    // Loop para percorrer cada posição do vetor até o tamanho definido por TAM
    for (int i = 0; i < TAM; i++) 
    {
        // Atribui um valor aleatório a cada posição do vetor
        // rand() % (MAX_VAL + 1) gera um número entre 0 e MAX_VAL (incluindo ambos)
        vetor[i] = rand() % (MAX_VAL + 1);
        memcpy(copiav, v, TAM * sizeof(int));
    }
}


/*===========================================================================================================*/


//                                         IMPRESSÃO VETOR

// Imprime um vetor de inteiros
void imprimeVetor(int vetor[], int n) 
{
    if (n > TAM)
        n = TAM;  // Limita a impressão ao tamanho máximo do vetor

    for (int i = 0; i < n; i++)
        printf("%d ", vetor[i]);

    printf("\n");
}


/*===========================================================================================================*/


//                                             CALCULA OS DADOS

// Função auxiliar para calcular a média de um conjunto de valores
double calcularMedia(int valores[], int numExecucoes) 
{
    int soma = 0;  // Variável para acumular a soma dos valores

    // Percorre cada valor no array e adiciona à soma total
    for (int i = 0; i < numExecucoes; i++) {
        soma += valores[i];
    }

    // Retorna a média como um valor do tipo double
    return (double)soma / numExecucoes;
}


// Função auxiliar para calcular o desvio padrão de um conjunto de valores
double calcularDesvioPadrao(int valores[], int numExecucoes, double media) 
{
    double somaDesvios = 0;  // Variável para acumular a soma dos quadrados das diferenças

    // Percorre cada valor no array e calcula o quadrado da diferença para a média
    for (int i = 0; i < numExecucoes; i++) {
        somaDesvios += pow(valores[i] - media, 2);  // Calcula (valor - média)² e adiciona à somaDesvios
    }

    // Retorna o desvio padrão, que é a raiz quadrada da média dos desvios quadrados
    return sqrt(somaDesvios / numExecucoes);
}


// Função auxiliar para calcular o total de comparações realizadas
double calcularTotalComparacoes(int valores[], int numExecucoes) 
{
    int total = 0;  // Variável para acumular o total das comparações

    // Percorre cada valor no array e adiciona ao total
    for (int i = 0; i < numExecucoes; i++) {
        total += valores[i];
    }

    // Retorna o total acumulado de comparações
    return total;
}


/*===========================================================================================================*/


//                                              MENU INTERATIVO


// Função para exibir o menu e retornar a opção escolhida
int menu() 
{
    int opcao;
    static bool primeiraExecucao = true; // Controle para verificar se é a primeira execução da função

    // Mensagem de boas-vindas exibida apenas na primeira execução
    if (primeiraExecucao) 
    {
        printf("\n");
        printf("\n");
        printf("                                    ||||   |||||  |   |      |     |  |||  |    |  ||||   |||  |\n");
        printf("                                    |   |  |      || ||      |     |   |   ||   |  |   | |   | |\n");
        printf("                                    |   |  |      | | |       |   |    |   | |  |  |   | |   | |\n");
        printf("                                    ||||   ||||   |   |       |   |    |   | |  |  |   | |   | |\n");
        printf("                                    |   |  |      |   |        | |     |   |  | |  |   | |   | |\n");
        printf("                                    |   |  |      |   |        | |     |   |  | |  |   | |   | |\n");
        printf("                                    ||||   |||||  |   |         |     |||  |   ||  ||||   |||  .\n");
        printf("\n");

        printf("                                Trabalho Prático (Ordenação e Pesquisa) - Disciplina de Algoritmos II\n");
        printf("                                             Prof. Dr. Elias Procópio Duarte Júnior!\n");
        printf("\n");
        printf("                                        Implementação de algoritmos de ordenação e busca.\n");
        printf("\n");
        printf("Selecione a operação desejada:\n");
        printf("\n");
        primeiraExecucao = false;
    }

    // Exibe o menu de opções
    printf("\n");
    printf("0. Parar Programa\n");
    printf("1. Gerar Vetor\n");
    printf("2. QuickSort - [Pivô Aleatório]\n");
    printf("3. QuickSort - [Pivô Mediana de Três]\n");
    printf("4. ShellSort - [Sequência de Knuth]\n");
    printf("5. ShellSort - [Sequência de Hibbard]\n");
    printf("6. SelectionSort - [Quadrático]\n");
    printf("7. Busca Sequencial\n");
    printf("8. Busca Binária\n");
    printf("9. Executar todos os algoritmos 1000 vezes\n");
    printf("\n");

    // Solicita a entrada do usuário e armazena em 'opcao'
    printf("Digite a opção desejada: ");
    scanf("%d", &opcao);

    return opcao;
}


/*===========================================================================================================*/


// Função para executar a operação com base na opção escolhida
void program(int opcao) 
{            
    switch (opcao) 
    {
        case 0:
            printf("Saindo do programa...\n");
            break;


        case 1:
            printf("Vetor gerado com sucesso...\n");


            geraVetor(v);
            vetorGerado = true;

            for(int i = 0; i < TAM; i++)
                v1[i] = v[i];

            printf("Digite o tamanho do vetor que deseja visualizar: ");
            int n;
            scanf("%d", &n);
            imprimeVetor(v, n);
            break;


        case 2:
            int escolha;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }
            
            printf("\n");
            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }

            printf("\n");
            printf("Executando QuickSort com Pivô Aleatório...\n");
            quickSortAleatorio(copiav, 0, TAM - 1);
            exibirContagens("QuickSort - Pivô Aleatório");

            printf("\n");
            printf("Deseja imprimir o vetor ordenado? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                printf("\n");
                printf("Digite o tamanho do vetor que deseja visualizar: ");
                int n;
                scanf("%d", &n);
                imprimeVetor(copiav, n);
            }
            break;


        case 3:
            contagemComparacoes = 0;
            contagemTrocas = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }

            printf("\n");
            memcpy(copiav, v, TAM * sizeof(int));
            printf("Executando QuickSort com Mediana de Três...\n");
            quickSortMedianaDeTres(copiav, 0, TAM - 1);
            exibirContagens("QuickSort - Pivô Mediana de Três");

            printf("\n");
            printf("Deseja imprimir o vetor ordenado? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                printf("\n");
                printf("Digite o tamanho do vetor que deseja visualizar: ");
                int n;
                scanf("%d", &n);
                imprimeVetor(copiav, n);
            }
            break;


        case 4:
            contagemComparacoes = 0;
            contagemTrocas = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }

            printf("\n");
            memcpy(copiav, v, TAM * sizeof(int));
            printf("Executando ShellSort com Sequência de Knuth...\n");
            shellSortKnuth(copiav, TAM);
            exibirContagens("ShellSort - Sequência de Knuth");

            printf("\n");
            printf("Deseja imprimir o vetor ordenado? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                printf("\n");
                printf("Digite o tamanho do vetor que deseja visualizar: ");
                int n;
                scanf("%d", &n);
                imprimeVetor(copiav, n);
            }
            break;


        case 5:
            contagemComparacoes = 0;
            contagemTrocas = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }

            printf("\n");
            memcpy(copiav, v, TAM * sizeof(int));
            printf("Executando ShellSort com Sequência de Hibbard...\n");
            shellSortHibbard(copiav, TAM);
            exibirContagens("ShellSort - Sequência de Hibbard");

            printf("\n");
            printf("Deseja imprimir o vetor ordenado? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                printf("\n");
                printf("Digite o tamanho do vetor que deseja visualizar: ");
                int n;
                scanf("%d", &n);
                imprimeVetor(copiav, n);
            }

            break;


        case 6:
            contagemComparacoes = 0;
            contagemTrocas = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }

            printf("\n");
            memcpy(copiav, v, TAM * sizeof(int));
            printf("Executando SelectionSort...\n");
            selectionSort(copiav, TAM);
            exibirContagens("SelectionSort");

            printf("\n");
            printf("Deseja imprimir o vetor ordenado? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                printf("\n");
                printf("Digite o tamanho do vetor que deseja visualizar: ");
                int n;
                scanf("%d", &n);
                imprimeVetor(copiav, n);
            }

            break;


        case 7:
            contagemComparacoes = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v1);
                printf("\n");
                printf("Deseja visualizar o vetor gerado? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(v1, n);
                }
            }

            printf("\n");
            printf("Executando Busca Sequencial...\n");
            realizarBuscaSequencial(v1, TAM);
            break;


        case 8:
            contagemComparacoes = 0;

            if (!vetorGerado) 
            {
                printf("Vetor não gerado! Por favor, gere um vetor antes de executar o algoritmo.\n");
                break;
            }

            printf("Gerar Vetor? (1. Sim / 2. Não):\n");
            scanf("%d", &escolha);

            if (escolha == 1) 
            {
                geraVetor(v);
                quickSortMedianaDeTres(copiav, 0, TAM - 1);
                printf("\n");
                printf("Deseja visualizar o vetor gerado (Ordenado)? (1. Sim / 2. Não):\n");
                scanf("%d", &escolha);

                if (escolha == 1) 
                {
                    printf("\n");
                    printf("Digite o tamanho do vetor que deseja visualizar: ");
                    int n;
                    scanf("%d", &n);
                    imprimeVetor(copiav, n);
                }
            }
            else
                quickSortMedianaDeTres(copiav, 0, TAM - 1);

            printf("\n");
            memcpy(copiav, v, TAM * sizeof(int));
            printf("Executando Busca Binária...\n");
            realizarBuscaBinaria(copiav, TAM);
            break;


        case 9: 
        {
            const int numExecucoes = 1000;
            int comparacoesQuickSortAleatorio[numExecucoes];
            int comparacoesQuickSortMediana[numExecucoes];
            int comparacoesShellSortKnuth[numExecucoes];
            int comparacoesShellSortHibbard[numExecucoes];
            int comparacoesSelectionSort[numExecucoes];
            int comparacoesBuscaSequencial[numExecucoes];
            int comparacoesBuscaBinaria[numExecucoes];

            printf("\n");
            printf("Executando TODOS os algoritmos 1000 vezes...\n");

            // Execução e contagem para cada algoritmo
            for (int i = 0; i < numExecucoes; i++) 
            {
                int v[TAM];
                int v1[TAM];

                // QuickSort com Pivô Aleatório
                geraVetor(v);
                contagemComparacoes = 0;
                quickSortAleatorio(v, 0, TAM - 1);
                comparacoesQuickSortAleatorio[i] = contagemComparacoes;

                // QuickSort com Pivô Mediana de Três
                geraVetor(v);
                contagemComparacoes = 0;
                quickSortMedianaDeTres(v, 0, TAM - 1);
                comparacoesQuickSortMediana[i] = contagemComparacoes;

                // ShellSort com Sequência de Knuth
                geraVetor(v);
                contagemComparacoes = 0;
                shellSortKnuth(v, TAM);
                comparacoesShellSortKnuth[i] = contagemComparacoes;

                // ShellSort com Sequência de Hibbard
                geraVetor(v);
                contagemComparacoes = 0;
                shellSortHibbard(v, TAM);
                comparacoesShellSortHibbard[i] = contagemComparacoes;

                // SelectionSort
                geraVetor(v);
                contagemComparacoes = 0;
                selectionSort(v, TAM);
                comparacoesSelectionSort[i] = contagemComparacoes;

                // Busca Sequencial
                geraVetor(v1);  // Usa v1 para não alterar o vetor ordenado em busca binária
                contagemComparacoes = 0;
                BuscaSequencialAleat(v1, TAM, &contagemComparacoes);
                comparacoesBuscaSequencial[i] = contagemComparacoes;

                // Busca Binária
                contagemComparacoes = 0;
                BuscaBinariaAleat(v, TAM, &contagemComparacoes);
                comparacoesBuscaBinaria[i] = contagemComparacoes;
            }

            // Cálculo da média, desvio padrão e total de comparações para cada algoritmo
            double mediaQuickAleatorio = calcularMedia(comparacoesQuickSortAleatorio, numExecucoes);
            double desvioQuickAleatorio = calcularDesvioPadrao(comparacoesQuickSortAleatorio, numExecucoes, mediaQuickAleatorio);
            int totalQuickAleatorio = calcularTotalComparacoes(comparacoesQuickSortAleatorio, numExecucoes);

            double mediaQuickMediana = calcularMedia(comparacoesQuickSortMediana, numExecucoes);
            double desvioQuickMediana = calcularDesvioPadrao(comparacoesQuickSortMediana, numExecucoes, mediaQuickMediana);
            int totalQuickMediana = calcularTotalComparacoes(comparacoesQuickSortMediana, numExecucoes);

            double mediaShellKnuth = calcularMedia(comparacoesShellSortKnuth, numExecucoes);
            double desvioShellKnuth = calcularDesvioPadrao(comparacoesShellSortKnuth, numExecucoes, mediaShellKnuth);
            int totalShellKnuth = calcularTotalComparacoes(comparacoesShellSortKnuth, numExecucoes);

            double mediaShellHibbard = calcularMedia(comparacoesShellSortHibbard, numExecucoes);
            double desvioShellHibbard = calcularDesvioPadrao(comparacoesShellSortHibbard, numExecucoes, mediaShellHibbard);
            int totalShellHibbard = calcularTotalComparacoes(comparacoesShellSortHibbard, numExecucoes);

            double mediaSelection = calcularMedia(comparacoesSelectionSort, numExecucoes);
            double desvioSelection = calcularDesvioPadrao(comparacoesSelectionSort, numExecucoes, mediaSelection);
            int totalSelection = calcularTotalComparacoes(comparacoesSelectionSort, numExecucoes);

            double mediaBuscaSequencial = calcularMedia(comparacoesBuscaSequencial, numExecucoes);
            double desvioBuscaSequencial = calcularDesvioPadrao(comparacoesBuscaSequencial, numExecucoes, mediaBuscaSequencial);
            int totalBuscaSequencial = calcularTotalComparacoes(comparacoesBuscaSequencial, numExecucoes);

            double mediaBuscaBinaria = calcularMedia(comparacoesBuscaBinaria, numExecucoes);
            double desvioBuscaBinaria = calcularDesvioPadrao(comparacoesBuscaBinaria, numExecucoes, mediaBuscaBinaria);
            int totalBuscaBinaria = calcularTotalComparacoes(comparacoesBuscaBinaria, numExecucoes);


            // Exibição dos resultados
            printf("\n");
            printf("Resultados das Comparações após 1000 execuções:\n");

            printf("\n");
            printf("QuickSort (Pivô Aleatório): Média = %.2f\n", mediaQuickAleatorio);
            printf("QuickSort (Pivô Aleatório): Desvio Padrão = %.2f\n", desvioQuickAleatorio);
            printf("QuickSort (Pivô Aleatório): Total = %d\n", totalQuickAleatorio);
            printf("____________________________________________________________________________\n");



            printf("\n");
            printf("QuickSort (Pivô Mediana de Três): Média = %.2f, \n", mediaQuickMediana);
            printf("QuickSort (Pivô Mediana de Três): Desvio Padrão = %.2f\n", desvioQuickMediana);
            printf("QuickSort (Pivô Mediana de Três): Total = %d\n", totalQuickMediana);
            printf("____________________________________________________________________________\n");



            printf("\n");
            printf("ShellSort (Sequência de Knuth): Média = %.2f\n", mediaShellKnuth);
            printf("ShellSort (Sequência de Knuth): Desvio Padrão = %.2f\n", desvioShellKnuth);
            printf("ShellSort (Sequência de Knuth): Total = %d\n", totalShellKnuth);
            printf("____________________________________________________________________________\n");



            printf("\n");
            printf("ShellSort (Sequência de Hibbard): Média = %.2f\n", mediaShellHibbard);
            printf("ShellSort (Sequência de Hibbard): Desvio Padrão = %.2f\n", desvioShellHibbard);
            printf("ShellSort (Sequência de Hibbard): Total = %d\n", totalShellHibbard);
            printf("____________________________________________________________________________\n");
            
            
            
            printf("\n");
            printf("SelectionSort: Média = %.2f\n", mediaSelection);
            printf("SelectionSort: Desvio Padrão = %.2f\n", desvioSelection);
            printf("SelectionSort: Total = %d\n", totalSelection);
            printf("____________________________________________________________________________\n");
            


            printf("\n");
            printf("Busca Sequencial: Média = %.2f\n", mediaBuscaSequencial);
            printf("Busca Sequencial: Desvio Padrão = %.2f\n", desvioBuscaSequencial);
            printf("Busca Sequencial: Total = %d\n", totalBuscaSequencial);
            printf("____________________________________________________________________________\n");
            

            
            printf("\n");
            printf("Busca Binária: Média = %.2f\n", mediaBuscaBinaria);
            printf("Busca Binária: Desvio Padrão = %.2f\n",desvioBuscaBinaria);
            printf("Busca Binária: Total = %d\n", totalBuscaBinaria);
            printf("____________________________________________________________________________\n");


            break;
        }

        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
    }
}


/*===========================================================================================================*/


//                                          TROCA DE ELEMENTOS

// Troca o conteúdo de duas variáveis
void trocar(int *a, int *b) 
{
    int temp = *a;
    *a = *b;
    *b = temp;
    contagemTrocas++;
}


/*==========================================================================================================================*/


//                                              EXIBE DADOS

void exibirContagens(char *metodo) 
{
    printf("\n[%s] Contagem de trocas: %d\n", metodo, contagemTrocas);
    printf("[%s] Contagem de comparações: %d\n", metodo, contagemComparacoes);
}


/*================================================ [QUICK SORT] ===========================================================*/


//                                UTILIZANDO UM ELEMENTO ALEATÓRIO DO VETOR COMO PIVÔ


// Função que particiona o vetor de forma que os elementos menores que o pivô fiquem à esquerda e os maiores à direita do pivô.
// O pivô é escolhido aleatoriamente.
int particionarAleatorio(int vetor[], int inicio, int fim) 
{
    // Escolhe um índice aleatório entre inicio e fim
    int indicePivoAleatorio = inicio + rand() % (fim - inicio + 1);
    
    // Troca o elemento aleatório com o Aleatório elemento para usá-lo como pivô
    trocar(&vetor[indicePivoAleatorio], &vetor[fim]);

    int pivo = vetor[fim];  // Define o pivô como o elemento agora na posição 'fim'
    int indiceMenor = inicio - 1;  // Inicializa o índice do menor elemento

    // Percorre o vetor do início até o penAleatório elemento (fim - 1), comparando cada elemento com o pivô
    for (int i = inicio; i < fim; i++) 
    {   
        contagemComparacoes++;  // Conta cada comparação feita entre o elemento e o pivô
        if (vetor[i] < pivo) {  // Se o elemento é menor que o pivô, ele deve ser movido para a esquerda
            indiceMenor++;  // Incrementa o índice do menor elemento
            trocar(&vetor[indiceMenor], &vetor[i]);  // Troca os elementos de posição
        }
    }

    // Coloca o pivô na posição correta, entre os elementos menores e maiores
    trocar(&vetor[indiceMenor + 1], &vetor[fim]);
    
    // Retorna o índice da posição final do pivô
    return indiceMenor + 1;
}


// Função que implementa o algoritmo de ordenação QuickSort utilizando um pivô aleatório
void quickSortAleatorio(int vetor[], int inicio, int fim) 
{
    // A recursão só continua se houver mais de um elemento a ser ordenado
    if (inicio < fim) {
        // Particiona o vetor e encontra o índice do pivô
        int indicePivo = particionarAleatorio(vetor, inicio, fim);
        
        // Ordena recursivamente os elementos à esquerda do pivô
        quickSortAleatorio(vetor, inicio, indicePivo - 1);
        
        // Ordena recursivamente os elementos à direita do pivô
        quickSortAleatorio(vetor, indicePivo + 1, fim);
    }
}


/*===========================================================================================================*/


//                              UTILIZANDO A MEDIANA DE TRÊS ELEMENTOS DO VETOR


// Função que escolhe o pivô como a mediana de três elementos: o primeiro, o meio e o Aleatório elemento do vetor.
int medianaDeTres(int vetor[], int inicio, int fim) 
{
    // Calcula o índice do meio do vetor
    int meio = (inicio + fim) / 2;

    // Ordena os elementos nas posições início, meio e fim para garantir que o pivô será a mediana
    // Se o primeiro elemento for maior que o do meio, troca-os
    if (vetor[inicio] > vetor[meio]) trocar(&vetor[inicio], &vetor[meio]);
    // Se o primeiro elemento for maior que o Aleatório, troca-os
    if (vetor[inicio] > vetor[fim]) trocar(&vetor[inicio], &vetor[fim]);
    // Se o meio for maior que o Aleatório, troca-os
    if (vetor[meio] > vetor[fim]) trocar(&vetor[meio], &vetor[fim]);

    // Coloca o valor da mediana (elemento do meio) na posição final do vetor
    // Isso facilita a escolha da mediana como pivô para a partição
    trocar(&vetor[meio], &vetor[fim]);

    // Retorna o valor do pivô (mediana)
    return vetor[fim];
}


// Função que particiona o vetor com base no pivô escolhido pela mediana de três
// A partição organiza os elementos menores que o pivô à esquerda e os maiores à direita
int particionarMedianaDeTres(int vetor[], int inicio, int fim) 
{
    // Obtém o pivô, que é a mediana de três
    int pivo = medianaDeTres(vetor, inicio, fim);  

    // Inicializa o índice do menor elemento à esquerda do início do vetor
    int indiceMenor = inicio - 1;

    // Loop para percorrer o vetor e organizar os elementos ao redor do pivô
    for (int i = inicio; i < fim; i++) 
    {
        contagemComparacoes++;  // Conta cada comparação entre o elemento e o pivô
        if (vetor[i] < pivo)  // Se o elemento é menor que o pivô
        {
            indiceMenor++;  // Incrementa o índice do menor elemento
            trocar(&vetor[indiceMenor], &vetor[i]);  // Troca o elemento para a esquerda
        }
    }

    // Coloca o pivô na posição correta (onde todos os elementos à esquerda são menores e à direita são maiores)
    trocar(&vetor[indiceMenor + 1], &vetor[fim]);

    // Retorna o índice da posição final do pivô, dividindo o vetor em duas partes
    return indiceMenor + 1;
}


// Função que implementa o algoritmo de ordenação QuickSort utilizando a mediana de três como pivô
void quickSortMedianaDeTres(int vetor[], int inicio, int fim) 
{
    // A recursão só continua se houver mais de um elemento a ser ordenado
    if (inicio < fim) {
        // Particiona o vetor e encontra o índice do pivô
        int indicePivo = particionarMedianaDeTres(vetor, inicio, fim);
        
        // Ordena recursivamente os elementos à esquerda do pivô
        quickSortMedianaDeTres(vetor, inicio, indicePivo - 1);
        
        // Ordena recursivamente os elementos à direita do pivô
        quickSortMedianaDeTres(vetor, indicePivo + 1, fim);
    }
}


/*================================================ [SHELL SORT] ===========================================================*/


//                                      UTILIZANDO A SEQUÊNCIA DE KNUTH


// Função que ordena o vetor utilizando o método ShellSort com a sequência de Knuth
void shellSortKnuth(int vetor[], int n) 
{
    // Inicializa o gap como 1
    int gap = 1;
    
    // Calcula o maior gap de Knuth que seja menor que o tamanho do vetor
    // A sequência de Knuth é gerada pela fórmula: gap = 3 * gap + 1
    // O loop continua até que o gap seja maior que o tamanho do vetor dividido por 3
    while (gap < n / 3) {
        gap = 3 * gap + 1;
    }

    // Enquanto o gap for maior que zero, executa o algoritmo de ordenação
    // A cada iteração, o gap diminui de acordo com a fórmula: gap = (gap - 1) / 3
    for (; gap > 0; gap = (gap - 1) / 3) {
        
        // Ordena os elementos com o gap atual
        // O loop começa com o índice igual ao gap e percorre o vetor
        for (int i = gap; i < n; i++) {
            int temp = vetor[i];  // Armazena o valor do elemento atual
            int j;
            
            // Compara o elemento com o anterior que está no índice i - gap
            // Se o elemento à esquerda (vetor[j - gap]) for maior que o elemento atual, ele é movido para a posição à direita
            for (j = i; j >= gap; j -= gap) {
                contagemComparacoes++;  // Incrementa a contagem de comparações
                if (vetor[j - gap] > temp) {
                    vetor[j] = vetor[j - gap];  // Move o valor para a direita
                } else {
                    break;  // Se não for maior, sai do loop
                }
            }
            
            // Se houve movimentação, coloca o elemento na posição correta
            // Isso ocorre se a comparação indicou que o valor atual deveria ser inserido em uma posição anterior
            if (j != i) {  // Verifica se houve alguma troca
                vetor[j] = temp;
                contagemTrocas++;  // Incrementa a contagem de trocas
            }
        }
    }
}


/*===========================================================================================================*/


//                                      UTILIZANDO A SEQUÊNCIA DE HIBBARD


// Função que ordena o vetor utilizando o método ShellSort com a sequência de Hibbard
void shellSortHibbard(int vetor[], int n) 
{
    int k = 1;
    
    // Calcula o maior gap de Hibbard que seja menor que o tamanho do vetor
    // A sequência de Hibbard é gerada pela fórmula: gap = (2^k - 1), onde k é um inteiro positivo
    // O loop encontra o maior k tal que (2^k - 1) seja menor que o tamanho do vetor
    while ((1 << k) - 1 < n) {
        k++;  // Incrementa k até que o gap gerado seja maior ou igual ao tamanho do vetor
    }
    k--;  // Ajusta k para garantir que o gap final seja válido

    // Loop principal: percorre os gaps da sequência de Hibbard
    // A cada iteração, o gap é calculado como (2^k - 1) e diminui após cada passagem
    for (int gap = (1 << k) - 1; gap > 0; k--, gap = (1 << k) - 1) {
        
        // Ordena os elementos com o gap atual
        // A cada gap, o vetor é dividido em subgrupos e ordenado como uma variação do InsertionSort
        for (int i = gap; i < n; i++) {
            int temp = vetor[i];  // Armazena o valor atual do vetor para comparação posterior
            int j;

            // Compara o elemento com o anterior a uma distância igual ao gap
            // Se o elemento à esquerda for maior, ele é movido para a direita
            for (j = i; j >= gap; j -= gap) {
                contagemComparacoes++;  // Incrementa a contagem de comparações
                if (vetor[j - gap] > temp) {
                    vetor[j] = vetor[j - gap];  // Move o valor maior para a direita
                } else {
                    break;  // Se o valor à esquerda não for maior, sai do loop
                }
            }
            
            // Coloca o valor armazenado na posição correta
            vetor[j] = temp;
            contagemTrocas++;  // Incrementa a contagem de trocas, pois houve uma movimentação
        }
    }
}



/*===========================================================================================================*/


//                                      UTILIZANDO O SELECTION SORT


// Função que ordena o vetor utilizando o método Selection Sort
void selectionSort(int vetor[], int n) {
    // Loop externo: percorre todos os elementos do vetor
    for (int i = 0; i < n - 1; i++) {
        int indiceMenor = i;  // Assume que o primeiro elemento não ordenado é o menor

        // Loop interno: percorre o restante do vetor para encontrar o menor elemento
        for (int j = i + 1; j < n; j++) {
            contagemComparacoes++;  // Incrementa a contagem de comparações

            // Se encontrar um elemento menor, atualiza o índice do menor elemento
            if (vetor[j] < vetor[indiceMenor]) {
                indiceMenor = j;
            }
        }

        // Se o índice do menor elemento não for o mesmo que o índice i, troca os elementos
        // Isso significa que o menor elemento foi encontrado no restante do vetor
        if (indiceMenor != i) {
            trocar(&vetor[i], &vetor[indiceMenor]);  // Chama a função de troca para colocar o menor elemento na posição correta
        }
    }
}


/*====================================== [ALGORITMOS DE PESQUISA] =================================================*/


//                                    ALGORITMO DE BUSCA SEQUENCIAL


// Função para buscar um elemento sequencialmente no vetor e contar as comparações
int buscaSequencial(int vetor[], int tamanho, int elemento, int *contagemComparacoes) 
{
    *contagemComparacoes = 0; // Zera a contagem no início da busca

    for (int i = 0; i < tamanho; i++) {
        (*contagemComparacoes)++; // Incrementa a contagem a cada comparação
        if (vetor[i] == elemento) {
            return i; // Retorna o índice onde o elemento foi encontrado
        }
    }
    return -1; // Retorna -1 se o elemento não for encontrado
}



// Escolhe entre um número digitado pelo usuário ou gerado aleatoriamente para busca
void realizarBuscaSequencial(int vetor[], int tamanho) 
{
    int opcao, elemento, posicao;
    int comparacoes;

    // Pergunta ao usuário se ele quer inserir um valor ou gerar um número aleatório
    do {
        printf("Escolha uma opção:\n");
        printf("1. Digitar um número para buscar\n");
        printf("2. Gerar um número aleatório para buscar\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao != 1 && opcao != 2) {
            printf("Opção inválida! Por favor, escolha 1 ou 2.\n");
        }
    } while (opcao != 1 && opcao != 2);

    if (opcao == 1) {
        printf("Digite o número a ser buscado: ");
        scanf("%d", &elemento);
    } else {
        elemento = rand() % (MAX_VAL + 1); // Gera número aleatório entre 0 e MAX_VAL
        printf("Número gerado aleatoriamente para busca: %d\n", elemento);
    }

    // Realiza a busca sequencial no vetor original
    posicao = buscaSequencial(vetor, tamanho, elemento, &comparacoes);

    // Exibe o resultado da busca
    if (posicao != -1) {
        printf("Elemento %d encontrado na posição %d após %d comparações.\n", elemento, posicao, comparacoes);
    } else {
        printf("Elemento %d não encontrado no vetor após %d comparações.\n", elemento, comparacoes);
    }
}



// Função para realizar a busca sequencial com número aleatório
void BuscaSequencialAleat(int vetor[], int tamanho, int *comparacoes) 
{
    int elemento = rand() % (MAX_VAL + 1); // Gera número aleatório entre 0 e MAX_VAL
    buscaSequencial(vetor, tamanho, elemento, comparacoes);
}


/*===========================================================================================================*/


//                                       ALGORITMO DE BUSCA BINÁRIA


// Função de busca binária no vetor ordenado
int buscaBinaria(int vetor[], int tamanho, int elemento, int *contagemComparacoes) {
    int inicio = 0, fim = tamanho - 1; // Define os limites iniciais do vetor (início e fim)
    *contagemComparacoes = 0; // Zera a contagem de comparações no início da busca

    // Loop principal da busca binária que continua enquanto o intervalo for válido
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2; // Calcula o índice do elemento do meio
        (*contagemComparacoes)++; // Incrementa a contagem de comparações

        // Verifica se o elemento do meio é o elemento procurado
        if (vetor[meio] == elemento) {
            return meio;  // Retorna o índice onde o elemento foi encontrado
        }
        else if (vetor[meio] < elemento) {
            inicio = meio + 1; // Ajusta o início para buscar na metade direita
        }
        else {
            fim = meio - 1; // Ajusta o fim para buscar na metade esquerda
        }
    }
    return -1;  // Retorna -1 se o elemento não for encontrado no vetor
}



// Função para permitir consulta de elemento no vetor, com entrada ou número aleatório
void realizarBuscaBinaria(int vetor[], int tamanho) {
    int elemento, contagemComparacoes = 0, opcao;

    // Loop para garantir que o usuário escolha uma opção válida
    do {
        printf("Escolha uma opção para a busca binária:\n");
        printf("1 - Digitar o elemento a ser buscado\n");
        printf("2 - Gerar aleatoriamente o elemento a ser buscado\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        // Exibe mensagem de erro se a opção for inválida
        if (opcao != 1 && opcao != 2) {
            printf("Opção inválida! Por favor, escolha 1 ou 2.\n");
        }
    } while (opcao != 1 && opcao != 2); // Repete até que o usuário forneça uma opção válida

    // Define o valor do elemento a ser buscado
    if (opcao == 1) {
        printf("Digite o elemento a ser buscado: ");
        scanf("%d", &elemento); // Lê o número digitado pelo usuário
    } else {
        elemento = rand() % (MAX_VAL + 1); // Gera um número aleatório entre 0 e MAX_VAL
        printf("Elemento gerado aleatoriamente: %d\n", elemento); // Exibe o número gerado
    }

    // Realiza a busca binária no vetor ordenado
    int posicao = buscaBinaria(vetor, tamanho, elemento, &contagemComparacoes);

    // Exibe o resultado da busca
    if (posicao != -1) {
        printf("Elemento encontrado na posição: %d\n", posicao); // Se encontrado, exibe a posição
    } else {
        printf("Elemento não encontrado no vetor.\n"); // Caso contrário, indica que não foi encontrado
    }
    printf("Número de comparações realizadas: %d\n", contagemComparacoes); // Exibe o total de comparações
}



// Função para realizar a busca binária com número aleatório
void BuscaBinariaAleat(int vetor[], int tamanho, int *comparacoes) {
    int elemento = rand() % (MAX_VAL + 1); // Gera um número aleatório entre 0 e MAX_VAL
    buscaBinaria(vetor, tamanho, elemento, comparacoes); // Realiza a busca binária com o número gerado
}


/*===========================================================================================================*/
