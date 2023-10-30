#ifndef JASMIN_CONSTANTS_HEADER
#define JASMIN_CONSTANTS_HEADER

#define LOCALS_SIZE "\t.limit locals " 
#define STACK_SIZE "\t.limit stack " 

#define BEGIN_METHOD ".method public static "
#define END_METHOD ".end method\n"
#define CLASS_BEGINNING ".class public "
#define SUPER_DECL ".super java/lang/Object\n"

#define J_LEN 2
#define J_EXT "j"
#define STDIN_NAME "out"
#define STDIN_NAME_LEN 4
#define STDIN_J "out.j"
#define STDIN_J_LEN 6

typedef struct names_extenstions {
    char* name;
    char* ext;
} names_extensions;


enum Op_type {ADD, SUB, DIV, MUL};

#endif