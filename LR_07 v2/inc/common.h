#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERR_ARGS 1
#define ERR_WORK 2
#define ERR_INPUT 3
#define ERR_OPEN_FILE 4
#define ERR_CREATE 5
#define COUNT_REPEAT 100000

#define TRUE 1
#define FALSE 0


typedef int peak_name_t;

typedef struct edge edge_t;
typedef struct graph graph_t;
typedef struct edges_array edges_array_t;
typedef struct peaks_array peaks_array_t;

struct edge
{
	int p1;
	int p2;
};

struct edges_array
{
	edge_t *elements;
	int len;
};

struct peaks_array
{
	int *elements;
	int len;
};

struct graph
{
	edges_array_t *edges;
	peaks_array_t *peaks;
};

#endif
