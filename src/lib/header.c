#include "header.h"
#include <stdlib.h>

void alloc_node_children(node *n, unsigned int children) {
    if(children == 0) {
        n->children.count = 0;
        n->children.data = NULL;
    }
    else {
        n->children.count = children;
        n->children.data = malloc(children * sizeof(node));
    }
}

void fill_node_int(node *n, int i, unsigned int children) {
    n->c.value.i = i;
    n->c.which = 0;
    alloc_node_children(n, children);
}

void fill_node_float(node *n, float f, unsigned int children) {
    n->c.value.f = f;
    n->c.which = 1;
    alloc_node_children(n, children);
}

void fill_node_char(node *n, char c, unsigned int children) {
    n->c.value.c = c;
    n->c.which = 2;
    alloc_node_children(n, children);
}

node *generate_tree() {
    /* Generated tree:
        (6 ('c' (3) (1.5)) (12.5 ('h')) ('f' (3) (12.58)))
    */
    node *root = malloc(sizeof(node));
    fill_node_int(root, 6, 3);

    fill_node_char(&root->children.data[0], 'c', 2);
    fill_node_int(&root->children.data[0].children.data[0], 3, 0);
    fill_node_float(&root->children.data[0].children.data[1], 1.5f, 0);

    fill_node_float(&root->children.data[1], 12.5f, 1);
    fill_node_char(&root->children.data[1].children.data[0], 'h', 0);

    fill_node_char(&root->children.data[2], 'f', 2);
    fill_node_int(&root->children.data[2].children.data[0], 3, 0);
    fill_node_float(&root->children.data[2].children.data[1], 12.58f, 0);

    return root;
}

void free_tree(node *n) {
    if(n != NULL) {
        for(unsigned int i = 0; i < n->children.count; i++) free_tree(&n->children.data[i]);
        free(n->children.data);
    }
}