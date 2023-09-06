CC = gcc
CFLAGS = -std=c99 -Wall -Werror -pedantic -linc

S_MAIN = ./src/main.c
S_ST_W = ./src/struct_array/struct_array_work.c
S_ST_S = ./src/struct_array/struct_array_sort.c
S_ST_O = ./src/struct_array/struct_array_output.c
S_F_O = ./src/file/file_output_error_messages.c
S_F_R = ./src/file/file_read.c
S_F_W = ./src/file/file_write.c
S_K_O = ./src/key_array/key_array_work.c
S_K_W = ./src/key_array/key_array_output.c
S_M = ./src/menu.c
S_T = ./src/testing.c
S_H_F = ./src/help_functions.c
S_C_F = ./src/check_fields.c
S_FILTER = ./src/filter.c
S_CHOICES = ./src/choices.c
S_INPUT = ./src/input_data.c

I_COM = ./inc/common.h
I_S = ./inc/struct_array.h
I_F = ./inc/file.h
I_K = ./inc/key_array.h
I_M = ./inc/menu.h
I_T = ./inc/testing.h
I_H_F = ./inc/help_functions.h
I_C_F = ./inc/check_fields.h
I_FILTER = ./inc/filter.h
I_CHOICES = ./inc/choices.h
I_INPUT = ./inc/input_data.h

O_MAIN = ./out/main.o
O_ST_W = ./out/struct_array_work.o
O_ST_S = ./out/struct_array_sort.o
O_ST_O = ./out/struct_array_output.o
O_F_O = ./out/file_output_error_messages.o
O_F_R = ./out/file_read.o
O_F_W = ./out/file_write.o
O_K_O = ./out/key_array_work.o
O_K_W = ./out/key_array_output.o
O_M = ./out/menu.o
O_T = ./out/testing.o
O_H_F = ./out/help_functions.o
O_C_F = ./out/check_fields.o
O_FILTER = ./out/filter.o
O_CHOICES = ./out/choices.o
O_INPUT = ./out/input_data.o

ALL_O = $(O_ST_W) $(O_ST_S) $(O_ST_O) $(O_F_O) $(O_F_R) $(O_K_O) $(O_K_W) $(O_M) $(O_T) $(O_H_F) $(O_C_F) $(O_MAIN) $(O_FILTER) $(O_F_W) $(O_CHOICES) $(O_INPUT)

ALL_I = $(I_COM) $(I_S) $(I_F) $(I_K) $(I_M) $(I_T) $(I_H_F) $(I_C_F) $(I_FILTER) $(I_CHOICES) $(I_INPUT)

all: main.exe 
# unit_tests.exe

# Files from .c to .o

$(O_MAIN): $(S_MAIN) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_MAIN) -c $(S_MAIN)
$(O_ST_W): $(S_ST_W) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_ST_W) -c $(S_ST_W)
$(O_ST_S): $(S_ST_S) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_ST_S) -c $(S_ST_S)
$(O_ST_O): $(S_ST_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_ST_O) -c $(S_ST_O)
$(O_F_O): $(S_F_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_F_O) -c $(S_F_O)
$(O_F_R): $(S_F_R) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_F_R) -c $(S_F_R)
$(O_F_W): $(S_F_W) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_F_W) -c $(S_F_W)
$(O_K_O): $(S_K_O) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_K_O) -c $(S_K_O)
$(O_K_W): $(S_K_W) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_K_W) -c $(S_K_W)
$(O_M): $(S_M) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_M) -c $(S_M)
$(O_T): $(S_T) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_T) -c $(S_T)
$(O_H_F): $(S_H_F) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_H_F) -c $(S_H_F)
$(O_C_F): $(S_C_F) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_C_F) -c $(S_C_F)
$(O_FILTER): $(S_FILTER) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_FILTER) -c $(S_FILTER)
$(O_CHOICES): $(S_CHOICES) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_CHOICES) -c $(S_CHOICES)
$(O_INPUT): $(S_INPUT) $(ALL_I)
	$(CC) $(CFLAGS) -o $(O_INPUT) -c $(S_INPUT)
	

# Files from .o to .exe

main.exe: $(ALL_O) $(ALL_I)
	$(CC) -o main.exe $(ALL_O)



	
#main.o: ./src/main.c ./inc/output.h ./inc/common.h ./inc/filework.h ./inc/structwork.h
#	$(CC) $(CFLAGS) -o ./out/main.o  -c ./src/main.c

#structwork.o: ./inc/structwork.h ./src/structwork.c ./inc/common.h
#	$(CC) $(CFLAGS) -o ./out/structwork.o -c ./src/structwork.c

#output.o: ./src/output.c ./inc/output.h ./inc/common.h
#	$(CC) $(CFLAGS) -o ./out/output.o  -c ./src/output.c
	
#filework.o: ./src/filework.c ./inc/filework.h ./inc/common.h ./inc/output.h
#	$(CC) $(CFLAGS) -o ./out/filework.o  -c ./src/filework.c

#filework_output_error_messages.o: ./src/filework_output_error_messages.c ./inc/filework.h ./inc/common.h 
#	$(CC) $(CFLAGS) -o ./out/filework_output_error_messages.o  -c ./src/#filework_output_error_messages.c

#check_fields.o: ./src/check_fields.c ./inc/check_fields.h ./inc/common.h
#	$(CC) $(CFLAGS) -o ./out/check_fields.o -c ./src/check_fields.c
#

#test_in_output.o: ./src/test_in_output.c ./inc/output.h ./inc/common.h
#	$(CC) $(CFLAGS) -o ./out/test_in_output.o  -c ./src/test_in_output.c 
	
#test_filework.o: ./src/test_filework.c ./inc/output.h ./inc/common.h ./inc/filework.h
#	$(CC) $(CFLAGS) -o ./out/test_filework.o  -c ./src/test_filework.c 

#main.exe: main.o output.o structwork.o filework.o check_fields.o
#	$(CC) -o main.exe out/main.o out/output.o out/structwork.o out/filework.o out/check_fields.o

#test_in_output.exe: test_in_output.o output.o
#	$(CC) -o test_in_output.exe ./out/test_in_output.o ./out/output.o

#test_filework.exe: test_filework.o output.o check_fields.o filework_output_error_messages.o filework.o
#	$(CC) -o test_filework.exe ./out/test_filework.o ./out/output.o ./out/filework.o ./out/#filework_output_error_messages.o ./out/check_fields.o


