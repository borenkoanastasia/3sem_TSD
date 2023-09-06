#include "../../inc/tree_work.h"

tree_node_t *see_left(tree_node_t **root)
{
	tree_node_t *res = NULL;
	//printf("Good see\n");
	//printf("Good start\n", root->left);
	if ((*root)->left)
		res = see_left(&(*root)->left);
	else
		res = *root;
	return res;
}

int delete_tree_node(tree_node_t **root, char *element)
{
	tree_node_t *del_node = NULL, *new_left = NULL, *parent = NULL;
	find_node_strictly(root, element, &del_node);
	if (del_node == NULL)
		return ERR_WORK;
	parent = del_node->parent;

	if (del_node->right)
	{
		new_left = see_left(&del_node->right);
	}
	else if (del_node->left)
	{
		new_left = see_left(&del_node->left);
	}

	if (new_left)
	{
		if (strcmp(new_left->word, new_left->parent->word) > 0)
		{
			new_left->parent->right = new_left->right;
		}
		else
		{
			new_left->parent->left = new_left->right;
		}
		printf("new_left = %s, new_left->parent = %s\n", new_left->word, new_left->parent->word);
		new_left->parent = parent;
		new_left->left = del_node->left;
		new_left->right = del_node->right;
		printf("new_left = %s, new_left->parent = %s\n", new_left->word, new_left->parent->word);
		printf("del_left = %s, del_left->parent = %s\n", del_node->word, del_node->parent->word);
	}
	if (!parent)
	{
		*root = new_left;
		free(del_node);
		return OK;
	}

	if (strcmp(del_node->word, parent->word) < 0)
		parent->left = new_left;
	else
		parent->right = new_left;

	free(del_node);

	return OK;
}