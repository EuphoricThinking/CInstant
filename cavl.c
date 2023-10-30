#include "cavl.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



// void remove(Node* tree, char* ident) {
//     tree = _remove(tree, ident);
// }

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

static Node* _rotate_left(Node* tree) {
    Node* right_child_to_go_up = tree->right;
    Node* left_child_to_switch_right = right_child_to_go_up->left;

    tree->right = left_child_to_switch_right;
    right_child_to_go_up->left = tree;

    _update_height(tree);
    _update_height(right_child_to_go_up);

    return right_child_to_go_up;
}

static Node* _rotate_right(Node* old_root) {
    Node* left_child_to_go_up = old_root->left;
    Node* right_child_to_switch_left = left_child_to_go_up->right;

    old_root->left = right_child_to_switch_left;
    left_child_to_go_up->right = old_root;

    _update_height(old_root);
    _update_height(left_child_to_go_up);

    return left_child_to_go_up;
}

static Node* _update(Node* tree, char* ident) {
    int height_left = get_height(tree->left);
    int height_right = get_height(tree->right);

    tree->height = max(height_left, height_right) + 1;

    int balance_factor = height_left - height_right;
    printf("bal%d\n", balance_factor);


    int cmp_child;

    // We know that the left is imbalanced, therefore we can check the left child
    // We compare key values to determine where nodes have been inserted
    if (balance_factor > 1) {
        cmp_child = strcmp(ident, tree->left->ident);
        
        // Left left
        if (cmp_child < 0) {
            return _rotate_right(tree);
        }
        // Left right
        else if (cmp_child > 0) {
            tree->left = _rotate_left(tree->left);
            return _rotate_right(tree);
        }
    }
    // Right tree is bigger
    else if (balance_factor < -1) {
        cmp_child = strcmp(tree->right->ident, ident);

        // Right right
        if (cmp_child < 0) {
            return _rotate_left(tree);
        }
        // Right left
        else if (cmp_child > 0) {
            tree->right = _rotate_right(tree->right);
            return _rotate_left(tree);
        }
    }
    else {
        return tree;
    }

}

// if found return the node
// Perform strdup earlier for an identifier
static Node* _insert(Node* tree, char* ident, int value) {
    if (!tree) {
        printf("inserting\n");
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
        printf("left\n");
        tree->left = _insert(tree->left, ident, value);
    }
    else if (comp_result > 0) {
        printf("right\n");
        tree->right = _insert(tree->right, ident, value);
    } else {
        printf("same\n");
        return tree;
    }

    printf("update\n");
    return _update(tree, ident);
}

void print_tree(Node* tree) {
    if (!tree) printf("NULL\n");
    if (tree) {
        print_tree(tree->left);
        printf("%s\n", tree->ident);
        print_tree(tree->right);
    }
}

void free_tree(Node* tree) {
    if (tree) {
        free_tree(tree->left);
        free_tree(tree->right);

        // should be satisfied
        free(tree->ident);
        free(tree);
    }
}

Node* search(Node* tree, char* ident) {
    if (!tree) {
        return NULL;
    }

    int comp_result = strcmp(ident, tree->ident);
    if (comp_result < 0) {
        return search(tree->left, ident);
    }
    else if (comp_result > 0) {
        return search(tree->right, ident);
    }
    else {
        return tree;
    }
}

Node* insert(Node* tree, char* ident, int value) {
    return _insert(tree, ident, value);
}


// static Node* _remove(Node* tree, char* ident) {
//     if (!tree) {
//         return tree;
//     }

//     int comp_result = strcmp(ident, tree->left);
//     if (comp_result < 0) {
//         tree->left = _remove(tree->left, ident);
//     }
//     else if (comp_result > 0) {
//         tree->right = _remove(tree->right, ident);
//     }
//     else {
//         return _free_node(tree);
//     }
// }