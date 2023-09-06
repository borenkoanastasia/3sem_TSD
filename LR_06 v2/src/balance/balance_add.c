#include "../../inc/balance_work.h"

int add_balance_node_in_tree(tree_node_t **root, tree_node_t *new_node)
{
	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}
	printf("root = %s\n", (*root)->word);

	// Если корень существует ищем ближайший в дереве узел для нового слова
	if (strcmp((*root)->word, new_node->word) < 0)
	{
		//printf("RIGHT\n");
		if ((*root)->right == NULL)
		{
			(*root)->right = new_node;
			new_node->height = 1;
			new_node->parent = (*root)->right;
			fix_height(root);
			printf("INIT\n");
			printf("root = %s, new_node = %s, new_node height = %d\n", 
				(*root)->word, new_node->word, new_node->height);
		}
		else
		{
			//fix_height(root);
			add_balance_node_in_tree(&(*root)->right, new_node);
			balance(root);
			fix_height(root);
		}
	}
	else if (strcmp((*root)->word, new_node->word) > 0)
	{
		//printf("LEFT\n");
		if ((*root)->left == NULL)
		{
			(*root)->left = new_node;
			new_node->height = 1;
			new_node->parent = (*root)->left;
			fix_height(root);
			//printf("INIT\n");
			//printf("root = %s, new_node = %s, new_node height = %d\n", 
			//	(*root)->word, new_node->word, new_node->height);
		}
		else
		{
			//fix_height(root);
			add_balance_node_in_tree(&(*root)->left, new_node);
			fix_height(root);
			balance(root);
		}
	}
	else
	{
	//printf("Success else\n");
		//printf("Такой узел уже существует %s\n", (*root)->word);
		return ERR_WORK;
	}
	//printf("start balance\n");
	balance(root);
	//printf("end balance\n");

	return OK;
}

int add_balance_node(tree_node_t **root, char *element)
{
	// Создаем узел
	tree_node_t *new_node = NULL;
	int rc = create_tree_node(&new_node, element);
	if (rc != OK)
		return ERR_CREATE;
	add_balance_node_in_tree(root, new_node);
	return OK;
}
