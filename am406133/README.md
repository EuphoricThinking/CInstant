Compilation is done by running in the command line from the root folder with Makefile within:
`make`

The command `make` generates two compilers: `insc_jvm` and  `insc_llvm`. To compile a file with Instant code to Jasmine, use:

`./insc_jvm filename`
and then to run the generated code:
`lli filename.bc`

To compile a file with Instant code to LLVM, use:
`./insc_llvm filename[.extension]`
and then to run the generated code:
`java filename`
For both compilers the code is generated to the source folders of the inpu files.

Contents of the folders:
* `src` - supporting structures, functions and the compiler code. All code is written in C by myself, including AVL from scratch;
* `lib` - only for `jasmin.jar`;
* `build` - contains temporary files and scripts generated and by the compilers;
* `root` - the destination of the compilation; contains `Makefile`