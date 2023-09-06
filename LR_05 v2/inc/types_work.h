#ifndef TYPES_WORK_H
#define TYPES_WORK_H

#include "common.h"

int create_event(event_t **new, id_t worker, int work, sys_time_t cur_sys_time);
int create_request(request_t **new, id_t id);
int create_turn(turn_t **new, id_t id);
int create_automat(automat_t **new, id_t id, sys_time_t tmin, sys_time_t tmax, turns_list_node_t *next_turns, 
	turn_t *(*beat)(turns_list_node_t *next_turns));

void delete_event(event_t **event);
void delete_request(request_t **request);
void delete_turn(turn_t **turn);
void delete_automat(automat_t **automat);


void output_events(events_list_node_t *head);
void output_turn(turn_t t, int buf);
void output_automat(automat_t a1);
void output_all(automat_t a1, automat_t a2, turn_t t1, turn_t t2, sys_time_t system_time);


#endif
