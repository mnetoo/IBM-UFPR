#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define MAX_WORD_LEN 100  // Tamanho máximo de uma palavra
#define MAX_WORDS 10000   // Número máximo de palavras únicas armazenadas



// Estrutura para armazenar uma palavra e sua contagem
typedef struct 
{
    char word[MAX_WORD_LEN];
    int count;
} WordFreq;

// Função para procurar uma palavra no vetor de palavras armazenadas
int find_word(WordFreq words[], int size, const char *word) 
{
    for (int i = 0; i < size; i++) {
        if (strcmp(words[i].word, word) == 0) 
        {
            return i; // Retorna o índice da palavra encontrada
        }
    }
    return -1; // Retorna -1 se a palavra não foi encontrada
}

// Função de comparação para ordenar as palavras pela frequência (decrescente)
int compare(const void *a, const void *b) 
{
    return ((WordFreq *)b)->count - ((WordFreq *)a)->count;
}

int main() 
{
    char filename[256];
    printf("Digite o nome do arquivo: ");
    scanf("%255s", filename);
    
    // Abre o arquivo para leitura
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }
    
    WordFreq words[MAX_WORDS]; // Vetor para armazenar palavras e suas frequências
    int word_count = 0; // Contador de palavras únicas armazenadas
    char word[MAX_WORD_LEN];
    
    // Lê palavras do arquivo uma por uma
    while (fscanf(file, "%99s", word) == 1) 
    {
        // Converte todas as letras da palavra para minúsculas
        int len = strlen(word);
        for (int i = 0; i < len; i++)
        {
            word[i] = tolower(word[i]);
        }
        
        // Verifica se a palavra já está armazenada
        int index = find_word(words, word_count, word);
        if (index != -1) 
        {
            words[index].count++; // Incrementa a contagem se a palavra já existir
        } 
        else if (word_count < MAX_WORDS) 
        {
            strcpy(words[word_count].word, word); // Armazena a nova palavra
            words[word_count].count = 1; // Inicia a contagem
            word_count++;
        }
    }
    fclose(file); // Fecha o arquivo após a leitura
    
    // Verifica se nenhuma palavra foi encontrada
    if (word_count == 0) 
    {
        printf("Nenhuma palavra encontrada no arquivo.\n");
        return 0;
    }
    
    // Ordena as palavras pela frequência (decrescente)
    qsort(words, word_count, sizeof(WordFreq), compare);
    
    // Exibe as palavras ordenadas por frequência
    printf("Palavras ordenadas por frequência:\n");
    for (int i = 0; i < word_count; i++) 
    {
        printf("%s: %d\n", words[i].word, words[i].count);
    }
    
    return 0;
}