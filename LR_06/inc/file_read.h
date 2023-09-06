#ifndef FILE_READ_H
#define FILE_READ_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERR_CREATE 1
#define ERR_WORK 2
#define ERR_INPUT 3

#define MAX_WORD_LEN 1000

typedef struct data_array data_array_t;
struct data_array
{
	char **pointers;
	int len;
};


int read_file(char *filename, data_array_t *data);
void output_data(data_array_t data);

#endif