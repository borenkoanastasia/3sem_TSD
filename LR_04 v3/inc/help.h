#ifndef HELP_H
#define HELP_H

#include "common.h"

void list_pop(list_stack_node_t **head);
int list_push(list_stack_node_t **head, int new_el);
void list_free(list_stack_node_t **stack);
void list_output_stack(list_stack_node_t *stack);
void list_output_stack_spec(list_stack_node_t *stack);
void list_output_tree_stacks(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3);

int array_create_stack(array_stack_t *stack, int len);
int array_push(array_stack_t *stack, int element);
int array_pop(array_stack_t *stack);
void array_free(array_stack_t *stack);
void array_output_stack(array_stack_t stack);
void array_output_stack_spec(array_stack_t stack);
void array_output_tree_stacks(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3);

void clearInputBuf(void);

void output_line(int size);

#endif