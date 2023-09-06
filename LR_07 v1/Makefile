CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_O = out/memory_work.o out/check_connectivity.o out/main.o
ALL_I = inc/memory_work.h inc/check_connectivity.h inc/common.h

out/%.o:src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $@ $(ALL_I)