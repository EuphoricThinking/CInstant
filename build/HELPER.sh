llvm-as -o ./build/runtime.bc ./build/runtime.ll 
llvm-as -o ./build/temp.bc vars.ll
llvm-link -o vars.bc ./build/temp.bc ./build/runtime.bc 