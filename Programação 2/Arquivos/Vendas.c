#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINHA 100
#define MAX_NOME 50


int main() 
{
    FILE *arquivo = fopen("vendas.txt", "r");
    if (arquivo == NULL) 
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char linha[MAX_LINHA];
    char nome[MAX_NOME], produto_mais_vendido[MAX_NOME], produto_maior_receita[MAX_NOME];
    float valor, receita, maior_receita = 0, faturamento_total = 0;
    int quantidade, maior_quantidade = 0;

    while (fgets(linha, sizeof(linha), arquivo)) 
    {
        // Substitui o '\n' por '\0' (evita problemas na leitura da string)
        linha[strcspn(linha, "\n")] = '\0';

        // Extrai os valores da linha
        sscanf(linha, "%[^|]|%f|%d", nome, &valor, &quantidade);

        // Calcula a receita do produto
        receita = valor * quantidade;

        // Soma ao faturamento total
        faturamento_total += receita;

        // Verifica o produto mais vendido
        if (quantidade > maior_quantidade) 
        {
            maior_quantidade = quantidade;
            strcpy(produto_mais_vendido, nome);
        }

        // Verifica o produto com maior receita
        if (receita > maior_receita) 
        {
            maior_receita = receita;
            strcpy(produto_maior_receita, nome);
        }
    }

    fclose(arquivo);

    // Exibição dos resultados
    printf("Faturamento total: R$ %.2f\n", faturamento_total);
    printf("Produto mais vendido: %s (%d unidades)\n", produto_mais_vendido, maior_quantidade);
    printf("Produto com maior receita: %s (R$ %.2f)\n", produto_maior_receita, maior_receita);

    return 0;
}