# Project C -- doubly linked list

this implementation only uses a single memory array to store all the nodes and do not use a malloc (memory allocation) for every node that is created.
As a result,this implementation is optimal in memory and time complexity.

All the project documentation is  [here](Sujet_projet_ver08.pdf).

------------------

# How to use :
there is a makefile where all the commands are specified but doing just the command `$ make`   in  the parent repertory will create three executable files for the three different tests files as follows :
* homogene -> all the nodes have the same size
* random   -> very long and random sequence of adding and deletting nodes in the list
* unitaire -> test all the functions implemented,one by one.
## Check memory leak
Once tested, you can check if there is a memory leak with our implementation with the 
  [Valgrind guide ](http://valgrind.org/docs/manual/quick-start.html "Valgrind tutorial") and use it with any file : \
  `valgrind --leak-check=yes ./random.o  `
