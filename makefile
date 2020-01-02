CC=gcc
CFLAGS= -g -Wall -std=c11 -o 


test1:test_unitaire.c projet2019.c 
	$(CC)  $(CFLAGS)  test1.o test_unitaire.c projet2019.c -lm

test2:test_homogene.c projet2019.c
	$(CC)  $(CFLAGS)  test2.o test_homogene.c projet2019.c -lm

clean:
	@rm -rf *.o
