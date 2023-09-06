#include "../inc/tree_work.h"

int create_tree_node(tree_node_t **root, char *string)
{
	*root = calloc(1, sizeof(tree_node_t));
	if (*root == NULL)
		return ERR_CREATE;
	(*root)->data = string;
	(*root)->left = NULL;
	(*root)->right = NULL;
	return OK;
}

void add_node(tree_node_t **root, char *new_el)
{
	//printf("%s, %s\n", (*root)->data, new_el);
	int rc;
	if (strcmp((*root)->data, new_el) < 0)
	{
		if ((*root)->right == NULL)
		{
			rc = create_tree_node(&((*root)->right), new_el);
			if (rc != OK)
				printf("Ошибка при создании узла\n");
		}
		if ((*root)->right != NULL)
		{
			add_node(&((*root)->right), new_el);
		}
	}
	else if (strcmp((*root)->data, new_el) > 0)
	{
		if ((*root)->left == NULL)
		{
			rc = create_tree_node(&((*root)->left), new_el);
			if (rc != OK)
				printf("Ошибка при создании узла\n");
		}
		if ((*root)->left != NULL)
		{
			add_node(&((*root)->left), new_el);
		}
	}
}

void make_tree_from_data(tree_node_t **root, data_array_t data)
{
	create_tree_node(root, data.pointers[0]);
	char *new_el;
	for (int i = 0;i < data.len; i++)
	{
		new_el = data.pointers[i];
		//printf("%d\n", i);
		add_node(root, new_el);
	}
}
