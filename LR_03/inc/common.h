#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERROR_CALC 1
#define ERROR_INPUT 2
#define ERROR_CREATE 3
#define ERROR_TEST -1

#define MAX_ELEM 100

typedef struct vec_t vec_t;
typedef struct norm_matrix_t norm_matrix_t;
typedef struct press_matrix_t press_matrix_t;

struct vec_t
{
    int *elements;
    int size;
};

struct norm_matrix_t
{
    int **pointers;
    int rows;
    int columns;
};

struct press_matrix_t
{
    vec_t a;
    vec_t ia;
    vec_t ja;
};

void output_error_message(int rc);

#endif // COMMON_H