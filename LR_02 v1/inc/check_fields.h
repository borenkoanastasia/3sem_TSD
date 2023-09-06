#ifndef CHECK_FIELDS_H
#define CHECK_FIELDS_H

#include "common.h"

#define CHECK_FIELD_BAD 0
#define CHECK_FIELD_GOOD 1
#define BAD_NAME 2

int check_field_name(char *string, countries table[MAX_STRUCT_COUNT], int len);
int check_field_people_amount(long long unsigned int people_amount);
int check_field_capital(char *string);
int check_field_mainland(char *string);
int check_field_tourism_type(char *string);
int check_field_exursion_main_type(char *string);
int check_field_exursion_monument_count(long int count);
int check_field_sport_type(char *string);
int check_field_sport_min_price(long int price);
int check_field_beach_season(char *string);
int check_field_beach_temperature_air(int t);
int check_field_beach_temperature_water(int t);
int check_field_beach_time_travel(int t);

int check_table_by_name(countries table[MAX_STRUCT_COUNT], int len);

#endif // CHECK_FIELDS_H
