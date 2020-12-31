CC = gcc
OBJS = main.o
COMPILE_OPTS = -g -Wall -c
OPTIM_OPTS = 
SANITIZERS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer

main: main.o vector.o files.o
	$(CC) main.o vector.o files.o -o optimizeDiskSpace $(OPTIM_OPTS) $(SANITIZERS)

main.o: src/main.c src/vector.h src/files.h
	$(CC) $(COMPILE_OPTS) $(OPTIM_OPTS) $(SANITIZERS) src/main.c -o main.o

files.o: src/files.c src/files.h src/vector.h
	$(CC) $(COMPILE_OPTS) $(OPTIM_OPTS) $(SANITIZERS) src/files.c -o files.o

vector.o: src/vector.c src/vector.h
	$(CC) $(COMPILE_OPTS) $(OPTIM_OPTS) $(SANITIZERS) src/vector.c -o vector.o

.PHONY = clean

clean:
	rm -f ./optimizeDiskSpace *.o
