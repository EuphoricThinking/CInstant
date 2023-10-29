all:
	cd build && $(MAKE)
	gcc compiler.c build/Parser.c build/Lexer.c build/Absyn.c -o compilerInstant -Ibuild
