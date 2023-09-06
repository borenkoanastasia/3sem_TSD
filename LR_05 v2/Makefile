CC = gcc
CFLAGS = -Wall -Werror -std=c99

ALL_I = inc/common.h inc/output.h $(LIST_I)
ALL_O = out/main.o out/output.o $(LIST_O)

ARR_I = inc/arr/automat_func.h inc/arr/simulation.h inc/arr/types_work.h inc/arr/array_work.h
ARR_O = out/arr/types_work.o out/arr/array_work.o out/arr/automat_func.o out/arr/simulation.o

LIST_I = inc/automat_func.h inc/simulation.h inc/types_work.h inc/lists_work.h
LIST_O = out/types_work.o out/lists_work.o out/automat_func.o out/simulation.o

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_I) $(ALL_O)
	$(CC) -o $@ $(ALL_O)