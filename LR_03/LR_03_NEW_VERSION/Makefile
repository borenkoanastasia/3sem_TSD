CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic #-linc

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# Files from .o to .exe

main.exe: out/main.o out/normal_matrica.o out/press_matrica.o out/input.o out/menu.o out/output_error_message.o \
out/vector.o out/testing.o out/list.o inc/common.h inc/list.h inc/input.h inc/menu.h inc/normal_matrica.h \
inc/press_matrica.h inc/testing.h inc/vector.h
	$(CC) -o main.exe out/main.o out/normal_matrica.o out/press_matrica.o out/input.o out/menu.o \
	out/output_error_message.o out/vector.o out/testing.o out/list.o

clean: 
	rm -rf out/*.o
	rm -rf *.exe