#ifndef NORM_MATRIX_H
#define NORM_MATRIX_H

#include "common.h"
#include "create.h"

//int nm_get_el_matrix(norm_matrix_t matrica, int i, int j, int *elem);
//int nm_put_el_matrix(norm_matrix_t *matrica, int i, int j, int elem);

int nm_get_col_matrix(norm_matrix_t matrica, int column_num, vec_t *column);
int nm_get_row_matrix(norm_matrix_t matrica, int row_num, vec_t *row);

int nm_multiply_row_and_col(vec_t row, vec_t column, int *res_elem);
int norm_multiply_vec_and_matrica(norm_matrix_t m_row, norm_matrix_t matrix, norm_matrix_t *result);

int nm_check_matrix(norm_matrix_t m1, norm_matrix_t m2);

int norm_make_rand_matrica(norm_matrix_t *m, int procent);

void nm_make_matrix_zero(norm_matrix_t *nm);

#endif // NORM_MATRIX_H