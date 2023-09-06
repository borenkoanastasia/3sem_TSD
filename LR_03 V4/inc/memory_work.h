#ifndef MEMORY_WORK_H
#define MEMORY_WORK_H

#include "common.h"

int create_vector(vector *n, int size);

void free_vector(vector *n);
void output_vector(vector n);

int create_press_matrix(press_matrix_t *n, int col_count, int el_count);
void free_press_matrix(press_matrix_t *m);
void output_press_matrix(press_matrix_t m);

int create_norm_matrix(norm_matrix_t *m, int rows, int columns);
void free_norm_matrix(norm_matrix_t *m);
void output_norm_matrix(norm_matrix_t m);

void clearInputBuf(void);

#endif