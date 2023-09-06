CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = out/main.o out/sort.o out/stack_work.o out/choises.o out/input.o
ALL_I = inc/common.h inc/sort.h inc/stack_work.h inc/input.h inc/choises.h

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_I) $(ALL_O)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)