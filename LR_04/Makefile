CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = out/array.o out/main.o out/sort.o
ALL_I = inc/common.h inc/sort.h

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_I) $(ALL_O)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)