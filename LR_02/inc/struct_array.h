#ifndef STRUCTWORK_H
#define STRUCTWORK_H

#include "common.h"

#define STRUCTWORK_OK 0
#define STRUCTWORK_ERROR_MIN_COUNT 1
#define STRUCTWORK_ERROR_MAX_COUNT 2

int struct_array_sort(countries arr[MAX_STRUCT_COUNT], int len);

int struct_array_sort_with(countries arr[MAX_STRUCT_COUNT], int len, size_t *size);
void struct_array_quick_sort(countries arr[MAX_STRUCT_COUNT], int first_border,
                             int last_border);

void struct_array_quick_sort_with(countries arr[MAX_STRUCT_COUNT], int first_border,
                                  int last_border, size_t *size);

int add_struct(countries arr[MAX_STRUCT_COUNT], int *len, countries add_element);
int del_struct(countries arr[MAX_STRUCT_COUNT], int *len, char name[MAX_STRING_FIELD_LEN]);

void output_table(countries result[MAX_STRUCT_COUNT], int len);
void output_title();
void output_countries_type(countries line);

#endif // STRUCTWORK_H
