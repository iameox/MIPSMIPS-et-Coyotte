all: main.o functions.o instructions.o files.o
	gcc -o main main.o functions.o instructions.o files.o

main.o: main.c
	gcc -c main.c -Wall

functions.o: functions.c functions.h
	gcc -c functions.c -Wall

instructions.o: instructions.c instructions.h
	gcc -c instructions.c -Wall

files.o: files.c files.h
	gcc -c files.c -Wall

clean:
	rm -rf *.o