#ifndef CAVL_HEADER
#define CAVL_HEADER

#include <stdint.h>

#include "Parser.h"
#include "Absyn.h"

typedef struct Node {
    //int16_t balance_factor; //reduce to smaller
    struct Node *left;
    struct Node *right;
    char* ident;
    int value;
    int height;
} Node;

Node* search(Node* tree, char* ident);
Node* insert(Node* tree, char* ident, int value);
// void remove(Node* tree, char* ident);
void free_tree(Node* tree);
void print_tree(Node* tree);

#endif