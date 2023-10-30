#include "cavl.h"
#include <string.h>
#include <stdbool.h>

void insert(Node* tree, char* ident, int value) {
    tree = _insert(tree, ident, value);
}

static int max(int a, int b) {
    if (a < b) return b;
    return a;
}

static int get_height(Node* tree) {
    if (!tree) {
        return 0;
    }
    else {
        return tree->height;
    }
}

static void _update_height(Node* tree) {
    int height_left = get_height(tree->left);
    int height_right = get_height(tree->right);

    tree->height = max(height_left, height_right) + 1;
}

// static void _get_balance_factor(Node* tree) {
//     if (tree->right && tree->left) {
//         return get_height(tree->left)
//     }
// }

static void _update(Node* tree) {
    int height_left = get_height(tree->left);
    int height_right = get_height(tree->right);

    int balance_factor = 

}

// if found return the node
// Perform strdup earlier for an identifier
static Node* _insert(Node* tree, char* ident, int value) {
    if (!tree) {
        Node* new_node = malloc(sizeof(Node));
        new_node->ident = ident;
        new_node->value = value;
        new_node->left = NULL;
        new_node->right = NULL;
        //new_node->balace_factor = 0;
        new_node->height = 1;

        return new_node;
    }

    int comp_result = strcmp(ident, tree->ident);
    if (comp_result < 0) {
        tree->left = _insert(tree->left, ident, value);
    }
    else if (comp_result > 0) {
        tree->right = _insert(tree->right, ident, value);
    } else {
        return tree;
    }

    _update(tree);
}