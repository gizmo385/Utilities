CC = gcc
CFLAGS = -g -Wall -std=c99

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

# Add a clean target that silently removes the .o files
clean:
	@rm *.o test-llist test-vector 2> /dev/null || true
