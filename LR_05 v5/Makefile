CC = gcc
CFLAGS = -std=c99 -Wall -Werror

ALL_I = inc/common.h inc/list_model.h inc/help_functions.h inc/array_model.h inc/experiment.h inc/adress_work.h inc/testing.h\
inc/turn_work.h
ALL_O = out/list_type_work.o out/list_model.o out/main.o out/help_functions.o \
out/array_type_work.o out/array_model.o out/experiment.o out/adress_work.o out/testing.o out/turn_work.o #out/menu.o

out/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

app.exe: $(ALL_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $@ $(ALL_O)

clean: 
	rm -rf *.exe out/*.o
