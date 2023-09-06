#ifndef ADRESS_WORK_H
#define ADRESS_WORK_H


#include "common.h"

typedef struct adress_stack_node_t adress_stack_node_t;
struct adress_stack_node_t
{
	long int element;
	adress_stack_node_t *next;
};

int add_adresses(adress_stack_node_t **head, long int adress);
void output_adresses(adress_stack_node_t *head);
void free_adresses(adress_stack_node_t **head);

#endif