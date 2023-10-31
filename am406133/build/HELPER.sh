llvm-as -o ./build/runtime.bc ./lib/runtime.ll 
llvm-as -o ./build/temp.bc ../alloca.ll
llvm-link -o ../alloca.bc ./build/temp.bc ./build/runtime.bc 