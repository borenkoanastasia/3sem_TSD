CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = out/main.o out/sort.o out/help.o out/input.o out/adress_work.o out/stack_work.o out/testing.o out/menu.o
ALL_I = inc/common.h inc/sort.h inc/input.h inc/help.h inc/adress_work.h inc/stack_work.h inc/testing.h inc/menu.h

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_I) $(ALL_O)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)