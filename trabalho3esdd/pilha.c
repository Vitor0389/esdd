#include <stdio.h>
#include <stdlib.h>
typedef int t_elem;


typedef struct
{
    int max;
    int top_index;
    t_elem *items;
} t_stack;


t_stack* create_stack(int n){
    t_stack *pilha = (t_stack*)calloc(1, sizeof(t_stack));
    pilha->max = n;
    pilha->top_index = -1;
    pilha->items = (t_elem*)calloc(n, sizeof(t_elem));
    return pilha;
}

void destroy_stack(t_stack *pilha){
    free(pilha ->items);
    free(pilha);
}

int is_full(t_stack *pilha)  {return pilha ->top_index + 1 == pilha->max ? 1:0;} 


int is_empty(t_stack *pilha)  {return pilha ->top_index == -1 ? 1:0; }

int push(t_stack *pilha, t_elem x){
    if(is_full(pilha)) return 0;

    pilha->top_index ++;
    pilha->items[pilha->top_index] = x;

    return 1;
}

int pop(t_stack *pilha, t_elem *x){
    if(is_empty(pilha)) return 0;

    *x = pilha ->items[pilha->top_index];
    pilha->top_index --;


    return 1;
}

int top(t_stack *pilha, t_elem *x){
    if(is_empty(pilha)) return 0;

    *x = pilha->items[pilha->top_index];

    return 1;
}

void clear(t_stack *pilha){
    pilha ->top_index = -1;
}

void print(t_stack *pilha){
    if(is_empty(pilha)) printf("PILHA VAZIA!");

    for(int i = 0; i < pilha -> top_index; i++){
        printf("%d", pilha-> items[i]);
    }
}