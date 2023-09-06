#ifndef START_WORK_H
#define START_WORK_H

#include "common.h"

int add_free_adress(adress_stack_node_t **head, long int adress);
void output_free_adresses(adress_stack_node_t *head);
void free_free_adresses(adress_stack_node_t **head);

int list_push(list_stack_node_t **head, int new_el);
void list_pop(list_stack_node_t **head, adress_stack_node_t **h);
void list_free(list_stack_node_t **head);
void list_output_stack(list_stack_node_t *stack);

int array_create_stack(array_stack_t *stack, int len);
int array_push(array_stack_t *stack, int element);
int array_pop(array_stack_t *stack, adress_stack_node_t **h);
void array_stack_free(array_stack_t *stack);
void array_output_stack(array_stack_t stack);

#endif