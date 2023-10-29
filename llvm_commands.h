#ifndef LLVM_COMMANDS_HEADER
#define LLVM_COMMANDS_HEADER

#define DECLARE_PRINT_INT "declare void @printInt(i32)\n"
#define PRINT_INT_START "call void @printInt(i32 "
#define PRINT_INT_END ")\n"

#define LLVM_LINK_START "llvm-link -o "
#define LLVM_LINK_END " temp.bc runtime.bc"
#define LLVM_AS_START "llvm-as -o runtime.bc runtime.ll\nllvm-as -o temp.bc "


#endif