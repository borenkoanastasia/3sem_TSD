#ifndef NORMAL_MULTIPLICATE_H
#define NORMAL_MULTIPLICATE_H

#include "common.h"
#include "vector.h"
#include "list.h"

int norm_create_matrica(norm_matrix *new_matrica, int rows, int columns);
void norm_free_matrica(norm_matrix *new_matrica);
int norm_get_element_from_matrix_by_i_j(norm_matrix matrica, int i, int j, int *elem);
int norm_put_element_from_matrix_by_i_j(norm_matrix *matrica, int i, int j, int elem);
//Проверка производится при умножении
int norm_multiplicate_matrica_and_matrica(norm_matrix m1, norm_matrix m2, norm_matrix *result);
void norm_output_matrica(norm_matrix m);
int norm_make_rand_matrica(norm_matrix *m, int procent);
int norm_check_matrica(norm_matrix m1, norm_matrix m2);

#endif // NORMAL_MULTIPLICATE_H
