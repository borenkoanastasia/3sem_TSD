#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"

#define OK 0
#define ERROR_CREATE 1

int create_vector(vector *vec, int size);
void free_vector(vector *vec);
void output_vector(vector v);

#endif // VECTOR_H
