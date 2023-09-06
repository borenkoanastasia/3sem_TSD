#ifndef KEY_ARRAY_H
#define KEY_ARRAY_H

#include "common.h"
#include "help_functions.h"

int key_array_sort_with(key arr[MAX_STRUCT_COUNT], int len, size_t *size);
int key_array_sort(key arr[MAX_STRUCT_COUNT], int len);

void key_array_quick_sort(key arr[MAX_STRUCT_COUNT], int first_border, int last_border);
void make_key_array_from_struct_array(key key_arr[MAX_STRUCT_COUNT],
                                     countries struct_arr[MAX_STRUCT_COUNT], int len);
void key_array_quick_sort_with(key arr[MAX_STRUCT_COUNT],
                               int first_border, int last_border, size_t *size);

void key_array_output_table(key key_arr[MAX_STRUCT_COUNT],
                            countries struct_arr[MAX_STRUCT_COUNT], int len);
#endif // KEY_ARRAY_H
