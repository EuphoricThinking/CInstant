llvm-as -o ./build/runtime.bc ./lib/runtime.ll 
llvm-as -o ./build/temp.bc out.ll
llvm-link -o out.bc ./build/temp.bc ./build/runtime.bc 