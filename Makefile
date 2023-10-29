CC = gcc -g
CCFLAGS = -W -Wall -Wsign-conversion -Wno-unused-parameter -Wno-unused-function -Wno-unneeded-internal-declaration ${CC_OPTS}

FLEX = flex
FLEX_OPTS = -Pinstant_

BISON = bison
BISON_OPTS = -t -pinstant_

OBJS = Absyn.o Buffer.o Lexer.o Parser.o

all : compilerInstant

compilerInstant : ${OBJS} compiler.o
	@echo "Linking CompilerInstant..."
	${CC} ${OBJS} compiler.o -o compilerInstant

Absyn.o : grammar/Absyn.c grammar/Absyn.h
	${CC} ${CCFLAGS} -c grammar/Absyn.c

Buffer.o : grammar/Buffer.c grammar/Buffer.h
	${CC} ${CCFLAGS} -c grammar/Buffer.c

Lexer.c : grammar/Instant.l
	${FLEX} ${FLEX_OPTS} -oLexer.c grammar/Instant.l

Parser.c Bison.h : grammar/Instant.y
	${BISON} ${BISON_OPTS} grammar/Instant.y -o Parser.c

Lexer.o : CCFLAGS+=-Wno-sign-conversion

Lexer.o : Lexer.c grammar/Bison.h
	${CC} ${CCFLAGS} -c Lexer.c

Parser.o : grammar/Parser.c grammar/Absyn.h grammar/Bison.h
	${CC} ${CCFLAGS} -c grammar/Parser.c
	
compiler.o : compiler.c grammar/Parser.h grammar/Printer.h grammar/Absyn.h
	${CC} ${CCFLAGS} -c compiler.c
