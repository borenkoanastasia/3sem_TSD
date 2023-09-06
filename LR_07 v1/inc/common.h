#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR_ARGS 1
#define ERR_WORK 2
#define ERR_INPUT 3

#define FLAG_BLACK 0
#define FLAG_RED 1
#define FLAG_BLUE 2

#define PEAKS_SPACE "\t\t"
#define EDGES_SPACE "\t\t"

#define DIRRECT_1_2 '>'
#define DIRRECT_2_1 '<'
#define DIRRECT_all '-'

#define CONNECT_TRUE 0
#define CONNECT_FALSE 1

typedef int peak_name_t;

typedef struct stack stack_t;

struct stack
{
	peak_name_t *current;
	peak_name_t *start;
	peak_name_t *end;
};

typedef struct list list_t;

struct list
{
	void *element;
	list_t *next;
};

typedef struct edge edge_t;
typedef struct graph graph_t;

struct edge
{
	int p1;
	int p2;
};

struct graph
{
	list_t *edges;
	int len;
};

#endif
