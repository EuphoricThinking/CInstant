all:
	gcc -g compiler.c cavl.c testReduce/Parser.c testReduce/Lexer.c testReduce/Absyn.c -o compilerInstant -ItestReduce
	gcc -g jasminCompiler.c cavl.c testReduce/Parser.c testReduce/Lexer.c testReduce/Absyn.c -o insc_jvm -ItestReduce

clean:
	rm compilerInstant
