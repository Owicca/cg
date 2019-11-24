CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 `pkg-config --cflags gtk+-3.0`
CLIBS = `pkg-config --libs gtk+-3.0`
LDFLAGS =
LDLIBS =

SRC = main.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
INSTALLDIR = ./
EXECNAME = exec
RM= rm -rf


all: install

install:
	${CC} ${CFLAGS} -o ${INSTALLDIR}/${EXECNAME} ${CLIBS} ${SRC}

run: install
	${INSTALLDIR}/${EXECNAME}

.PHONY: clean

clean:
	${RM} ${INSTALLDIR}*.o
	${RM} ${INSTALLDIR}${EXECNAME}

-include ${DEP}
