#ifndef COMMON_H
#define COMMON_H

#define OK 0
#define ERR_CREATE 1

#define MAX_OA2_TASKS 1000
#define START_OA1_TASKS 100

#define NEXT_OA1 1
#define NEXT_OA2 2

#define EPS 0.000001

typedef struct turn_node_t turn_node_t;
typedef struct turn_t turn_t;
typedef struct average_t average_t;
typedef struct simulation_100_result_t simulation_100_result_t;

struct turn_node_t
{
	int *element;
	turn_node_t *next;
};

struct average_t
{
	long int summ;
	int el_count;
};

struct turn_t
{
	turn_node_t *pin;
	turn_node_t *pout;
	int len;
	average_t ;
};

struct simulation_100_result_t
{
	int cur_oa1_len;
	int cur_oa2_len;
	int average_oa1_len;
	int average_oa2_len;
};

struct simulation_1000_result_t
{
	int cur_oa1_len;
	int cur_oa2_len;
	int average_oa1_len;
	int average_oa2_len;

	int oa1_tasks;
	int oa2_down_time;
	int result_time;
};

#endif