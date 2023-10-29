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

#include "grammar/Parser.h"
//#include "grammar/Printer.h"
#include "grammar/Absyn.h"
#include "compiler_constants.h"
#include "llvm_commands.h"

void usage(void) {
  printf("usage: Call with one of the following argument combinations:\n");
  printf("\t--help\t\tDisplay this help message.\n");
  printf("\t(no arguments)\tParse stdin verbosely.\n");
  printf("\t(files)\t\tParse content of files verbosely.\n");
  printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}

void print_value(FILE* ll_to_append, int value) {
  fprintf(ll_to_append, PRINT_INT_START);
  fprintf(ll_to_append, "%d", value);
  fprintf(ll_to_append, PRINT_INT_END);
}

void execute_expression(Exp expression, FILE* ll_to_append) {
  switch (expression->kind) {
    case is_ExpLit:
      printf("%d\n", expression->u.explit_.integer_);
      print_value(ll_to_append, expression->u.explit_.integer_);

      break;
  }
}
void execute_statement(Stmt single_statement, FILE* ll_to_append) {
  if (single_statement->kind == is_SExp) {
      execute_expression(single_statement->u.sexp_.exp_, ll_to_append);
  }
}

void execute_statements_list(ListStmt statements, FILE* ll_to_append) {
  // Not null
  if (statements) {
    execute_statement(statements->stmt_, ll_to_append);

    execute_statements_list(statements->liststmt_, ll_to_append);
  }

}
void iterate_over_program(Program program, FILE* ll_to_append) {
  if (!program->kind == is_Prog) {
    return;
  }
    
  ListStmt statements = program->u.prog_.liststmt_;

  execute_statements_list(statements, ll_to_append);
}

char* get_ll_filename(char* basename) {
  if (!basename) {
    char* stdin_name = malloc(sizeof(char) * STDIN_STR_LEN); 
    strcpy(stdin_name, STDIN_NAME);

    return stdin_name;
  }

  char* dot_occurence = strrchr(basename, '.');

  // Null pointer or the same as basename pointer
  if (! dot_occurence || dot_occurence == basename) {
    //return NULL;
    // Return only stdin.ll
    char* stdin_name = malloc(sizeof(char) * STDIN_STR_LEN); 
    strcpy(stdin_name, STDIN_NAME);

    return stdin_name;
  }
  else {
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

    char* ll_filename = malloc(((size_t) core_size)*sizeof(char) + LL_LEN);

    memcpy(ll_filename, basename, core_size);
    memcpy(ll_filename + core_size, LL_SUFF, LL_LEN);
    ll_filename[core_size + LL_LEN - 1] = '\0';

    return ll_filename;
  }
}

// void append_instruction_to_the_end(FILE* opened_ll_file)

int main(int argc, char ** argv)
{
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
    
    //char* filename_without_path = basename(filename);
    // printf("%s\n", filename_without_path);
    char* new_name = get_ll_filename(filename);
    printf("%s\n", new_name);

    // Erase the file content if the file has been already created
    fclose(fopen(new_name, "w"));
    FILE* opened_ll_file = fopen(new_name, "a");
    fprintf(opened_ll_file, DECLARE_PRINT_INT);

    iterate_over_program(parse_tree, opened_ll_file);

    free_Program(parse_tree);

    free(new_name);

    return 0;
  }
  return 1;
}

