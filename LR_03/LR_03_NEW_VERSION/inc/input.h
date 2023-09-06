#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "normal_matrica.h"
#include "press_matrica.h"


#define MANNUALY 1
#define RANDOM 2
#define GO_AWAY 3

int input_two_norm_matrixes(norm_matrix *m1, norm_matrix *m2);
int input_press_vector_and_matrix(press_matrix *m1, press_matrix *m2);

#endif // INPUT_H
