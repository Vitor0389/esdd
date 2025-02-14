#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

node* create_node(char content) {
    node *no = (node*)malloc(sizeof(node));
    no->content = content;
    no->left = NULL;
    no->right = NULL;
    return no;
}

tree* create_tree() {
    tree *arvore = (tree*)malloc(sizeof(tree));
    arvore->raiz = NULL;
    return arvore;
}

int validate_expression(const char *str) {
    int balance = 0;
    int nodes = 0;

    while (*str) {
        if (*str == '(') {
            balance++;
        } else if (*str == ')') {
            balance--;
            if (balance < 0) return 0;
        } else if (*str >= 'A' && *str <= 'Z') {
            nodes++;
        } else if (*str == ',' && *(str + 1) != '\0') {
            // Ignora espa�os ap�s a v�rgula
            while (*(str + 1) == ' ') str++;
        } else if (*str != ',') {
            return 0;
        }
        str++;
    }

    return (balance == 0 && nodes > 0);
}


node* parse_tree(const char **str) {
    if (**str == '(') (*str)++; 

    if (**str == ')') { 
        (*str)++; 
        return NULL;
    }

    node *no = create_node(**str);
    (*str)++; 

    if (**str == ',') (*str)++; 

    no->left = parse_tree(str); 

    if (**str == ',') (*str)++; 

    no->right = parse_tree(str);

    if (**str == ')') (*str)++;

    return no;
}

void create(tree *arvore, const char *str) {
    if (!validate_expression(str)) {
        printf("Expressao mal formada.\n");
        return;
    }

    const char *ptr = str;
    arvore->raiz = parse_tree(&ptr);
}

void pre_order(node *no) {
    if (no != NULL) {
        printf("%c ", no->content);
        pre_order(no->left);
        pre_order(no->right);
    }
}

void in_order(node *no) {
    if (no != NULL) {
        in_order(no->left);
        printf("%c ", no->content);
        in_order(no->right);
    }
}

void post_order(node *no) {
    if (no != NULL) {
        post_order(no->left);
        post_order(no->right);
        printf("%c ", no->content);
    }
}

int height(node *no) {
    if (no == NULL) {
        return -1;
    } else {
        int left_height = height(no->left);
        int right_height = height(no->right);
        return (left_height > right_height ? left_height : right_height) + 1;
    }
}

node* search(node *no, char content) {
    if (no == NULL || no->content == content) {
        return no;
    } else {
        node *found_node = search(no->left, content);
        if (found_node == NULL) {
            found_node = search(no->right, content);
        }
        return found_node;
    }
}

void print_tree(node *no, int depth) {
    if (no == NULL) return;
    print_tree(no->right, depth + 1);
    for (int i = 0; i < depth; i++) printf("   ");
    printf("%c\n", no->content);
    print_tree(no->left, depth + 1);
}

int main(int argc, char *argv[]) {
    tree *arvore = create_tree();

    if (argc < 2) {
        printf("Uso: %s <comando> [argumento]\n", argv[0]);
        printf("Comandos:\n");
        printf("create <representation>\n");
        printf("pre\n");
        printf("in\n");
        printf("post\n");
        printf("height <node>\n");
        printf("print\n");
        return 1;
    }

    char command[100];
    char *arg = NULL;

    strcpy(command, argv[1]);
    if (argc > 2) {
        arg = argv[2];
    }

    if (strcmp(command, "create") == 0) {
        if (arg != NULL) {
            create(arvore, arg);
        } else {
            printf("Erro: estrutura da arvore nao fornecida.\n");
        }
    } else if (strcmp(command, "pre") == 0) {
        pre_order(arvore->raiz);
        printf("\n");
    } else if (strcmp(command, "in") == 0) {
        in_order(arvore->raiz);
        printf("\n");
    } else if (strcmp(command, "post") == 0) {
        post_order(arvore->raiz);
        printf("\n");
    } else if (strcmp(command, "height") == 0) {
        if (arg != NULL && strlen(arg) == 1) {
            node *n = search(arvore->raiz, arg[0]);
            if (n != NULL) {
                printf("Altura do nó %c: %d\n", arg[0], height(n));
            } else {
                printf("Nó não encontrado.\n");
            }
        } else {
            printf("Comando inválido.\n");
        }
    } else if (strcmp(command, "print") == 0) {
        print_tree(arvore->raiz, 0);
    } else if (strcmp(command, "exit") == 0) {
        // Nothing to do, just exit
    } else {
        printf("Comando inválido.\n");
        printf("Uso: %s <comando> [argumento]\n", argv[0]);
        printf("Comandos:\n");
        printf("create <representation>\n");
        printf("pre\n");
        printf("in\n");
        printf("post\n");
        printf("height <node>\n");
        printf("print\n");
    }

    return 0;
}
