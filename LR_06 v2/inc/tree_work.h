#ifndef TREE_WORK_H
#define TREE_WORK_H

#include "../inc/common.h"
#include "../inc/help_functions.h"

typedef struct tree_node tree_node_t;

struct tree_node
{
	tree_node_t *parent;
	tree_node_t *right;
	tree_node_t *left;
	int height;
	char *word;
};

// COMMON

void check_heights(tree_node_t **root);
int create_tree_node(tree_node_t **new_node, char *word);
void free_tree_node(tree_node_t **root);
void free_tree(tree_node_t **root);

int fix_height(tree_node_t **root);
int get_balance_factor(tree_node_t *node);
void find_near_node(tree_node_t **root, char *element, tree_node_t **return_node);
int add_tree_node(tree_node_t **root, char *element);
void make_tree_from_data(tree_node_t **root, data_node_t *array);

// FIND
void find_node_strictly(tree_node_t **root, char *element, tree_node_t **return_node);

// DELETE
int delete_tree_node(tree_node_t **root, char *element); // дописать

// OUTPUT
void output_tree_as_dot(tree_node_t *root, char *filename);

void tree_menu();
#endif