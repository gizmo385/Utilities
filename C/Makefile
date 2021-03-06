# Compiler options
CC = gcc
CFLAGS = -g -Wall -std=c99

# This regular expression matches the names of files from the test make directives
BINARY_REGEX = "test-(\w+)$$"

# Utility targets
utils.o: utils.c utils.h
	${CC} ${CFLAGS} -c utils.c

# Vector make directives
vector.o: vector.c vector.h utils.h
	${CC} ${CFLAGS} -c vector.c

test-vector: vector.o utils.o test-vector.o
	${CC} ${CFLAGS} -o test-vector test-vector.o vector.o utils.o

# Linked List make directives
llist.o: llist.c llist.h utils.h
	${CC} ${CFLAGS} -c llist.c

test-llist: llist.o utils.o test-llist.o
	${CC} ${CFLAGS} -o test-llist test-llist.o llist.o utils.o

# Binary Search Tree make directives
bst.o: bst.c bst.h utils.h functions.h
	${CC} ${CFLAGS} -c bst.c

test-bst: bst.o utils.o test-bst.o
	${CC} ${CFLAGS} -o test-bst test-bst.o bst.o utils.o

# Set make directives
set.o: set.c set.h bst.c bst.h utils.h functions.h
	${CC} ${CFLAGS} -c set.c

test-set: set.o bst.o utils.o test-set.o
	${CC} ${CFLAGS} -o test-set test-set.o bst.o set.o utils.o

# Add a clean target that silently removes the .o files
clean:
	@rm *.o 2> /dev/null || true
	@ls | egrep ${BINARY_REGEX} | xargs rm 2> /dev/null || true
