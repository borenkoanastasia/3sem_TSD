#ifndef TESTING_H
#define TESTING_H

#include "common.h"
#include "help_functions.h"
#include "key_array.h"
#include "struct_array.h"
#include <time.h>

void test_key_sort(countries table[MAX_STRUCT_COUNT], int len,  int *time, int *memory);
void test_key_quick_sort(countries table[MAX_STRUCT_COUNT], int len, int *time, int *memory);
void test_struct_sort(countries table[MAX_STRUCT_COUNT], int len, int *time, int *memory);
void test_struct_quick_sort(countries table[MAX_STRUCT_COUNT], int len, int *time,
                            int *memory);

#endif // TESTING_H
