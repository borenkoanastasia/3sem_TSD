#ifndef INPUT_DATA_H
#define INPUT_DATA_H

#include "common.h"
#include "check_fields.h"
#include "help_functions.h"

#define INPUT_OK 0
#define INPUT_ERROR 1
#define INPUT_NOT_INDIVIDUAL_NAME 2

#define INPUT_ERROR_MAX_STRING_LEN 3

int input_name(char name[MAX_STRING_FIELD_LEN], countries table[MAX_STRUCT_COUNT], int len);
int input_people_amount(long long unsigned int *people_amount);
int input_capital(char capital[MAX_STRING_FIELD_LEN]);
int input_mainland(char mainland[MAX_STRING_FIELD_LEN]);
int input_tourism_type(char tourism_type[MAX_STRING_FIELD_LEN]);

int input_excursion_main_type(char main_type[MAX_STRING_FIELD_LEN]);
int input_excursion_monuments_count(long int *monuments_count);

int input_beach_season(char season[MAX_STRING_FIELD_LEN]);
int input_beach_temperature_air(int *temperature_air);
int input_beach_temperature_water(int *temperature_water);
int input_beach_time_travel(int *time_travel);

int input_sport_main_type(char main_type[MAX_STRING_FIELD_LEN]);
int input_sport_min_price(long int *time_travel);

int input_country(countries *elem, countries table[MAX_STRUCT_COUNT], int len);

#endif // INPUT_DATA_H
