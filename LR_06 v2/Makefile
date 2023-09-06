CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_TREE_O = out/tree/tree_add.o out/tree/tree_common.o out/tree/tree_delete.o out/tree/tree_find.o \
out/tree/tree_output.o out/tree/tree_menu.o
ALL_TREE_I = inc/tree_work.h

ALL_HELP_O = out/main.o out/help_functions.o 
ALL_HELP_I = inc/help_functions.h inc/common.h 

ALL_BALANCE_O = out/balance/balance_make.o out/balance/balance_menu.o out/balance/balance_main.o \
out/balance/balance_add.o
ALL_BALANCE_I = inc/balance_work.h 

ALL_HASH_O = src/hash/hash_create.c
ALL_HASH_I = inc/hash_work.h

ALL_O = $(ALL_TREE_O) $(ALL_HELP_O) $(ALL_BALANCE_O) $(ALL_HASH_O) out/testing_trees.o
ALL_I = $(ALL_TREE_I) $(ALL_HELP_I) $(ALL_BALANCE_I) $(ALL_HASH_I) inc/testing_trees.h

out/%.o: src/%.c 
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_I) $(ALL_O)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf out/*.o