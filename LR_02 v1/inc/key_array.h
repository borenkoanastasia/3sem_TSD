#ifndef KEY_ARRAY_H
#define KEY_ARRAY_H

#include "../inc/common.h"

int key_array_sort(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int len);
void key_array_quick_sort(char arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN], int first_border,
                          int last_border);
void make_key_array_from_struct_array(char key_arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN],
                                     countries struct_arr[MAX_STRUCT_COUNT], int len);

void key_array_output_table(char key_arr[MAX_STRUCT_COUNT][MAX_STRING_FIELD_LEN],
                            countries struct_arr[MAX_STRUCT_COUNT], int len);
#endif // KEY_ARRAY_H
