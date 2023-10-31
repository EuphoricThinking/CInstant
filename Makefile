all:
	gcc -g compiler.c cavl.c testReduce/Parser.c testReduce/Lexer.c testReduce/Absyn.c -o compilerInstant -ItestReduce
	gcc -g jasminCompiler.c cavl.c testReduce/Parser.c testReduce/Lexer.c testReduce/Absyn.c castree.c -o insc_jvm -ItestReduce

clean:
	rm compilerInstant

jasm:
	valgrind --leak-check=full ./insc_jvm dummyj.ins
	java -jar ./lib/jasmin.jar dummyj.j
