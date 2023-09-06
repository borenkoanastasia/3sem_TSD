#ifndef CHOISES_H
#define CHOISES_H

#include "common.h"
#include "press_matrica.h"
#include "normal_matrica.h"

#define MANNUALY 1
#define RANDOM 2
#define GO_AWAY 3

void output_work_normal_matrixes(norm_matrix a, norm_matrix b);
void output_work_press_matrixes(press_matrix a, press_matrix b);
int input_manually_or_random();
int input_press_matrica_elements_columns(int *elem_count, int *columns);
int input_press_matrica_ja(press_matrix *m, int columns, int elem_count);
int input_press_matrica_a_ia(press_matrix *m, int elem_counts, int vector_condition);
void input_press_matrica_manually(press_matrix *m, int vector_condition);
int input_norm_matrica_size(int *rows, int *columns);
int input_norm_vector_size(int *columns);
int input_norm_matrica_elements(norm_matrix *m);
void input_norm_matrica_manually(norm_matrix *m);
int input_procent(int *procent);
void input_press_matrica_random(press_matrix *m, int vector_condition);
void input_norm_matrica_random(norm_matrix *m);

#endif // CHOISES_H
