#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main() 
{
    char linha[MAX_LINE_LENGTH];
    char *token;
    int coluna = 1;

    printf("Digite uma linha no formato CSV: ");
    fgets(linha, sizeof(linha), stdin);

    // Remove a quebra de linha no final, se existir
    linha[strcspn(linha, "\n")] = '\0';

    printf("\nColunas encontradas:\n");

    // Divide a linha usando vírgula como delimitador
    token = strtok(linha, ",");
    while (token != NULL) 
    {
        printf("%d: %s\n", coluna++, token);
        token = strtok(NULL, ",");
    }

    return 0;
}