#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK 0
#define ERROR_INCORRECT_OUTPUT 1
#define ERROR_LONG_MANTISSA 2
#define ERROR_LONG_ORDER 3
#define ERROR_RESULT_LOG_ORDER 4

#define MAX_MANTISSA_LEN 30
#define MAX_ORDER_LEN 5

#define DIGITS(x) strchr("1234567890", x)
#define SEP(x) strchr("Ee\n", x)

struct first_number
{
    char mantissa[MAX_MANTISSA_LEN + 1]; //число хранится задом наперед
    //int point_position;
    char sign;
    long int order;
};

struct second_number
{
    char num[MAX_MANTISSA_LEN + 1]; //число хранится задом наперед
    char sign;
};

typedef struct first_number  fns;
typedef struct second_number  sns;
#endif // COMMON_H
