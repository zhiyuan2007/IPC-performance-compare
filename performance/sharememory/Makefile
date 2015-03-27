OBJ= shmwrite shmread 
all: ${OBJ}
shmread:
	gcc -g -o shmread shmread.c
shmwrite:
	gcc -g -o shmwrite shmwrite.c
clean:
	rm -f ${OBJ}
.PHONY: ${OBJ}
