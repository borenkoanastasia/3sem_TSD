#ifndef SORT_H
#define SORT_H

#include "stack_work.h"

int array_sort(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3, 
	adress_stack_node_t **h);
int list_sort(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3, 
	adress_stack_node_t **h);

#endif