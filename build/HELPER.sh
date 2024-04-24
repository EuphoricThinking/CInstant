llvm-as -o ./build/runtime.bc ./build/runtime.ll 
llvm-as -o ./build/temp.bc ../alloca.ll
llvm-link -o ../alloca.bc ./build/temp.bc ./build/runtime.bc 