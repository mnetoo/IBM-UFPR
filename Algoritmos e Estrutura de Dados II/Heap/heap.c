#include <stdio.h>
#include <stdlib.h>
#include "heap.h"



void trocar(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}





void InicHeap (struct heap_t *heap)
{
    heap->tam = 0;
}


void Heapify(int *vetor, int tam, int i)
{
    int maior = i;
    int esquerda = 2*i;
    int direita = 2*i + 1;

    if(esquerda < tam && vetor[esquerda] > vetor[maior])
        maior = esquerda;

    if(direita < tam && vetor[direita] > vetor[maior])
        maior = direita;

    if(maior != i)
    {
        trocar(&vetor[i], &vetor[maior]);
        Heapify(vetor, tam, maior);
    }
}



void InsertHeap (struct heap_t *heap, int valor)
{
    heap->data[heap->tam] = valor;
    int i = heap->tam;
    heap->tam++;

    while(i > 0  && heap->data[i] > heap->data[i/2])
    {   
        trocar(&heap->data[i], &heap->data[i/2]);
        i = i/2;        
    }
}


void RemoveHeap (struct heap_t *heap)
{
    heap->data[0] = heap->data[heap->tam-1];
    heap->tam--;
    Heapify(heap->data, heap->tam, 0);
}


void HeapSort(int *vetor, int tam)
{
    for(int i = tam/2 - 1; i >= 0; i--)
        Heapify(vetor, tam, i);

    for(int i = tam - 1; i > 0; i--)
    {
        trocar(&vetor[0], &vetor[i]);
        Heapify(vetor, i, 0);
    }
}


void PrintHeap (struct heap_t *heap)
{
    for(int i = 0; i < heap->tam; i++)
        printf("%d ", heap->data[i]);
    printf("\n");
}
