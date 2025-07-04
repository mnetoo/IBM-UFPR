

#include <stdio.h>


struct heap_t 
{
    vetor[TAM];
    int tam;
};


void InicHeap (struct heap_t *heap);

void Heapify(int *vetor, int tam, int i);

void InsertHeap (struct heap_t *heap, int valor);

void RemoveHeap (struct heap_t *heap);

void HeapSort (int *vetor, int tam);

void PrintHeap (struct heap_t *heap);
