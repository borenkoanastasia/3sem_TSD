#ifndef PRESS_MATRICA_H
#define PRESS_MATRICA_H

#include "normal_matrica.h"

int press_norm_matrica_to_press(norm_matrix nm, press_matrix *pm);
void press_output_matrica(press_matrix m);
int press_create_matrix(press_matrix *m, int a_size, int ia_size, int ja_size);
void press_free_matrica(press_matrix *p);
//int press_make_rand_matrica(press_matrix *m, int procent, int rows, int columns);

int press_multiplicate_vector_to_matrica(press_matrix vector, press_matrix matrica,
                                          press_matrix *result);
void press_matrica_output_as_normal(press_matrix pm);

int press_check_matrica(press_matrix a, press_matrix b);
int get_column_count(list_el *head);

#endif // PRESS_MATRICA_H
