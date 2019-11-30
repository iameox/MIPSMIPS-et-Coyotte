all: main.o functions.o instructions.o files.o
	gcc -o main main.o functions.o instructions.o files.o

main.o: code/main.c
	gcc -c code/main.c -Wall

functions.o: code/functions.c code/functions.h
	gcc -c code/functions.c -Wall

instructions.o: code/instructions.c code/instructions.h
	gcc -c code/instructions.c -Wall

files.o: code/files.c code/files.h
	gcc -c code/files.c -Wall

clean:
	rm -rf *.o tests/out/out.s