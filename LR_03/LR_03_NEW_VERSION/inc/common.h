#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ELEM 10

#define OK 0
#define ERROR_CREATE 1
#define ERROR_DIFFERENT_MATRIX 2
#define ERROR_INDEX_NOT_IN_MATRIX 3
#define ERROR_INDEX_NOT_IN_VECTOR 4
#define ERROR_INPUT 5

typedef struct vector vector;
typedef struct norm_matrix norm_matrix;
typedef struct press_matrix press_matrix;
typedef struct list_el list_el;

struct list_el
{
    int value;
    list_el *next;
};

struct vector
{
    int *elements;
    int size;
};

struct norm_matrix
{
    int *elements;
    int rows;
    int columns;
};

struct press_matrix
{
    vector a;
    vector ia;
    list_el *ja_head;
};

void output_error_message(int rc);

#endif // COMMON_H
