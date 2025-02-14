#ifndef STACK_H
#define STACK_H

typedef int t_elem;

typedef struct
{
    int max;
    int top_index;
    t_elem *items;
} t_stack;

t_stack* create_stack(int n);
void destroy_stack(t_stack *pilha);
int is_full(t_stack *pilha);
int is_empty(t_stack *pilha);
int push(t_stack *pilha, t_elem x);
int pop(t_stack *pilha, t_elem *x);
int top(t_stack *pilha, t_elem *x);
void clear(t_stack *pilha);
void print(t_stack *pilha);

#endif // STACK_H