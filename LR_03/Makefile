CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic

ALL_O = out/input.o out/norm_matrix.o out/press_matrix.o out/main.o out/create.o out/testing.o out/menu.o out/output_error_message.o
ALL_I = inc/common.h inc/create.h inc/input.h inc/norm_matrix.h inc/press_matrix.h inc/menu.h inc/testing.h

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) -o $@ $(ALL_O)