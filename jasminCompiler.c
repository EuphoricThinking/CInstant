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
#include "grammar/Parser.h"
//#include "grammar/Printer.h"
#include "grammar/Absyn.h"
#include "cavl.h"
#include "jasmin_constants.h"

#define UINT32_FORMATTER PRIu32

// TODO check for max values

int last_register = 0;
Node* assignment_dictionary = NULL;
int last_load = 0;

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

// void print_value(FILE* ll_to_append, int value) {
//   fprintf(ll_to_append, PRINT_INT_START);
//   fprintf(ll_to_append, "%d", value);
//   fprintf(ll_to_append, PRINT_INT_END);
// }

// void print_register(FILE* ll_to_append, int register_num) {
//   fprintf(ll_to_append, "%s%d%s", PRINT_REGISTER_START, register_num, PRINT_REGISTER_END);
// }

// int load_variable(FILE* ll_to_append, char* register_name) {
//   int new_load = get_new_load();
//   fprintf(ll_to_append, "%s%d%s%s%s", LOAD_START, new_load, LOAD_MIDDLE, register_name, LOAD_END);

//   return new_load;
// }
// void print_variable(FILE* ll_to_append, char* register_name) {
//   int load_register = load_variable(ll_to_append, register_name);
//   fprintf(ll_to_append, PRINT_VAR_START);
//   fprintf(ll_to_append, "%d", load_register);
//   fprintf(ll_to_append, PRINT_VAR_END);
// }
// void store_value(FILE* ll_to_append, char* register_name, int value) {
//   fprintf(ll_to_append, STORE_START_VALUE);
//   fprintf(ll_to_append, "%d", value);
//   fprintf(ll_to_append, STORE_MIDDLE);
//   fprintf(ll_to_append, "%s", register_name);
//   fprintf(ll_to_append, STORE_END_REGISTER);
// }

// void store_register(FILE* ll_to_append, char* register_name, int register_num) {
//   fprintf(ll_to_append, "%s%%%d", STORE_START_VALUE, register_num);
//  // fprintf(ll_to_append, "%d", register_num);
//   fprintf(ll_to_append, STORE_MIDDLE);
//   fprintf(ll_to_append, "%s", register_name);
//   fprintf(ll_to_append, STORE_END_REGISTER);
// }

// // the value is in variable
// void store_variable(FILE* ll_to_append, char* register_name, int register_num) {
//   fprintf(ll_to_append, "%s%%load_%d", STORE_START_VALUE, register_num);
//  // fprintf(ll_to_append, "%d", register_num);
//   fprintf(ll_to_append, STORE_MIDDLE);
//   fprintf(ll_to_append, "%s", register_name);
//   fprintf(ll_to_append, STORE_END_REGISTER);
// }

// void alloca_assign(FILE* ll_to_append, char* register_name) {
//   fprintf(ll_to_append, ALLOCA_START);
//   fprintf(ll_to_append, "%s", register_name);
//   fprintf(ll_to_append, ALLOCA_END);
// }

// void initialize_variable(FILE* ll_to_append, char* register_name, int value) {
//   alloca_assign(ll_to_append, register_name);

//   store_value(ll_to_append, register_name, value);
// }

// void initialize_variable_with_register(FILE* ll_to_append, char* register_name, int register_num) {
//   alloca_assign(ll_to_append, register_name);

//   store_register(ll_to_append, register_name, register_num);
// }

// void initialize_variable_with_variable(FILE* ll_to_append, char* register_name, int register_num) {
//   alloca_assign(ll_to_append, register_name);

//   store_variable(ll_to_append, register_name, register_num);
// }

int get_expr_value(Exp expr) {
  return expr->u.explit_.integer_;
}

char* get_expr_ident(Exp expr) {
  return expr->u.expvar_.ident_;
}

// void fprintf_register_var_or_literal(arithmetic_result arm_res, FILE* ll_to_append) {
//   if (arm_res.kind == is_variable) {
//     fprintf(ll_to_append, "%%load_%d", arm_res.register_num);
//   }
//   else if (arm_res.kind == is_register) {
//     fprintf(ll_to_append, "%%%d", arm_res.register_num);
//   }
//   else { // literal
//     fprintf(ll_to_append, "%d", arm_res.value);
//   }
// }

