#include <stdio.h>    // Biblioteca para funções de entrada e saída (ex: printf, scanf)
#include <stdlib.h>   // Biblioteca para alocação de memória, conversões e outras funções utilitárias
#include <string.h>   // Biblioteca para manipulação de strings
#include <time.h>     // Biblioteca para manipulação de data e hora (ex: função time)
#include <stdbool.h>  // Biblioteca para tipos booleanos (ex: true, false)
#include "funções.h"  // Inclui o cabeçalho com as funções personalizadas do programa


// Variáveis globais para contagem de trocas e comparações realizadas nos algoritmos de ordenação
int contagemTrocas = 0;      
int contagemComparacoes = 0;


int main() 
{
    int opcao = 0;            // Variável para armazenar a opção escolhida pelo usuário no menu
    srand(time(NULL));         // Inicializa o gerador de números aleatórios com base no tempo atual

    // Loop principal do programa, que exibe o menu e executa a opção escolhida
    do {
        opcao = menu();        // Chama a função 'menu' para exibir as opções e obter a escolha do usuário
        program(opcao);        // Chama a função 'program' para executar a ação correspondente à opção
    } while (opcao != 0);      // O loop continua enquanto a opção não for 0 (sair do programa)

    return 0; // Retorna 0 para indicar que o programa foi finalizado com sucesso
}