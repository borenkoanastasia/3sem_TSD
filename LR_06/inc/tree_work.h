#ifndef TREE_WORK_H
#define TREE_WORK_H

#include "file_read.h"

typedef struct tree_node tree_node_t;
struct tree_node
{
	char *data;
	tree_node_t *left;
	tree_node_t *right;
};

int create_tree_node(tree_node_t **root, char *string);
void make_tree_from_data(tree_node_t **root, data_array_t data);

#endif