/* File generated by the BNF Converter (bnfc 2.9.4). */

#ifndef SKELETON_HEADER
#define SKELETON_HEADER
/* You might want to change the above name. */

#include "Absyn.h"


void visitProgram(Program p);
void visitStmt(Stmt p);
void visitListStmt(ListStmt p);
void visitExp(Exp p);


void visitIdent(Ident i);
void visitInteger(Integer i);
void visitDouble(Double d);
void visitChar(Char c);
void visitString(String s);

#endif

