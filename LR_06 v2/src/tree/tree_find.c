#include "../../inc/tree_work.h"

void find_near_node(tree_node_t **root, char *element, tree_node_t **return_node)
{
	if (*root == NULL)
		return;
	//printf("%s\n", (*root)->word);
	if (strcmp((*root)->word, element) < 0)
	{
		if ((*root)->right == NULL)
		{
			*return_node = (*root);
		}
		else
		{
			find_near_node(&(*root)->right, element, return_node);
		}
	}
	else if (strcmp((*root)->word, element) > 0)
	{
		if ((*root)->left == NULL)
		{
			*return_node = (*root);
		}
		else
		{
			find_near_node(&(*root)->left, element, return_node);
		}
	}
	else
	{
		*return_node = (*root);
	}
}

void find_node_strictly(tree_node_t **root, char *element, tree_node_t **return_node)
{
	find_near_node(root, element, return_node);
	if (strcmp((*return_node)->word, element))
		*return_node = NULL;
}
