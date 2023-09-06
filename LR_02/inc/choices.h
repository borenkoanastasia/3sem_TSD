#ifndef CHOICES_H
#define CHOICES_H

#include "common.h"
#include "input_data.h"
#include "struct_array.h"
#include "filter.h"

void add_country(countries table[MAX_STRUCT_COUNT], int *len);
void del_country(countries table[MAX_STRUCT_COUNT], int * len);
void choice_filter(countries table[MAX_STRUCT_COUNT], int len);

#endif // CHOICES_H
