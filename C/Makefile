CC = gcc
CFLAGS = -g -Wall -std=c99

# Utility targets
utils.o: utils.c utils.h
	${CC} ${CFLAGS} -c utils.c

vector.o: vector.c vector.h utils.h
	${CC} ${CFLAGS} -c vector.c

test-vector.o: test-vector.c utils.h vector.h
	${CC} ${CFLAGS} -c test-vector.c

test-vector: vector.o utils.o test-vector.o
	${CC} ${CFLAGS} -o test-vector test-vector.o vector.o utils.o

# Add a clean target that silently removes the .o files
clean:
	@rm *.o test-vector 2> /dev/null || true
