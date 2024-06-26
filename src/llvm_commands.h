#ifndef LLVM_COMMANDS_HEADER
#define LLVM_COMMANDS_HEADER

#define DECLARE_PRINT_INT_MAIN "declare void @printInt(i32)\ndefine i32 @main() {\n"
#define ZERO_RET_MAIN "\tret i32 0\n"
#define END_MAIN_BRACKET "}"
#define PRINT_INT_START "\tcall void @printInt(i32 "
#define PRINT_INT_END ")\n"

#define PRINT_VAR_START "\tcall void @printInt(i32 %%load_"
#define PRINT_VAR_END ")\n"

#define PRINT_REGISTER_START "\tcall void @printInt(i32 %"
#define PRINT_REGISTER_END ")\n"

#define ALLOCA_START "\t%%"
#define ALLOCA_END " = alloca i32\n"

#define STORE_START_VALUE "\tstore i32 "
#define STORE_MIDDLE ", i32* %%"
#define STORE_END_REGISTER "\n"

#define LOAD_START "\t%load_"
#define LOAD_MIDDLE " = load i32, i32* %"
#define LOAD_END "\n"

#define ADD_START "add i32 "
#define MUL_START "mul i32 "
#define DIV_START "sdiv i32 "
#define SUB_START "sub i32 "

#define ARITHM_MIDDLE ", "
#define ARITHM_END "\n"

#define LLVM_LINK_START "llvm-link -o "
#define LLVM_LINK_END " ./build/temp.bc ./build/runtime.bc "
#define LLVM_AS_START "llvm-as -o ./build/runtime.bc ./lib/runtime.ll \nllvm-as -o ./build/temp.bc "
#define LLVM_AS_END "\n"
#define SHELL_COMMAND_LENGTH 93 // +2
#define HELPER_NAME "./build/HELPER.sh"
#define COMPILE_TO_BC_COMMAND "echo \"dupa\" > dupa.txt && bash ./build/HELPER.sh"

#define PRINT_INT_DEF "declare i32 @printf(i8*, ...)\n@dnl = internal constant [4 x i8] c\"%d\0A\00\"\ndefine void @printInt(i32 %x) {\t%t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0\n\tcall i32 (i8*, ...) @printf(i8* %t0, i32 %x)\n\tret void\n}\n\n"

#define BASH_COMMAND "/bin/sh"

enum Op_type {ADD, DIV, MUL, SUB};


#endif