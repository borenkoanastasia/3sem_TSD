#ifndef LIST_H
#define LIST_H

#include "common.h"

list_el *new_elem_add_end(list_el *head, list_el *new_el);
int create_list_el(list_el **el);
void free_list_el(list_el *el);
void free_list(list_el *head);

#endif // LIST_H
