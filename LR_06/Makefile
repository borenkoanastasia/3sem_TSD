CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_I = inc/file_read.h inc/balance_work.h inc/tree_work.h inc/amazing_output.h
ALL_O = out/main.o out/file_read.o out/tree_work.o out/balance_work.o out/amazing_output.o

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)

clean: 
	rm -rf *.exe out/*.o