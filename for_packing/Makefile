all:
	gcc -g compiler.c lib/cavl.c grammar/Parser.c grammar/Lexer.c grammar/Absyn.c -o insc_jvm -Igrammar -Ilib
	gcc -g jasminCompiler.c lib/cavl.c grammar/Parser.c grammar/Lexer.c grammar/Absyn.c lib/castree.c -o insc_jvm -Igrammar -Ilib

clean:
	rm compilerInstant

jasm:
	valgrind --leak-check=full ./insc_jvm dummyj.ins
	java -jar ./lib/jasmin.jar dummyj.j

test:
	valgrind --leak-check=full ./insc_jvm test.ins
	java -jar ./lib/jasmin.jar test.j
	java test