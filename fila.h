#ifndef FILA_H
#define FILA_H

typedef struct {
    int max;
    int inicio;
    int fim;
    int n;
    int *itens;
} t_queue;

t_queue* create_queue(int max);
int is_empty(t_queue* fila);
int is_full(t_queue* fila);
int in(t_queue* fila, int elem);
int out(t_queue* fila, int *elem);
void clear(t_queue* fila);
int size(t_queue* fila);

#endif