/* File generated by the BNF Converter (bnfc 2.9.4). */

#ifndef ABSYN_HEADER
#define ABSYN_HEADER

/* strdup was not in the ISO C standard before 6/2019 (C2x), but in POSIX 1003.1.
 * See: https://en.cppreference.com/w/c/experimental/dynamic/strdup
 * Setting _POSIX_C_SOURCE to 200809L activates strdup in string.h.
 */
#define _POSIX_C_SOURCE 200809L

#include <stddef.h>  /* NULL */
#include <string.h>  /* strdup */

/* C++ Abstract Syntax Interface.*/

/********************   TypeDef Section    ********************/

typedef int Integer;
typedef char Char;
typedef double Double;
typedef char* String;
typedef char* Ident;

/********************   Forward Declarations    ***********************/
struct Program_;
typedef struct Program_ *Program;

struct Stmt_;
typedef struct Stmt_ *Stmt;

struct ListStmt_;
typedef struct ListStmt_ *ListStmt;

struct Exp_;
typedef struct Exp_ *Exp;

/********************   Abstract Syntax Classes    ********************/

struct Program_
{
  enum { is_Prog } kind;
  union
  {
    struct { ListStmt liststmt_; } prog_;
  } u;
};

Program make_Prog(ListStmt p0);

struct Stmt_
{
  enum { is_SAss, is_SExp } kind;
  union
  {
    struct { Exp exp_; Ident ident_; } sass_;
    struct { Exp exp_; } sexp_;
  } u;
};

Stmt make_SAss(Ident p0, Exp p1);
Stmt make_SExp(Exp p0);

struct ListStmt_
{
  Stmt stmt_;
  ListStmt liststmt_;
};

ListStmt make_ListStmt(Stmt p1, ListStmt p2);

struct Exp_
{
  enum { is_ExpAdd, is_ExpSub, is_ExpMul, is_ExpDiv, is_ExpLit, is_ExpVar } kind;
  union
  {
    struct { Exp exp_1, exp_2; } expadd_;
    struct { Exp exp_1, exp_2; } expsub_;
    struct { Exp exp_1, exp_2; } expmul_;
    struct { Exp exp_1, exp_2; } expdiv_;
    struct { Integer integer_; } explit_;
    struct { Ident ident_; } expvar_;
  } u;
};

Exp make_ExpAdd(Exp p0, Exp p1);
Exp make_ExpSub(Exp p0, Exp p1);
Exp make_ExpMul(Exp p0, Exp p1);
Exp make_ExpDiv(Exp p0, Exp p1);
Exp make_ExpLit(Integer p0);
Exp make_ExpVar(Ident p0);

/***************************   Cloning   ******************************/

Program clone_Program(Program p);
Stmt clone_Stmt(Stmt p);
ListStmt clone_ListStmt(ListStmt p);
Exp clone_Exp(Exp p);

/********************   Recursive Destructors    **********************/

/* These free an entire abstract syntax tree
 * including all subtrees and strings.
 *
 * Will not work properly if there is sharing in the tree,
 * i.e., when some pointers are aliased.  In this case
 * it will attempt to free the same memory twice.
 */

void free_Program(Program p);
void free_Stmt(Stmt p);
void free_ListStmt(ListStmt p);
void free_Exp(Exp p);


#endif
