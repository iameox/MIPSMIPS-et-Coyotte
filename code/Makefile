all: main.o functions.o files.o
	gcc -o main main.o functions.o files.o

main.o: main.c
	gcc -c main.c -ansi -pedantic -Wall

files.o: files.c files.h
	gcc -c files.c -ansi -pedantic -Wall

functions.o: functions.c functions.h
	gcc -c functions.c -ansi -pedantic -Wall

clean:
	rm -rf *.o