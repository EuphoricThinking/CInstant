all:
	gcc -g src/compiler.c src/cavl.c src/Parser.c src/Lexer.c src/Absyn.c -o insc_llvm -Isrc
	gcc -g src/jasminCompiler.c src/cavl.c src/Parser.c src/Lexer.c src/Absyn.c src/castree.c -o insc_jvm -Isrc

clean:
	rm insc_jvm insc_llvm

jasm:
	valgrind --leak-check=full ./insc_jvm dummyj.ins
	java -jar ./lib/jasmin.jar dummyj.j

test:
	valgrind --leak-check=full ./insc_jvm test.ins
	java -jar ./lib/jasmin.jar test.j
	java test