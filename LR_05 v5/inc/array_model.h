#ifndef ARRAY_MODEL_H
#define ARRAY_MODEL_H

#include "help_functions.h"

#define MAX_REQUEST_COUNT 100

typedef struct array_turn_t array_turn_t;

// Очередь
struct array_turn_t
{
	int id;
	request_t *pout;
	request_t *pin;

	request_t *start;
	int max_len;
	
	int len;
	average_t time_av;
	average_t len_av;
};

list_node_t *array_find_turn_by_id(list_node_t *head, int turn_id);

int array_create_turn(array_turn_t **turn, int id);
void array_delete_turn(array_turn_t **turn);
void array_start_fill_turn(array_turn_t **turn);
void array_add_request(array_turn_t **turn, request_t request);
request_t array_remove_request(array_turn_t **turn);
void array_output_turn(array_turn_t t1);

intermediat_result_t *get_array_intermediate(void *turn);
my_time_t array_get_average_time(void *turn);

void array_prepearing_turns(array_turn_t **t1, array_turn_t **t2);
void array_prearing_automats(automat_t *a1, automat_t *a2, array_turn_t **t1, 
							array_turn_t **t2);

void array_output_turn(array_turn_t t1);

my_time_t array_modeling(array_turn_t **t1, array_turn_t **t2, automat_t *a1, automat_t *a2, int condition);

#endif