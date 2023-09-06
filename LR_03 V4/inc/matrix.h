#ifndef NORM_MATRIX_H
#define NORM_MATRIX_H

#include "common.h"
#include "memory_work.h"

int norm_multiplicate_vec_and_matrix(norm_matrix_t n1, norm_matrix_t n2, norm_matrix_t *res);
int norm_make_rand_matrix(norm_matrix_t *m, int rows, int columns, int procent);
//int get_elements_count(norm_matrix n);
int press_norm_matrix(norm_matrix_t n, press_matrix_t *p);
int press_multiplicate_vec_and_matrix(press_matrix_t m1, press_matrix_t m2, press_matrix_t *res);

#endif