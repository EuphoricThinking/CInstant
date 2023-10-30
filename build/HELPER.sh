llvm-as -o ./build/runtime.bc ./build/runtime.ll 
llvm-as -o ./build/temp.bc playground/a.ll
llvm-link -o playground/a.bc ./build/temp.bc ./build/runtime.bc 