// void perform_arithm_op_assign_reg(int register_result, arithmetic_result expr1, arithmetic_result expr2, FILE* ll_to_append, enum Op_type operation) {

//   switch (operation) {
//     case ADD:
//       fprintf(ll_to_append, "\t%%%d = %s", register_result, ADD_START);
//       break;
//     case DIV:
//       fprintf(ll_to_append, "\t%%%d = %s", register_result, DIV_START);
//       break;
//     case MUL:
//       fprintf(ll_to_append, "\t%%%d = %s", register_result, MUL_START);
//       break;
//     case SUB:
//       fprintf(ll_to_append, "\t%%%d = %s", register_result, SUB_START);
//       break;
//   }

//   fprintf_register_var_or_literal(expr1, ll_to_append);

//   fprintf(ll_to_append, ARITHM_MIDDLE);

//   fprintf_register_var_or_literal(expr2, ll_to_append);

//   fprintf(ll_to_append, ARITHM_END);
// }

enum Op_type get_operation_type(Exp expr) {
  switch (expr->kind) {
    case is_ExpAdd:
      return ADD;
    case is_ExpSub:
      return SUB;
    case is_ExpDiv:
      return DIV;
    case is_ExpMul:
      return MUL;
  }
}

// arithmetic_result parse_tree_calculate(Exp expr, FILE* ll_to_append) {
//   Node* found;
//   arithmetic_result result;
//   arithmetic_result exp1_res;
//   arithmetic_result exp2_res;
//   int new_register;
//   int new_load;
//   switch (expr->kind) {
//     case is_ExpLit:
//       result.kind = is_literal;
//       result.variable = NULL;
//       result.register_num = -1;
//       result.value = get_expr_value(expr);

//       return result;

//     case is_ExpVar:
//       new_load = load_variable(ll_to_append, get_expr_ident(expr));
//       result.kind = is_variable;
//       result.variable = get_expr_ident(expr);
//       result.register_num = new_load;

//       return result;

//     default:
//       exp1_res = parse_tree_calculate(expr->u.expadd_.exp_1, ll_to_append);
//       exp2_res = parse_tree_calculate(expr->u.expadd_.exp_2, ll_to_append);

//       new_register = get_new_register_increase_previous();

//       perform_arithm_op_assign_reg(new_register, exp1_res, exp2_res, ll_to_append, get_operation_type(expr));

//       result.kind = is_register;
//       result.variable = NULL;
//       result.register_num = new_register;
//       result.value = -1;

//       return result;
//   }
// }
// // load and print

// void execute_expression(Exp expression, FILE* ll_to_append) {
//   Node* found = NULL;
//   switch (expression->kind) {
//     // single expression to print
//     case is_ExpLit:
//       printf("%d\n", expression->u.explit_.integer_);
//       print_value(ll_to_append, expression->u.explit_.integer_);

//       break;

//     // single variable to print
//     case is_ExpVar:
//       printf("variable\n");
//       found = search(assignment_dictionary, expression->u.expvar_.ident_);
//       if (!found) printf("not found\n");
//       print_variable(ll_to_append, found->ident);

//       break;

//     // whole statement to print
//     default:
//       arithmetic_result result = parse_tree_calculate(expression, ll_to_append);
//       print_register(ll_to_append, result.register_num);
//   }
// }

// void execute_assignment(Exp exp, Ident ident, FILE* ll_to_append) {
//   Node* found = search(assignment_dictionary, ident);
//   arithmetic_result arm_res;
//   int value;
//   int register_num;

//   switch (exp->kind) {
//     case is_ExpLit:
//       value = exp->u.explit_.integer_;
//       if (found) {
//         found->value = value;
//         store_value(ll_to_append, ident, value);
//       }
//       else {
//         char* new_ident = strdup(ident);
//         assignment_dictionary = insert(assignment_dictionary, new_ident, value);

//         initialize_variable(ll_to_append, ident, value);
//       }
//       break;

//     default:
//       arm_res = parse_tree_calculate(exp, ll_to_append);
//       register_num = arm_res.register_num;
//       if (arm_res.kind == is_variable) printf("var%d\n", is_variable);
//       printf("%s %d %d\n", ident, arm_res.kind, arm_res.register_num);

