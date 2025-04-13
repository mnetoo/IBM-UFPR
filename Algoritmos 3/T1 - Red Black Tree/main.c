#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "redblack.h"




int main() 
{
    struct RBTree *tree = create_tree();
    char operacao;
    int valor;

    // Lê da entrada padrão
    while (scanf(" %c %d", &operacao, &valor) == 2) {
        if (operacao == 'i') {
            insert_BST(tree, valor);
        } else if (operacao == 'r') {
            delete(tree, valor);
        } else {
            fprintf(stderr, "Operação inválida: %c\n", operacao);
        }
    }

    // Imprime na saída padrão
    print_formatted(tree->root, 0);

    free_tree(tree->root);
    free(tree);

    return 0;
}