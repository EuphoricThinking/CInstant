#ifndef LLVM_COMMANDS_HEADER
#define LLVM_COMMANDS_HEADER

#define DECLARE_PRINT_INT_MAIN "declare void @printInt(i32)\ndefine i32 @main() {\n"
#define ZERO_RET_MAIN "\tret i32 0\n"
#define END_MAIN_BRACKET "}"
#define PRINT_INT_START "\tcall void @printInt(i32 "
#define PRINT_INT_END ")\n"

#define LLVM_LINK_START "llvm-link -o "
#define LLVM_LINK_END " ./build/temp.bc ./build/runtime.bc \n lli playground/a.bc > output.txt 2> error.txt"
#define LLVM_AS_START "llvm-as -o ./build/runtime.bc ./build/runtime.ll ; pwd > pwd.txt ; llvm-as -o ./build/temp.bc "
#define LLVM_AS_END "\n"
#define SHELL_COMMAND_LENGTH 93 // +2
#define HELPER_NAME "./build/HELPER.sh"
#define COMPILE_TO_BC_COMMAND "echo \"dupa\" > dupa.txt && bash ./build/HELPER.sh"

#endif