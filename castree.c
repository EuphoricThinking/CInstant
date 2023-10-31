#include "castee.h"

void free_tree_ast(ast_node* tree) {
    if (tree) {
        free_tree_ast(tree->left);
        free_tree_ast(tree->right);
        free(tree);
    }
}

bool is_leaf(Exp exp) {
  return exp->kind == is_ExpLit || exp->kind == is_ExpVar;
}

bool have_both_leaves(Exp exp) {
  Exp e1 = get_exp1(exp);
  Exp e2 = get_exp2(exp);

  return is_leaf(e1) && is_leaf(e2);
}