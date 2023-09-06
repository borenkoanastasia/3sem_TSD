#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define OK 0
#define ERR_CREATE 1
#define ERR_INPUT 2
#define AUTO 3
#define MANUALLY 4

#define MAX_NUM 10

typedef struct vector vector;
typedef struct press_matrix_t press_matrix_t;
typedef struct norm_matrix_t norm_matrix_t;

struct vector
{
	int *elements;
	int size;
};

struct press_matrix_t
{
	vector a;
	vector ia;
	vector ja;
};

struct norm_matrix_t
{
	int **pointers;
	int rows;
	int columns;
};

#endif