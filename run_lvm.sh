llvm-as -o runtime.bc build/runtime.ll
llvm-as -o foo.bc foo.ll
llvm-link -o out.bc foo.bc runtime.bc
lli out.bc