#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>

#define OK 0
#define ERROR_NO_FILE 1
#define ERROR_STRUCT 2
#define ERROR_ARGS 3
#define ERROR_FILE 4

#define MAX_FILENAME_LEN 30
#define MAX_STRUCT_COUNT 100
#define MIN_STRUCT_COUNT 40

#define MAX_NAME_LEN 30
#define MAX_PEOPLE_AMOUNT 7600000000
#define MAX_CAP_LEN 30

#define MAX_EXURSION_MONUMENTS_COUNT 2000000000

#define MIN_TEMPERATURE 0
#define MAX_TEMPERATURE 70
#define MAX_TIME_TRAVEL 7200

#define MAX_SPORT_MIN_PRICE 2000000000

#define MAX_STRING_FIELD_LEN 30
#define MAX_AMOUNT_VARIANTS 7

struct excursion{
    long int monument_count;
    char main_type[MAX_STRING_FIELD_LEN];
};

struct beach_front{
    char season[MAX_STRING_FIELD_LEN];
    int temperature_air;
    int temperature_water;
    int time_travel;
};

struct sport{
    char type_sport[MAX_STRING_FIELD_LEN];
    long int min_price;
};

typedef struct excursion excursion;
typedef struct beach_front beach_front;
typedef struct sport sport;

union type_tourism{
    excursion excursion;
    beach_front beach;
    sport sport;
};

typedef union type_tourism type_tourism;

struct countries{
    char name[MAX_STRING_FIELD_LEN];
    long long unsigned int people_amount;
    char capital[MAX_STRING_FIELD_LEN];
    char mainland[MAX_STRING_FIELD_LEN];
    char tourism_type[MAX_STRING_FIELD_LEN];
    type_tourism description;
};

typedef struct countries countries;

struct key{
    int index;
    char name[MAX_STRING_FIELD_LEN];
};

typedef struct key key;

#endif // COMMON_H
