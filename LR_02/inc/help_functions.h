#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "common.h"


// keys = 's', 'e', 'p', 'm', 't'
// s - seasons, e - exursions type, p - sport types, m - mainlands, t - tourism types
// res_arr - [7][MAX_MAINLAND]
void get_variants_value_by_key(char key, int *len, char res_arr[7][MAX_STRING_FIELD_LEN]);

// Возвращает индекс искомого элемента или возвращает -1
int search_struct_by_name(countries struct_arr[MAX_STRUCT_COUNT],
                          char key[MAX_STRING_FIELD_LEN], int len);

void make_hours_from_minutes(int minutes, int *res_minutes, int *hours);
void make_minutes_from_hours(int *res_minutes, int minutes, int hours);
void clear_string(char *string, int len);
void clear_contries(countries *elem);

//int get_max(int n1, int n2, int n3, int n4);
int get_max(int n1, int n2);

void copy_countries(countries old_table[MAX_STRUCT_COUNT], countries new_table[MAX_STRUCT_COUNT],
                    int len);

#endif // HELP_FUNCTIONS_H
