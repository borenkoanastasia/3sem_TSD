#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "../inc/common.h"

typedef struct data_node data_node_t;
typedef struct matrix matrix_t;

struct data_node
{
	char *data;
	data_node_t *next;
};

struct matrix
{
	char **pointers;
	int rows;
	int columns;
};

// HELPERS

int max(int r1, int r2);

// ОБЩИЙ СПИСОК СЛОВ
int add_data_node(data_node_t **list, char *word);
void free_data(data_node_t **list);
void output_data(data_node_t *list);
int get_data_size(data_node_t *data);
char *get_data_word(data_node_t *data, int pos);
void sort_data(data_node_t **data, data_node_t **result);
void copy_data(data_node_t *src, data_node_t **dst);

// STDOUT
void clearInputBuf(void);
void output_line(int size);

// STDIN

int input_word(char **new_el);
int check_word(char *new_element);

// FILE
char *read_word(FILE *file);
int read_file(char *filename, data_node_t **data);

#endif