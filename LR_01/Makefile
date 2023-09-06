main.exe: main.c multiplication.c input_output.c input_output.h common.h multiplication.h
	gcc -std=c99 -Wall -Werror -Wvla -pedantic -c main.c multiplication.c input_output.c
	gcc -o main.exe main.o input_output.o multiplication.c

main_debug.exe: main.c multiplication.c input_output.c input_output.h common.h multiplication.h
	gcc -std=c99 -Wall -Werror -Wvla -pedantic -c main.c multiplication.c input_output.c
	gcc -o main_debug.exe main.o input_output.o multiplication.c


inout_tests.exe: input_output.c inout_tests.c input_output.h
	gcc -std=c99 -Wall -Werror -Wvla -pedantic -c input_output.c inout_tests.c
	gcc -o inout_tests.exe input_output.o inout_tests.o

all: main.exe

clean:
	rm -rf main.exe *.o
