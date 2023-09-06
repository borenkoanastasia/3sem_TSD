#ifndef TURN_WORK_H
#define TURN_WORK_H

#include "common.h"
#include "adress_work.h"
#include "help_functions.h"

typedef struct tw_node tw_node;
typedef struct tw_list tw_list;
typedef struct tw_array tw_array;

struct tw_node
{
	int element;
	tw_node *next;
};

struct tw_list
{
	tw_node *pin;
	tw_node *pout;
};

struct tw_array
{
	int size;
	int *pin;
	int *pout;
};

int tw_list_push(tw_list *turn, int element);
int tw_list_pop(tw_list *turn, adress_stack_node_t **head);
void tw_list_free(tw_list *turn, adress_stack_node_t **head);

int tw_array_create(tw_array *turn, int size);
int tw_array_push(tw_array *turn, int element);
int tw_array_pop(tw_array *turn);
void tw_array_free(tw_array *turn);

void choise_turn_work();
#endif