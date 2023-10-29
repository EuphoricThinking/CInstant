/* File generated by the BNF Converter (bnfc 2.9.4). */

/* C Abstract Syntax Implementation. */

#include <stdio.h>
#include <stdlib.h>
#include "Absyn.h"

/********************   Prog    ********************/

Program make_Prog(ListStmt p1)
{
    Program tmp = (Program) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating Prog!\n");
        exit(1);
    }
    tmp->kind = is_Prog;
    tmp->u.prog_.liststmt_ = p1;
    return tmp;
}

/********************   SAss    ********************/

Stmt make_SAss(Ident p1, Exp p2)
{
    Stmt tmp = (Stmt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SAss!\n");
        exit(1);
    }
    tmp->kind = is_SAss;
    tmp->u.sass_.ident_ = p1;
    tmp->u.sass_.exp_ = p2;
    return tmp;
}

/********************   SExp    ********************/

Stmt make_SExp(Exp p1)
{
    Stmt tmp = (Stmt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating SExp!\n");
        exit(1);
    }
    tmp->kind = is_SExp;
    tmp->u.sexp_.exp_ = p1;
    return tmp;
}

/********************   ListStmt    ********************/

ListStmt make_ListStmt(Stmt p1, ListStmt p2)
{
    ListStmt tmp = (ListStmt) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ListStmt!\n");
        exit(1);
    }
    tmp->stmt_ = p1;
    tmp->liststmt_ = p2;
    return tmp;
}

/********************   ExpAdd    ********************/

Exp make_ExpAdd(Exp p1, Exp p2)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpAdd!\n");
        exit(1);
    }
    tmp->kind = is_ExpAdd;
    tmp->u.expadd_.exp_1 = p1;
    tmp->u.expadd_.exp_2 = p2;
    return tmp;
}

/********************   ExpSub    ********************/

Exp make_ExpSub(Exp p1, Exp p2)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpSub!\n");
        exit(1);
    }
    tmp->kind = is_ExpSub;
    tmp->u.expsub_.exp_1 = p1;
    tmp->u.expsub_.exp_2 = p2;
    return tmp;
}

/********************   ExpMul    ********************/

Exp make_ExpMul(Exp p1, Exp p2)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpMul!\n");
        exit(1);
    }
    tmp->kind = is_ExpMul;
    tmp->u.expmul_.exp_1 = p1;
    tmp->u.expmul_.exp_2 = p2;
    return tmp;
}

/********************   ExpDiv    ********************/

Exp make_ExpDiv(Exp p1, Exp p2)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpDiv!\n");
        exit(1);
    }
    tmp->kind = is_ExpDiv;
    tmp->u.expdiv_.exp_1 = p1;
    tmp->u.expdiv_.exp_2 = p2;
    return tmp;
}

/********************   ExpLit    ********************/

Exp make_ExpLit(Integer p1)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpLit!\n");
        exit(1);
    }
    tmp->kind = is_ExpLit;
    tmp->u.explit_.integer_ = p1;
    return tmp;
}

/********************   ExpVar    ********************/

Exp make_ExpVar(Ident p1)
{
    Exp tmp = (Exp) malloc(sizeof(*tmp));
    if (!tmp)
    {
        fprintf(stderr, "Error: out of memory when allocating ExpVar!\n");
        exit(1);
    }
    tmp->kind = is_ExpVar;
    tmp->u.expvar_.ident_ = p1;
    return tmp;
}

/***************************   Cloning   ******************************/

Program clone_Program(Program p)
{
  switch(p->kind)
  {
  case is_Prog:
    return make_Prog (clone_ListStmt(p->u.prog_.liststmt_));

  default:
    fprintf(stderr, "Error: bad kind field when cloning Program!\n");
    exit(1);
  }
}

Stmt clone_Stmt(Stmt p)
{
  switch(p->kind)
  {
  case is_SAss:
    return make_SAss
      ( strdup(p->u.sass_.ident_)
      , clone_Exp(p->u.sass_.exp_)
      );

  case is_SExp:
    return make_SExp (clone_Exp(p->u.sexp_.exp_));

  default:
    fprintf(stderr, "Error: bad kind field when cloning Stmt!\n");
    exit(1);
  }
}

ListStmt clone_ListStmt(ListStmt liststmt)
{
  if (liststmt)
  {
    /* clone of non-empty list */
    return make_ListStmt
      ( clone_Stmt(liststmt->stmt_)
      , clone_ListStmt(liststmt->liststmt_)
      );
  }
  else return NULL; /* clone of empty list */
}

Exp clone_Exp(Exp p)
{
  switch(p->kind)
  {
  case is_ExpAdd:
    return make_ExpAdd
      ( clone_Exp(p->u.expadd_.exp_1)
      , clone_Exp(p->u.expadd_.exp_2)
      );

  case is_ExpSub:
    return make_ExpSub
      ( clone_Exp(p->u.expsub_.exp_1)
      , clone_Exp(p->u.expsub_.exp_2)
      );

  case is_ExpMul:
    return make_ExpMul
      ( clone_Exp(p->u.expmul_.exp_1)
      , clone_Exp(p->u.expmul_.exp_2)
      );

  case is_ExpDiv:
    return make_ExpDiv
      ( clone_Exp(p->u.expdiv_.exp_1)
      , clone_Exp(p->u.expdiv_.exp_2)
      );

  case is_ExpLit:
    return make_ExpLit (p->u.explit_.integer_);

  case is_ExpVar:
    return make_ExpVar (strdup(p->u.expvar_.ident_));

  default:
    fprintf(stderr, "Error: bad kind field when cloning Exp!\n");
    exit(1);
  }
}

/********************   Recursive Destructors    **********************/

/* These free an entire abstract syntax tree
 * including all subtrees and strings.
 *
 * Will not work properly if there is sharing in the tree,
 * i.e., when some pointers are aliased.  In this case
 * it will attempt to free the same memory twice.
 */

void free_Program(Program p)
{
  switch(p->kind)
  {
  case is_Prog:
    free_ListStmt(p->u.prog_.liststmt_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when freeing Program!\n");
    exit(1);
  }
  free(p);
}

void free_Stmt(Stmt p)
{
  switch(p->kind)
  {
  case is_SAss:
    free(p->u.sass_.ident_);
    free_Exp(p->u.sass_.exp_);
    break;

  case is_SExp:
    free_Exp(p->u.sexp_.exp_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when freeing Stmt!\n");
    exit(1);
  }
  free(p);
}

void free_ListStmt(ListStmt liststmt)
{
  if (liststmt)
  {
    free_Stmt(liststmt->stmt_);
    free_ListStmt(liststmt->liststmt_);
    free(liststmt);
  }
}

void free_Exp(Exp p)
{
  switch(p->kind)
  {
  case is_ExpAdd:
    free_Exp(p->u.expadd_.exp_1);
    free_Exp(p->u.expadd_.exp_2);
    break;

  case is_ExpSub:
    free_Exp(p->u.expsub_.exp_1);
    free_Exp(p->u.expsub_.exp_2);
    break;

  case is_ExpMul:
    free_Exp(p->u.expmul_.exp_1);
    free_Exp(p->u.expmul_.exp_2);
    break;

  case is_ExpDiv:
    free_Exp(p->u.expdiv_.exp_1);
    free_Exp(p->u.expdiv_.exp_2);
    break;

  case is_ExpLit:
    break;

  case is_ExpVar:
    free(p->u.expvar_.ident_);
    break;

  default:
    fprintf(stderr, "Error: bad kind field when freeing Exp!\n");
    exit(1);
  }
  free(p);
}
