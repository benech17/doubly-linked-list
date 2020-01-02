CC=gcc
CFLAGS= -g -Wall -std=c11 -o 

exec:test_unitaire.c projet2019.c 
	$(CC)  $(CFLAGS)  exec.o test_unitaire.c projet2019.c -lm

clean:
	@rm -rf *.o
