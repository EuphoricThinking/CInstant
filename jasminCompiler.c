/* File generated by the BNF Converter (bnfc 2.9.4). */

/************************* Compiler Front-End Test *************************/
/*                                                                         */
/*  This test will parse a file, print the abstract syntax tree, and then  */
/*  pretty-print the result.                                               */
/*                                                                         */
/***************************************************************************/
// TODO check errors
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#include "grammar/Parser.h"
//#include "grammar/Printer.h"
#include "grammar/Absyn.h"
#include "cavl.h"
#include "jasmin_constants.h"
#include "castree.h"

#define UINT32_FORMATTER PRIu32

// TODO check for max values
method_text* method_body;

void initialize_method_body() {
  method_body = malloc(sizeof(method_body));
  method_body->text = malloc(sizeof(char) * INIT_BUFF_SIZE);
  method_body->cursor = 0;
  method_body->len = INIT_BUFF_SIZE;
}

void free_body() {
  free(method_body->text);
  free(method_body);
}

void concatenate_at_the_end(char* text) {
  size_t suff_len = strlen(text);

  if (method_body->cursor + suff_len + 1 < method_body->len) {
    method_body->len = method_body->len * 2;
    method_body->text = realloc(method_body->text, method_body->len);
    // TODO check for errors
  }

  memcpy(method_body + method_body->cursor, text, suff_len);
  method_body->cursor += suff_len;
  // At the end added null pointer
}

int last_register = 0;
Node* assignment_dictionary = NULL;
int last_load = 0;

int max_stack = 0;
int max_locals = 1; // default is 1

int get_new_register_increase_previous() {
  return last_register++;
}

int get_new_load() {
  return last_load++;
}

// TODO change to single fprintf

void usage(void) {
  printf("usage: Call with one of the following argument combinations:\n");
  printf("\t--help\t\tDisplay this help message.\n");
  printf("\t(no arguments)\tParse stdin verbosely.\n");
  printf("\t(files)\t\tParse content of files verbosely.\n");
  printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}



void invoke_printer_start(FILE* opened) {
  fprintf(opened, "%s", GET_PRINTER);
}

void invoke_printer_end(FILE* opened) {
  fprintf(opened, "%s", INVOKE_PRINTER);
}

int get_expr_value(Exp expr) {
  return expr->u.explit_.integer_;
}

char* get_expr_ident(Exp expr) {
  return expr->u.expvar_.ident_;
}

void update_stack_limit(int new_value) {
  max_stack = max(max_stack, new_value);
}





void determine_literal_opcode_push_onto_stack(Exp exp, FILE* opened) {
  int value = get_expr_value(exp);

  if (value >= ICONST_RANGE_MIN && value <= ICONST_RANGE_MAX) {
    fprintf(opened, "%s%d\n", ICONST_SHORT, value);
    //concatenate_at_the_end(I)
  }
  else if (value < BIPUSH_LIMIT) {
    fprintf(opened, "%s%d\n", BIPUSH, value);
  }
  else if (value < SIPUSH_LIMIT) {
    fprintf(opened, "%s%d\n", SIPUSH, value);
  }
  else if (value == -1) {
    fprintf(opened, ICONST_M1);
  }
  else {
    fprintf(opened, "%s%d\n", PUSH, value);
  }
}

void determine_opcode_load(int local_num, FILE* opened) {
  if (local_num >= ILOAD_RANGE_MIN && local_num <= ILOAD_RANGE_MAX) {
    fprintf(opened, "%s%d\n", ILOAD_SHORT, local_num);
  }
  else {
    fprintf(opened, "%s%d\n", LOAD, local_num);
  }
}

void load_variable(Exp exp, FILE* opened) {
    Node* found = search(assignment_dictionary, get_expr_ident(exp));

    if (!found) return; // TODO error handling
    // assigned number - starting from 0
    invoke_printer_start(opened);
    determine_opcode_load(found->value, opened);
    invoke_printer_end(opened);
}



void perform_arithmetic(Exp exp, FILE* opened) {
  switch (exp->kind) {
    case is_ExpLit:
      determine_literal_opcode_push_onto_stack(exp, opened);
      break;

    case is_ExpVar:
      load_variable(exp, opened);

      break;


    default:
  }
}
void execute_assignment(Exp exp, Ident ident, FILE* ll_to_append) {}  

void execute_expression(Exp exp, FILE* opened) {
  // Node* found;
  switch(exp->kind) {
    // print a literal
    case is_ExpLit:
      invoke_printer_start(opened);
      determine_literal_opcode_push_onto_stack(exp, opened);
      invoke_printer_end(opened);

      break;
    // print a variable
    case is_ExpVar:
      load_variable(exp, opened);

      break;

    //print an expression
    default:
  }
}

