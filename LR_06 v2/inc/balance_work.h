#ifndef BALANCE_WORK_H
#define BALANCE_WORK_H

#include "../inc/common.h"
#include "../inc/tree_work.h"

void right_rotate(tree_node_t **root);
void left_rotate(tree_node_t **root);
void balance(tree_node_t **root);
void make_balanced_tree_from_data(tree_node_t **root, data_node_t *data);

void make_by_add_balanced_tree_from_data(tree_node_t **root, data_node_t *data);
int add_balance_node(tree_node_t **root, char *element);
void balanced_menu();
#endif