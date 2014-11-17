CC = gcc
CFLAGS = -g -Wall -std=c99

# Utility targets
utils.o: utils.c utils.h
	${CC} ${CFLAGS} -c utils.c

# Add a clean target that silently removes the .o files
clean:
	@rm *.o 2> /dev/null || true
