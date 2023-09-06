#ifndef LIST_MODEL_H
#define LIST_MODEL_H

#include "help_functions.h"

typedef struct list_turn_t list_turn_t;


// Очередь
struct list_turn_t
{
	int id;
	list_node_t *pout;
	list_node_t *pin;
	int len;
	average_t time_av;
	average_t len_av;
};

int list_create_turn(list_turn_t **turn, int id);
void list_delete_turn(list_turn_t **turn);
void list_start_fill_turn(list_turn_t **turn);
list_node_t *list_find_turn_by_id(list_node_t *head, int turn_id);

void list_prepearing_turns(list_turn_t **t1, list_turn_t **t2);
void list_prepearing_automats(automat_t *a1, automat_t *a2, list_turn_t **t1, list_turn_t **t2);

my_time_t list_modeling(list_turn_t **t1, list_turn_t **t2, automat_t *a1, automat_t *a2, int condition);

intermediat_result_t *get_list_intermediate(void *turn);
my_time_t list_get_average_time(void *turn);

#endif