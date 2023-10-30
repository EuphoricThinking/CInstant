#ifndef COMPILER_CONSTANTS_HEADER
#define COMPILER_CONSTANTS_HEADER

typedef struct names_extensions {
    char* ll_ext;
    char* bc_ext;
} names_extensions;

#define STDIN_STR_LEN 7
#define STDIN_BC_LEN 7

#define STDIN_BC_NAME "out.bc"
#define STDIN_NAME "out.ll"

#define LL_LEN 3
#define LL_SUFF "ll"

#define BC_LEN 3
#define BC_SUFF "bc"

#endif