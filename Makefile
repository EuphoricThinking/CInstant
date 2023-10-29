CC = gcc -g
CCFLAGS = -W -Wall -Wsign-conversion -Wno-unused-parameter -Wno-unused-function -Wno-unneeded-internal-declaration ${CC_OPTS}

FLEX = flex
FLEX_OPTS = -Pinstant_

BISON = bison
BISON_OPTS = -t -pinstant_

OBJS = Absyn.o Buffer.o Lexer.o Parser.o Printer.o

all : TestInstant

TestInstant : ${OBJS} Test.o
	@echo "Linking TestInstant..."
	${CC} ${OBJS} Test.o -o TestInstant

Absyn.o : grammar/Absyn.c grammar/Absyn.h
	${CC} ${CCFLAGS} -c Absyn.c

Buffer.o : Buffer.c Buffer.h
	${CC} ${CCFLAGS} -c Buffer.c

Lexer.c : Instant.l
	${FLEX} ${FLEX_OPTS} -oLexer.c Instant.l

Parser.c Bison.h : Instant.y
	${BISON} ${BISON_OPTS} Instant.y -o Parser.c

Lexer.o : CCFLAGS+=-Wno-sign-conversion

Lexer.o : Lexer.c Bison.h
	${CC} ${CCFLAGS} -c Lexer.c

Parser.o : Parser.c Absyn.h Bison.h
	${CC} ${CCFLAGS} -c Parser.c