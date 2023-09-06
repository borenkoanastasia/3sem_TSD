#ifndef FILEWORK_H
#define FILEWORK_H

#include "common.h"
#include "check_fields.h"

#define FILEWORK_OK 0
#define FILEWORK_ERROR_NO_FILE 1
#define FILEWORK_ERROR_NAME 2
#define FILEWORK_ERROR_PEOPLE_AMOUNT 3
#define FILEWORK_ERROR_CAPITAL 4
#define FILEWORK_ERROR_MAINLAND 5
#define FILEWORK_ERROR_TOURISM_TYPE 6
#define FILEWORK_ERROR_EXCURSION_MAIN_TYPE 7
#define FILEWORK_ERROR_EXCURSION_MONUMENT_AMOUNT 8
#define FILEWORK_ERROR_BEACH_SEASON 9
#define FILEWORK_ERROR_BEACH_TEMPERATURE_AIR 10
#define FILEWORK_ERROR_BEACH_TEMPERATURE_WATER 11
#define FILEWORK_ERROR_BEACH_TIME_TRAVEL 12
#define FILEWORK_ERROR_SPORT_TYPE 13
#define FILEWORK_ERROR_SPORT_MIN_PRICE 14

#define FILEWORK_ERROR_READING 15

#define FILEWORK_ERROR_LONG_FIELD 16

#define  FILEWORK_ERROR_BAD_NAME 17

int read_file_to_struct(char *filename, countries arr[MAX_STRUCT_COUNT], int *len);
void filework_output_error_messages(int rc);
int read_field_char(FILE *file, char field[MAX_STRING_FIELD_LEN]);
int read_line(FILE *file, countries *line);

void write_table_in_file(char file_name[MAX_FILENAME_LEN], countries table[MAX_STRUCT_COUNT],
                   int len);

#endif // FILEWORK_H
