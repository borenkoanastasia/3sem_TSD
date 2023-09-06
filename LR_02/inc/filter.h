#ifndef FILTER_H
#define FILTER_H

#include "testing.h"
#include "check_fields.h"
#include "key_array.h"
#include "struct_array.h"
#include "help_functions.h"
#include "testing.h"
#include "file.h"

int input_filters_fields(char mainland[MAX_STRING_FIELD_LEN],
                          char sport_type[MAX_STRING_FIELD_LEN]);
void output_filter_results(char mainland[MAX_STRING_FIELD_LEN],
                           char sport_type[MAX_STRING_FIELD_LEN],
                           countries table[MAX_STRUCT_COUNT], int len);

#endif // FILTER_H
