#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define OK 0
#define ERR_CREATE -1
#define ERR_INPUT -2
#define ERR_WORK -3
#define ERR_OVERFLOW -4

#define EPS 0.000001

#define SHOW 1
#define NOT_SHOW 2

#define TESTING_REPEATS 100 

#define LIST_TURN 2
#define ARRAY_TURN 1

#define DEBUG 1

#define debug_print(fmt, ...) \
        do { if (fmt) {printf(__VA_ARGS__);}} while (0);

typedef struct average_t average_t;

struct average_t
{
	double sum;
	int count;
};

#endif