CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = src/main.o src/memory_work.o src/matrix.o src/input.o src/choise.o
ALL_I = inc/common.h inc/memory_work.h inc/matrix.h inc/input.h inc/choise.h

out/%.o: src/%.c 
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)