void execute_statement(Stmt single_statement, FILE* opened) {
  if (single_statement->kind == is_SExp) {
      execute_expression(single_statement->u.sexp_.exp_, opened);
  }
  else if (single_statement->kind == is_SAss) {
      execute_assignment(single_statement->u.sass_.exp_, single_statement->u.sass_.ident_, opened);
  }
}

void execute_statements_list(ListStmt statements, FILE* opened) {
  // Not null
  if (statements) {
    execute_statement(statements->stmt_, opened);

    execute_statements_list(statements->liststmt_, opened);
  }

}
void iterate_over_program(Program program, FILE* opened) {
  if (!program->kind == is_Prog) {
    return;
  }
    
  ListStmt statements = program->u.prog_.liststmt_;

  execute_statements_list(statements, opened);
}

names_extensions* get_names(char* basename) {
  char* dot_occurence;

  names_extensions* result = malloc(sizeof(names_extensions));
  if (!basename || !(dot_occurence = strrchr(basename, '.')) || dot_occurence == basename) {
    char* stdin_name = malloc(sizeof(char) * STDIN_NAME_LEN); 
    strcpy(stdin_name, STDIN_NAME);
    char* stdin_j = malloc(sizeof(char) * STDIN_J_LEN);

    result->name = stdin_name;
    result->ext = stdin_j;
    // names_extensions result = { .ll_ext = stdin_name, .bc_ext = stdin_bc};
    return result;
  }

   ;

  
    int basename_len = (int) strlen(basename);
    // only the extension
    int ext_len = (int) strlen(dot_occurence + 1);
    int core_size;

    if (basename_len > ext_len) {
      core_size = basename_len - ext_len;
    }
    else {
      core_size = ext_len - basename_len;
    }

    char* j_filename = malloc(((size_t) core_size)*sizeof(char) + J_LEN);

    memcpy(j_filename, basename, core_size);
    memcpy(j_filename + core_size, J_EXT, J_LEN);
    // ll_filename[core_size + LL_LEN - 1] = '\0';

    char* single_name = malloc(sizeof(char) * core_size + 1);
    strncpy(single_name, basename, core_size);
    single_name[core_size - 1] = '\0';

    //return ll_filename;
    //return {ll_filename, bc_filename};
    result->name = single_name;
    result->ext = j_filename;

    //names_extensions result = { .ll_ext = ll_filename, .bc_ext = bc_filename};
    return result;
  //}
}

// void append_instruction_to_the_end(FILE* opened_ll_file)
void free_names(names_extensions* names) {
  free(names->ext);
  free(names->name);
  free(names);
}



void print_jasmin_header(names_extensions* names, FILE* opened) {
  fprintf(opened, "%s%s\n%s", CLASS_BEGINNING, names->name, SUPER_DECL);
  fprintf(opened, BEGIN_METHOD); //"%s%s()V\n", BEGIN_METHOD, names->name);
}

void print_jasmin_end(FILE* opened) {
  fprintf(opened, "%s%s", RETURN, END_METHOD);
}

void print_jasmin_stack_locals(FILE* opened) { //}, int locals_size, int stack_size) {
  fprintf(opened, "%s%d\n", LOCALS_SIZE, max_locals);//locals_size);
  fprintf(opened, "%s%d\n", STACK_SIZE, max_stack); //stack_size);
}

int determine_tree(Exp exp) {
  if (is_leaf(exp)) {
    return 1;
  }

  Exp e1 = get_exp1(exp);
  Exp e2 = get_exp2(exp);

  int subtree1 = determine_tree(e1);
  int subtree2 = determine_tree(e2);

  if (subtree1 == subtree2) {
    return subtree1 + 1;
  }
  else {
    return max(subtree1, subtree2);
  }
}

void determine_expression(Exp exp) {
  int max_height;
  int stack_height_with_print;
  switch(exp->kind) {
    // print literal
    case is_ExpLit:
      update_stack_limit(PRINT_STACK);
      // invoke_printer_start(opened);
      // determine_literal_opcode_push_onto_stack(exp, opened);
      // invoke_printer_end(opened);
      break;
    // print variable
    case is_ExpVar:
      update_stack_limit(PRINT_STACK);
      break;

    // The whole expression is to be printed
    default:
      max_height = determine_tree(exp);
      // One at the top of the stack
      stack_height_with_print = max(max_height, PRINT_STACK);
      update_stack_limit(stack_height_with_print);
  }
}

void update_variables_count() {
  max_locals++;
}

