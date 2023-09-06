#ifndef OUTPUT_H
#define OUTPUT_H

#include "common.h"

struct results_100_call_A2
{
	int current_len_turn_1;
	int current_len_turn_2;
	int average_len_turn_1;
	int average_len_turn_2;
};

struct results_ending_simulation
{
	sys_time_t system_time;
	sys_time_t downtime_a2;
	int call_count_a1;
	int average_request_time_in;
};

#endif