//       if (found) {
//         found->value = value;
//         if (arm_res.kind == is_register) {
//    //       store_register(ll_to_append, ident, register_num);
//         }
//         else { //assignment from varuabke
//           store_variable(ll_to_append, ident, register_num);
//         }
//       }
//       else {
//         char* new_ident = strdup(ident);
//         assignment_dictionary = insert(assignment_dictionary, new_ident, register_num); // -1 ough to b

//         if (arm_res.kind == is_register) {
//           initialize_variable_with_register(ll_to_append, ident, register_num);
//         }
//         else {
//           initialize_variable_with_variable(ll_to_append, ident, register_num);
//         }
//       }
//   }
//   // switch (exp->kind) {
//   //   // ident = exp.int
//   //   case is_ExpLit:
//   //     printf("literal\n");
//   //     found = search(assignment_dictionary, ident);
//   //     int value = exp->u.explit_.integer_;

//   //     if (found) {
//   //       found->value = value;
//   //       store_value(ll_to_append, ident, value);
//   //     }
//   //     else {
//   //       char* new_ident = strdup(ident);
//   //       printf("cmp %d\n", strcmp(new_ident, ident));
//   //       assignment_dictionary = insert(assignment_dictionary, new_ident, value);

//   //       initialize_variable(ll_to_append, ident, value);
//   //     }

//   //     break;

//   //   // an expression x = 2*4
//   //   default:
//   //     arm_res = parse_tree_calculate(exp, ll_to_append);

//   // }
// }

void execute_assignment(Exp exp, Ident ident, FILE* ll_to_append) {}  
void execute_expression(Exp exp, FILE* ll_to_append) {}

void execute_statement(Stmt single_statement, FILE* ll_to_append) {
  if (single_statement->kind == is_SExp) {
      execute_expression(single_statement->u.sexp_.exp_, ll_to_append);
  }
  else if (single_statement->kind == is_SAss) {
      execute_assignment(single_statement->u.sass_.exp_, single_statement->u.sass_.ident_, ll_to_append);
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

  // // Null pointer or the same as basename pointer
  // if (! dot_occurence || dot_occurence == basename) {
  //   //return NULL;
  //   // Return only stdin.ll
  //   char* stdin_name = malloc(sizeof(char) * STDIN_STR_LEN); 
  //   strcpy(stdin_name, STDIN_NAME);

  //   return stdin_name;
  // }
  // else {
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

// // TODO check for errors
// void create_shell_command(names_extensions* names) {
//   fclose(fopen(HELPER_NAME, "w"));
//   FILE* helper_script = fopen(HELPER_NAME, "a");
//   fprintf(helper_script, LLVM_AS_START);
//   fprintf(helper_script, names->ll_ext);
//   fprintf(helper_script, LLVM_AS_END);
//   fprintf(helper_script, LLVM_LINK_START);
//   fprintf(helper_script, names->bc_ext);
//   fprintf(helper_script, LLVM_LINK_END);
//   fclose(helper_script);
// }

void print_jasmin_header(names_extensions* names, FILE* opened) {
  fprintf(opened, "%s%s\n%s", CLASS_BEGINNING, names->name, SUPER_DECL);
  fprintf(opened, "%s%s()V\n", BEGIN_METHOD, names->name);
}

void print_jasmin_end(FILE* opened) {
  fprintf(opened, END_METHOD);
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
    fclose(fopen(j_name, "w"));
    FILE* opened_j_file = fopen(j_name, "a");
    print_jasmin_header(new_name, opened_j_file);

    printf("%s\n%s\n", new_name->ext, new_name->name);

    int prev = last_register;
    int next = get_new_register_increase_previous();
    
    printf("ha%d %d %d\n", prev, next, last_register);


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

    // if (execle(BASH_COMMAND, BASH_COMMAND, HELPER_NAME, NULL, environ) == -1) {

    //   return 1;
    // }

    // int call_result = system(COMPILE_TO_BC_COMMAND);
    // printf("%d i chuj\n", call_result);

    return 0;
  }
  return 1;
}
