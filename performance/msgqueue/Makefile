OBJ= server client
all: ${OBJ}
server:
	gcc -g -o msgrecv msgrecv.c
client:
	gcc -g -o msgsend msgsend.c
clean:
	rm -f ${OBJ}
.PHONY: ${OBJ}
