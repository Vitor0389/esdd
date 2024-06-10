#ifndef TREE_H
#define TREE_H

typedef struct _node {
    char content;
    struct _node *left;
    struct _node *right;
} node;

typedef struct {
    node *raiz;
} tree;

node* create_node(char content);
tree* create_tree();
void create(tree *arvore, const char *str);
void pre_order(node *no);
void in_order(node *no);
void post_order(node *no);
int height(node *no);
node* search(node *no, char content);
void print_tree(node *no, int depth);
int validate_expression(const char *str);
node* parse_tree(const char **str);

#endif
