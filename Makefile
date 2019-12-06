CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 `pkg-config --cflags gtk+-3.0`
CLIBS = `pkg-config --libs gtk+-3.0`
LDFLAGS =
LDLIBS =
INCLUDES =

MAIN_SRC = $(wildcard *.c)
LIB_SRC = $(wildcard */*.c)
OBJ = $(patsubst %.c,%.o,$(MAIN_SRC)) \
			$(patsubst %/%.c,%.o,$(LIB_SRC))
INSTALLDIR = ./
EXECNAME = exec
RM= rm -rf

.PHONY: all clean run install

all: install

install: $(OBJ)
	$(CC) $(CFLAGS) -o $(INSTALLDIR)/$(EXECNAME) $(OBJ) $(CLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(CLIBS) -c $^ $(INCLUDES)

run: install
	$(INSTALLDIR)/$(EXECNAME)

clean:
	$(RM) $(INSTALLDIR)*.o
	$(RM) $(INSTALLDIR)$(EXECNAME)

-include $(DEP)
