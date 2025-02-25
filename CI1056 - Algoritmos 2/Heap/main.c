#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heap.h"







int main ()
{
    struct heap_t v;



    // Inicializa o heap
    InicHeap(&v);


    srand(time(NULL));
    for (int i = 0; i < 10; i++) 
    {
        int aleatorio = rand() % 100;

        InsertHeap(&v, aleatorio);
    }

    // Imprime o heap
    printf("Heap após inserções:\n");
    PrintHeap(&v);


    // Remove o maior elemento (raiz)
    printf("Removendo a raiz do heap...\n");
    RemoveHeap(&v);
    PrintHeap(&v);



    // Ordena o heap
    printf("Heap ordenado:\n");
    HeapSort(&v, v.tam);

    PrintHeap(&v);




    return 0;
}