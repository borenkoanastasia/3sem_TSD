#ifndef INPUT_H
#define INPUT_H

#include "common.h"
#include "sort.h"
#include "help.h"

int input_array_stack(array_stack_t *stack);
int input_list_stack(list_stack_node_t **head);
int input_type_stack();

#endif