#ifndef JASMIN_CONSTANTS_HEADER
#define JASMIN_CONSTANTS_HEADER

#include <stdint.h>

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

#define GET_PRINTER "\tgetstatic java/lang/System/out Ljava/io/PrintStream\n"
#define INVOKE_PRINTER "\tinvokevirtual java/io/PrintStream/println(I)V\n"

// push onto the stack
#define ICONST_RANGE_MIN 0
#define ICONST_RANGE_MAX 5
#define ICONST_SHORT "\ticonst_"

// push ith local variable onto the stack
#define ILOAD_RANGE_MIN 0
#define ILOAD_RANGE_MAX 3
#define ILOAD_SHORT "\tiload_"

#define ICONST_M1 "\ticonst_m1"

#define ISTORE_RANGE_MIN 0
#define ISTORE_RANGE_MAX 3

#define BIPUSH_LIMIT INT8_MAX
#define SIPUSH_LIMIT INT16_MAX

#define BIPUSH "\tbipush "
#define SIPUSH "\tsipush "

#define DUP "\tdup\n"
#define POP "\tpop\n"

#define SWAP "\tswap\n"

#define IRETURN "\tireturn\n"

#define LOAD "\tload "
#define STORE "\tstore "
#define PUSH "\tpush "
#define LDC "\tldc "

#define IMUL "\timul\n"
#define ISUB "\tisub\n"
#define IADD "\tiadd\n"
#define IDIV "\tidiv\n"


typedef struct names_extenstions {
    char* name;
    char* ext;
} names_extensions;


enum Op_type {ADD, SUB, DIV, MUL};

#endif