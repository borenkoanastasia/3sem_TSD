#include "../../inc/tree_work.h"


int add_tree_node(tree_node_t **root, char *element)
{
	tree_node_t *new_node = NULL, *found_node = NULL;
	int rc;
	//printf("OK");

	// Если корень существует ищем ближайший в дереве узел для нового слова
	if (*root)
	{
		find_near_node(root, element, &found_node);
		if (!strcmp(found_node->word, element))
			return ERR_WORK;
	}

	// Создаем узел
	rc = create_tree_node(&new_node, element);
	if (rc != OK)
		return rc;

	//printf("OK");
	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}
	//printf("OK");

	// Заполняем параметры узла
	if (strcmp(found_node->word, element) < 0)
		found_node->right = new_node;
	else
		found_node->left = new_node;

	new_node->parent = found_node;

	return OK;
}
