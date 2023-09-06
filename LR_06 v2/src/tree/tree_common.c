#include "../../inc/tree_work.h"

//Создание листа
int create_tree_node(tree_node_t **new_node, char *word)
{
	*new_node = calloc(1, sizeof(tree_node_t));
	if (!*new_node)
	{
		printf("Не удалось выделить память под узел дерева\n");
		return ERR_CREATE;
	}
	(*new_node)->parent = NULL;
	(*new_node)->right = NULL;
	(*new_node)->left = NULL;
	(*new_node)->height = 1;
	(*new_node)->word = word;
	return OK;
}

void free_tree_node(tree_node_t **root)
{
	free(*root);
}

void free_tree(tree_node_t **root)
{
	if ((*root)->right)
		free_tree(&(*root)->right);
	if ((*root)->left)
		free_tree(&(*root)->left);
	free_tree_node(root);
}

int fix_height(tree_node_t **root)
{
	int left_height = 1, right_height = 1;
	if ((*root)->left)
		left_height = (*root)->left->height + 1;
	if ((*root)->right)
		right_height = (*root)->right->height + 1;
	(*root)->height = max(left_height, right_height);

	return (*root)->height;
}

int get_balance_factor(tree_node_t *node)
{
	int l_left = 0, l_right = 0;
	if (node->left)
	{
		l_left = node->left->height;
	}
	if (node->right)
	{
		l_right = node->right->height;
	}
	return l_left - l_right;
}

void make_tree_from_data(tree_node_t **root, data_node_t *words)
{
	create_tree_node(root, words->data);
	int i = 0;
	for (data_node_t *cur = words; cur; cur = cur->next, i++)
	{
		//printf("i = %d, word = %s\n", i, cur->data);
		if (cur->data == NULL)
			continue;
		add_tree_node(root, cur->data);
	}
	check_heights(root);
}
void check_heights(tree_node_t **root)
{
	if ((*root)->left)
		check_heights(&(*root)->left);
	if ((*root)->right)
		check_heights(&(*root)->right);
	fix_height(root);
}
