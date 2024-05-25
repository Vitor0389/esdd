#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
/* Sim, a estratégia iterativa do algoritmo Quicksort é uma abordagem eficiente
 para limitar o tamanho da pilha de execução e evitar problemas de estouro de pilha.
 Ao usar a estratégia iterativa, podemos verificar o tamanho das partições antes de 
 adicioná-las à pilha. Isso nos permite controlar melhor o uso da memória e evitar 
 estouros de pilha, especialmente em conjuntos de dados grandes ou desbalanceados. 
 Como resultado dessas estratégias, a complexidade de espaço do algoritmo Quicksort 
 iterativo é da ordem de O(log(n))*/

 // Nós utilizamos essa estratégia no nosso código.

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] < pivot)
        {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return (i + 1);
}

void iterative_quicksort(int array[], int start, int end)
{
    t_stack *stack = create_stack(end - start + 1);

    push(stack, start);
    push(stack, end);

    while (!is_empty(stack))
    {
        pop(stack, &end);
        pop(stack, &start);

        int pivot_index = partition(array, start, end);

        if (pivot_index - 1 > start && end - pivot_index > pivot_index - start)
        {
            push(stack, start);
            push(stack, pivot_index - 1);
            if (pivot_index + 1 < end)
            {
                push(stack, pivot_index + 1);
                push(stack, end);
            }
        }
        else
        {
            if (pivot_index + 1 < end)
            {
                push(stack, pivot_index + 1);
                push(stack, end);
            }
            if (pivot_index - 1 > start)
            {
                push(stack, start);
                push(stack, pivot_index - 1);
            }
        }
    }

    destroy_stack(stack);
}

void print_array(int array[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s num_elements element1 element2 ... elementN\n", argv[0]);
        return 1;
    }

    int num_elements = atoi(argv[1]);
    if (argc != num_elements + 2)
    {
        printf("Number of elements does not match the provided elements.\n");
        return 1;
    }

    int *array = (int *)malloc(num_elements * sizeof(int));
    for (int i = 0; i < num_elements; i++)
    {
        array[i] = atoi(argv[i + 2]);
    }

    iterative_quicksort(array, 0, num_elements - 1);

    printf("Sorted array: \n");
    print_array(array, num_elements);

    free(array);
    return 0;
}