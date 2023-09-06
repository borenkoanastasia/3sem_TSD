#ifndef AUTOMAT_FUNC_H
#define AUTOMAT_FUNC_H

#include "common.h"
#include "lists_work.h"

turns_list_node_t *find_turn_by_id(turns_list_node_t *next_turns, id_t find_turn_id);
turn_t *beat1(turns_list_node_t *next_turns);
turn_t *beat2(turns_list_node_t *next_turns);
sys_time_t random_time(sys_time_t tmin, sys_time_t tmax);
int start_fill_turn_1(turn_t *turn);

#endif