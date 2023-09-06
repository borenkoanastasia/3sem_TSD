#ifndef CONNECTIVITY_H
#define CONNECTIVITY_H

#include "types_work.h"

typedef struct array array_t;

struct array
{
	int *elements;
	int len;
};

typedef struct stack stack_t;

struct stack
{
	int *start;
	int *ps;
	int *end;
};

array_t *create_array(int size);
void delete_array(array_t *s);
void output_array(array_t s);

int check_graph_connectivity(graph_t g);

#endif