#ifndef LLVM_COMMANDS_HEADER
#define LLVM_COMMANDS_HEADER

#define DECLARE_PRINT_INT_MAIN "declare void @printInt(i32)\ndefine i32 @main() {\n"
#define ZERO_RET_MAIN "\tret i32 0\n"
#define END_MAIN_BRACKET "}"
#define PRINT_INT_START "\tcall void @printInt(i32 "
#define PRINT_INT_END ")\n"

#define PRINT_VAR_START "\tcall void @printInt(i32 %%load_"
#define PRINT_VAR_END ")\n"

#define ALLOCA_START "\t%%"
#define ALLOCA_END " = alloca i32\n"

#define STORE_START_VALUE "\tstore i32 "
#define STORE_MIDDLE ", i32* %%"
#define STORE_END_REGISTER "\n"

#define LOAD_START "\t%load_"
#define LOAD_MIDDLE " = load i32, i32* %"
#define LOAD_END "\n"

#define LLVM_LINK_START "llvm-link -o "
#define LLVM_LINK_END " ./build/temp.bc ./build/runtime.bc "
#define LLVM_AS_START "llvm-as -o ./build/runtime.bc ./build/runtime.ll \nllvm-as -o ./build/temp.bc "
#define LLVM_AS_END "\n"
#define SHELL_COMMAND_LENGTH 93 // +2
#define HELPER_NAME "./build/HELPER.sh"
#define COMPILE_TO_BC_COMMAND "echo \"dupa\" > dupa.txt && bash ./build/HELPER.sh"

#define BASH_COMMAND "/bin/sh"


#endif