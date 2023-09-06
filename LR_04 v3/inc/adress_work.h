#ifndef ADRESS_WORK_H
#define ADRESS_WORK_H

#include "common.h"

int add_adresses(adress_stack_node_t **head, long int adress);
void output_adresses(adress_stack_node_t *head);
void free_adresses(adress_stack_node_t **head);

#endif