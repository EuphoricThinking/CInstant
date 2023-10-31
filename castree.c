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

int max(int a, int b) {
  if (a < b) return b;
  return a;
}

bool have_both_leaves(Exp exp) {
  Exp e1 = get_exp1(exp);
  Exp e2 = get_exp2(exp);

  return is_leaf(e1) && is_leaf(e2);
}

Exp get_exp1(Exp exp) {
  switch (exp->kind) {
    case is_ExpAdd:
      return exp->u.expadd_.exp_1;
    case is_ExpSub:
      return exp->u.expsub_.exp_1;
    case is_ExpMul:
      return exp->u.expmul_.exp_1;
    case is_ExpDiv:
      return exp->u.expdiv_.exp_1;
    default:
      return exp;
  }
}

Exp get_exp2(Exp exp) {
  switch (exp->kind) {
    case is_ExpAdd:
      return exp->u.expadd_.exp_2;
    case is_ExpSub:
      return exp->u.expsub_.exp_2;
    case is_ExpMul:
      return exp->u.expmul_.exp_2;
    case is_ExpDiv:
      return exp->u.expdiv_.exp_2;
    default:
      return exp;
  }
}

static int get_height(ast_node* node) {
    if (!node) return 0;
    return node->height;
}

ast_node* get_ast_tree(Exp exp) {
    if (is_leaf(exp)) {
        ast_node* new_node = malloc(sizeof(ast_node));
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;
        new_node->expr = exp;

        return new_node;
    }

    Exp e1 = get_exp1(exp);
    Exp e2 = get_exp2(exp);

    ast_node* new_node = malloc(sizeof(ast_node));
    new_node->left = get_ast_tree(e1);
    new_node->right = get_ast_tree(e2);

    int left_height = get_height(new_node->left);
    int right_height = get_height(new_node->right);

    if (left_height == right_height) {
        new_node->height = left_height + 1;
    }
    else {
        new_node->height = max(left_height, right_height);
    }
    
    new_node->expr = expr;

    return new_node;
}