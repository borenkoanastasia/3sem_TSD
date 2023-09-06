#ifndef OUTPUT_H
#define OUTPUT_H

#include "common.h"
#include "check_fields.h"
#include "key_array.h"
#include "struct_array.h"
#include "help_functions.h"
#include "testing.h"
#include "file.h"
#include "filter.h"
#include "choices.h"

// При выводе не выполняется никаких проверок, поэтому функции вывода ничего не возвращают
// 80 - длина строки в терминале

#define COMMAND_STRING_LEN 80

int make_choise(int choise, countries table[MAX_STRUCT_COUNT], int *len,
                char filename[MAX_FILENAME_LEN]);
void output_menu_message();
void output_start_message();
void output_table_title();

#endif // OUTPUT_H
