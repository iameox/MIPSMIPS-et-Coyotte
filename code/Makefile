all: main.o functions.o files.o
	gcc -o main main.o functions.o files.o

main.o: main.c
	gcc -c main.c -Wall

files.o: files.c files.h
	gcc -c files.c -Wall

functions.o: functions.c functions.h
	gcc -c functions.c -Wall

clean:
	rm -rf *.o