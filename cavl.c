#include "cavl.h"
#include <string.h>

void insert(Node* tree, char* ident, int value) {
    tree = _insert(tree, ident, value);
}

// Perform strdup earlier for an identifier
Node* _insert(Node* tree, char* ident, int value) {
    if (!tree) {
        Node* new_node = malloc(sizeof(Node));
        new_node->ident = ident;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        //new_node->balace_factor = 0;
        new_node->height = 0;

        return new_node;
    }
}