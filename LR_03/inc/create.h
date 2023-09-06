#ifndef CREATE_H
#define CREATE_H

#include "common.h"
#include "norm_matrix.h"

int create_norm_matrix(norm_matrix_t *nm, int rows, int columns);
void free_norm_matrix(norm_matrix_t *nm);
void output_norm_matrix(norm_matrix_t nm);

int create_vector(vec_t *vec, int size);
void free_vector(vec_t *vec);
void output_vector(vec_t vec);

int create_press_matrix(press_matrix_t *pm, int a_size, int ja_size);
void free_press_matrix(press_matrix_t *pm);
void output_press_matrix(press_matrix_t pm);

#endif // CREATE_H