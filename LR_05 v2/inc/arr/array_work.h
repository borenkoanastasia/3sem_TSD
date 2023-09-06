#ifndef LISTS_WORK_H
#define LISTS_WORK_H

#include "../common.h"
#include "types_work.h"

int create_event_node(events_list_node_t **new, id_t worker, int work, sys_time_t cur_sys_time);
int create_request_node(requests_list_node_t **new, id_t id);
int create_turn_node(turns_list_node_t **new, id_t id);

void delete_event_node(events_list_node_t **new);
void delete_request_node(requests_list_node_t **new);
void delete_turn_node(turns_list_node_t **new);

void add_event_node(request_t **request, events_list_node_t **new);
void add_request_node(turn_t **turn, requests_list_node_t **new);
void add_turn_node(turns_list_node_t **last_turn, turns_list_node_t **new);

requests_list_node_t *remove_request_node(turn_t **turn);

void clear_event_list(events_list_node_t **head);
void clear_request_list(requests_list_node_t **head);
void clear_turn_list(turns_list_node_t **head);


#endif
