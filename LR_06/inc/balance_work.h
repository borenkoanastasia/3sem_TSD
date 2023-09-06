#ifndef BALANCE_WORK_H
#define BALANCE_WORK_H

#include "tree_work.h"

typedef struct balance_tree_node balance_tree_node_t;

struct balance_tree_node
{	
	int len_left;
	int len_right;
	char *data;
	balance_tree_node_t *left;
	balance_tree_node_t *right;
};

void make_balance_tree_from_data(balance_tree_node_t **root, data_array_t data);

#endif