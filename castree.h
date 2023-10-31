#include "grammar/Absyn.h"
#include <stdbool.h>

typedef struct ast_node {
    struct ast_node* left;
    struct ast_node* right;
    int height;
    Exp expr;
} ast_node;

void free_tree_ast(ast_node* tree);
bool is_leaf(Exp exp);
bool have_both_leaves(Exp exp);
