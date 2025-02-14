#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

t_queue* create_queue(int max) {
    t_queue *fila = (t_queue*)malloc(sizeof(t_queue));
    fila->max = max;
    fila->inicio = 0;
    fila->fim = 0;
    fila->n = 0;
    fila->itens = (int*)malloc(sizeof(int) * max);
    return fila;
}

int is_empty(t_queue* fila) {
    return fila->n == 0;
}

int is_full(t_queue* fila) {
    return fila->n == fila->max;
}

int in(t_queue* fila, int elem) {
    if (is_full(fila)) return 0;
    fila->itens[fila->fim] = elem;
    fila->fim = (fila->fim + 1) % fila->max;
    fila->n++;
    return 1;
}

int out(t_queue* fila, int *elem) {
    if (is_empty(fila)) return 0;
    *elem = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->max;
    fila->n--;
    return 1;
}

void clear(t_queue* fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->n = 0;
}

int size(t_queue* fila) {
    return fila->n;
}
