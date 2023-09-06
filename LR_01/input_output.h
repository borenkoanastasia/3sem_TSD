#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include "common.h"

#define INOUT_OK 0
#define INOUT_ERROR_LONG_MANTISSA 1
#define INOUT_ERROR_LONG_ORDER 2
#define INOUT_ERROR_BAD_LINE 3
#define INOUT_ERROR_EMPTY_MANTISSA 4
#define INOUT_NOT_END_READING 5
#define INOUT_ERROR_LONG_ORDER_CALC 6

int read_first_number(fns *number);
int output_first_number(fns number);
int read_second_number(sns *number);
void output_error_message(int rc);
void output_second_num(sns first_num);
void output_start_first_num_message();
void output_start_second_num_message();
#endif // INPUT_OUTPUT_H
