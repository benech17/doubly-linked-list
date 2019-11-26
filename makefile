CC=gcc
CFLAGS =-Wall -std=c11 -o -lm
SRC=$(wildcard *.c)
EXEC=$(SRC:.c=.o)
all:$(EXEC)
%.o:%.c
	@$(CC) $< $(CFLAGS) $@

cleanall:
	@rm -rf *.o
