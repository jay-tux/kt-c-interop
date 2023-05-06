#ifndef __HEADER_H
#define __HEADER_H

struct _node;

typedef struct {
    struct _node *data;
    unsigned int count;
} array;

typedef struct {
    union {
        int i;      // which = 0
        float f;    // which = 1
        char c;     // which = 2
    } value;
    unsigned int which;
} content;

struct _node {
    content c;
    array children;
};

typedef struct _node node;

node *generate_tree();
void free_tree(node *);

#endif