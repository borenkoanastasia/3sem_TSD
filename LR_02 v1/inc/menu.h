#ifndef OUTPUT_H
#define OUTPUT_H

#include "common.h"

// При выводе не выполняется никаких проверок, поэтому функции вывода ничего не возвращают

// 80 - длина строки в терминале
#define COMMAND_STRING_LEN 80

int make_choise(int choise, countries table[MAX_STRUCT_COUNT], int *len);

void output_menu_message();
void output_start_message();
void output_end_message();
void output_table_title();
void output_results_testing(int time, int memory);

#endif // OUTPUT_H
