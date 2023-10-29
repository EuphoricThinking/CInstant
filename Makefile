all:
	gcc -g compiler.c testReduce/Parser.c testReduce/Lexer.c testReduce/Absyn.c -o compilerInstant -ItestReduce

clean:
	rm compilerInstant
