#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

#define MAX 100
#define MAX_NAME 50

typedef struct {
    char nome[MAX_NAME];
    char tipo; 
} Cliente;

void process_command(char comando, char* nome, t_queue *filaGeral, t_queue *filaPrioridade, Cliente *clientes, int *indiceCliente, int *contadorPrioridade) {
    if (comando == 'g' || comando == 'p') {
        clientes[*indiceCliente].tipo = comando;
        strcpy(clientes[*indiceCliente].nome, nome);
        if (comando == 'g') {
            in(filaGeral, *indiceCliente);
        } else {
            in(filaPrioridade, *indiceCliente);
        }
        (*indiceCliente)++;
    } else if (comando == 's') {
        int clienteIndice;
        if (!is_empty(filaPrioridade) && (*contadorPrioridade < 3 || is_empty(filaGeral))) {
            out(filaPrioridade, &clienteIndice);
            (*contadorPrioridade)++;
        } else if (!is_empty(filaGeral)) {
            out(filaGeral, &clienteIndice);
            *contadorPrioridade = 0;
        } else {
            return; 
        }
        printf("%s\n", clientes[clienteIndice].nome);
    }
}

void print_remaining_clients(t_queue *filaGeral, t_queue *filaPrioridade, Cliente *clientes) {
    int clienteIndice;
    while (!is_empty(filaPrioridade)) {
        out(filaPrioridade, &clienteIndice);
        printf("%s\n", clientes[clienteIndice].nome);
    }
    while (!is_empty(filaGeral)) {
        out(filaGeral, &clienteIndice);
        printf("%s\n", clientes[clienteIndice].nome);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s [commands]\n", argv[0]);
        return 1;
    }

    t_queue *filaGeral = create_queue(MAX);
    t_queue *filaPrioridade = create_queue(MAX);

    Cliente clientes[MAX];
    int indiceCliente = 0;
    int contadorPrioridade = 0;

    for (int i = 1; i < argc; i++) {
        char comando = argv[i][0];
        char nome[MAX_NAME] = {0};

        if (comando == 'g' || comando == 'p') {
            if (i + 1 < argc) {
                strcpy(nome, argv[++i]);
            } else {
                printf("Nome do cliente não fornecido para comando %c\n", comando);
                continue;
            }
        }

        process_command(comando, nome, filaGeral, filaPrioridade, clientes, &indiceCliente, &contadorPrioridade);

        if (comando == 'f') {
            print_remaining_clients(filaGeral, filaPrioridade, clientes);
            break;
        }
    }

    free(filaGeral->itens);
    free(filaGeral);
    free(filaPrioridade->itens);
    free(filaPrioridade);

    return 0;
}