void determine_assignment(Exp exp, Ident ident) {
  Node* found = search(assignment_dictionary, ident);
  if (!found) {
        update_variables_count();
        assignment_dictionary = insert(assignment_dictionary, ident, 0);
  }

  int max_height;
  int stack_height_with_print;
  switch (exp->kind) {
    // first time assignment to a literal
    case is_ExpLit:
      break;

    default:
      max_height = determine_tree(exp);
      stack_height_with_print = max(max_height, PRINT_STACK);
      update_stack_limit(stack_height_with_print);
  }
}

void determine_statement(Stmt single_statement) {
  if (single_statement->kind == is_SExp) {
      determine_expression(single_statement->u.sexp_.exp_);
  }
  else if (single_statement->kind == is_SAss) {
      determine_assignment(single_statement->u.sass_.exp_, single_statement->u.sass_.ident_);
  }
}

void determine_statement_list(ListStmt statements) {
  if (statements) {
    determine_statement(statements->stmt_);

    determine_statement_list(statements->liststmt_);
  }
}

void determine_stack_and_locals(Program program) {
  if (!program->kind == is_Prog) {
    return;
  }
    
  ListStmt statements = program->u.prog_.liststmt_;

  determine_statement_list(statements);
}

int list_stms_len(ListStmt stms) {
  if (!stms) return 0;
  return 1 + list_stms_len(stms->liststmt_);
}

void initialize_list_nodes_null(ast_node** listtree, int len) {
  for (int i = 0; i < len; i++) {
    listtree[i] = NULL;
  }
}

void free_list_nodes(ast_node** listtree, int len) {
  for (int i = 0; i < len; i++) {
    ast_node* temp = listtree[i];
    if (temp) {
      free_tree_ast(temp);
    }
  }

  free(listtree);
}

int main(int argc, char ** argv)
{
  printf("in\n");
  FILE *input;
  Program parse_tree;
  int quiet = 0;
  char *filename = NULL;

  if (argc > 1) {
    if (strcmp(argv[1], "-s") == 0) {
      quiet = 1;
      if (argc > 2) {
        filename = argv[2];
      } else {
        input = stdin;
      }
    } else {
      filename = argv[1];
    }
  }

  printf("next\n");

  if (filename) {
    input = fopen(filename, "r");
    if (!input) {
      usage();
      exit(1);
    }
  }
  else input = stdin;
  /* The default entry point is used. For other options see Parser.h */
  parse_tree = pProgram(input);

  fclose(input);

  if (parse_tree)
  {
    printf("here\n");
    //char* filename_without_path = basename(filename);
    // printf("%s\n", filename_without_path);
    names_extensions* new_name = get_names(filename);
    // printf("%s\n", new_name);
    char* j_name = new_name->ext;

    // TODO add const char*
    // Erase the file content if the file has been already created
    

    initialize_method_body();

    printf("%s\n%s\n", new_name->ext, new_name->name);

    int prev = last_register;
    int next = get_new_register_increase_previous();
    
    printf("ha%d %d %d\n", prev, next, last_register);

    int list_len = 0;
    ast_node** list_of_trees = NULL;

    if (parse_tree->kind == is_Prog) {
      list_len = list_stms_len(parse_tree->u.prog_.liststmt_);
      initialize_list_nodes_null(list_of_trees, list_len);
    }

    ast_node** list_of_trees = malloc(sizeof(ast_node*) * list_len);

    // here we go
    determine_stack_and_locals(parse_tree, list_of_trees);

    fclose(fopen(j_name, "w"));
    FILE* opened_j_file = fopen(j_name, "a");
    print_jasmin_header(new_name, opened_j_file);
    print_jasmin_stack_locals(opened_j_file);

    free_tree(assignment_dictionary);
    assignment_dictionary = NULL;

    iterate_over_program(parse_tree, opened_j_file);

    print_jasmin_end(opened_j_file);

    free_Program(parse_tree);

    // fprintf(opened_ll_file, ZERO_RET_MAIN);
    // fprintf(opened_ll_file, END_MAIN_BRACKET);

    // create_shell_command(new_name);
    free_names(new_name);
    fclose(opened_j_file);

    extern char** environ;
    printf("printing\n");
    print_tree(assignment_dictionary);

    free_tree(assignment_dictionary);
    free_body();

    // if (execle(BASH_COMMAND, BASH_COMMAND, HELPER_NAME, NULL, environ) == -1) {

    //   return 1;
    // }

    // int call_result = system(COMPILE_TO_BC_COMMAND);
    // printf("%d i chuj\n", call_result);

    return 0;
  }
  return 1;
}

