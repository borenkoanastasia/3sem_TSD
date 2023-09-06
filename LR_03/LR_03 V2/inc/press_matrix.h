#ifndef PRESS_MATRIX_H
#define PRESS_MATRIX_H

#include "common.h"

void pm_get_el(press_matrix_t pm, int in_i, int in_j, int *elem);

void pm_get_column(press_matrix_t pm, press_matrix_t *column, int in_c);
int pm_multiply_row_and_column(press_matrix_t row, press_matrix_t column);
int get_row_count(press_matrix_t pm);
int pm_miltiply_row_and_matrix(press_matrix_t row, press_matrix_t matrix, press_matrix_t *result);

int get_nm_el_count(norm_matrix_t nm);
int pm_press_nm_to_pm(norm_matrix_t nm, press_matrix_t *pm);

#endif // PRESS_MATRIX_H