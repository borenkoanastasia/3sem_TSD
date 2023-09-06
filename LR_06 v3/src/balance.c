#include "../inc/balance_work.h"

int add_balance_node_in_tree(tree_node_t **root, tree_node_t *new_node)
{
	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}

	// Если корень существует ищем ближайший в дереве узел для нового слова
	if (strcmp((*root)->word, new_node->word) < 0)
	{
		if ((*root)->right == NULL)
		{
			(*root)->right = new_node;
			new_node->height = 1;
			//new_node->parent = (*root)->right;
			fix_height(root);
		}
		else
		{
			add_balance_node_in_tree(&(*root)->right, new_node);
			//balance(root);
			fix_height(root);
		}
	}
	else if (strcmp((*root)->word, new_node->word) > 0)
	{
		if ((*root)->left == NULL)
		{
			(*root)->left = new_node;
			new_node->height = 1;
			//new_node->parent = (*root)->left;
			fix_height(root);
		}
		else
		{
			add_balance_node_in_tree(&(*root)->left, new_node);
			fix_height(root);
			//balance(root);
		}
	}
	else
	{
		return ERR_WORK;
	}
	balance(root);

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

int add_balance_counter(tree_node_t **root, tree_node_t *new_node, int *i)
{
	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}
	(*i)++;

	// Если корень существует ищем ближайший в дереве узел для нового слова
	if (strcmp((*root)->word, new_node->word) < 0)
	{
		if ((*root)->right == NULL)
		{
			(*root)->right = new_node;
			new_node->height = 1;
			//new_node->parent = (*root)->right;
			fix_height(root);
		}
		else
		{
			add_balance_counter(&(*root)->right, new_node, i);
			//balance(root);
			fix_height(root);
		}
	}
	else if (strcmp((*root)->word, new_node->word) > 0)
	{
		if ((*root)->left == NULL)
		{
			(*root)->left = new_node;
			new_node->height = 1;
			//new_node->parent = (*root)->left;
			fix_height(root);
		}
		else
		{
			add_balance_counter(&(*root)->left, new_node, i);
			fix_height(root);
			//balance(root);
		}
	}
	else
	{
		return ERR_WORK;
	}
	balance(root);

	return OK;
}

int add_balance_node_counter(tree_node_t **root, char *element, int *i)
{
	// Создаем узел
	tree_node_t *new_node = NULL;
	int rc = create_tree_node(&new_node, element);
	if (rc != OK)
		return ERR_CREATE;
	add_balance_counter(root, new_node, i);
	return OK;
}

void right_rotate(tree_node_t **root)
{
	if (!(*root)->right)
		return;
	tree_node_t *new_root = (*root)->right;
	(*root)->right = new_root->left;
	new_root->left = *root;
	*root = new_root;
	fix_height(&(*root)->left);
	fix_height(root);
}

void left_rotate(tree_node_t **root)
{
	if (!(*root)->left)
		return;
	tree_node_t *new_root = (*root)->left;
	(*root)->left = new_root->right;
	new_root->right = *root;
	*root = new_root;
	fix_height(&(*root)->right);
	fix_height(root);
}

void balance(tree_node_t **root)
{
	int main_balance = get_balance_factor(*root);
	int balance_right = 0, balance_left = 0;
	if ((*root)->right)
		balance_right = get_balance_factor((*root)->right);
	if ((*root)->left)
		balance_left = get_balance_factor((*root)->left);

	if (main_balance == -2)
	{
		if (balance_right == 1)
			left_rotate(&(*root)->right);
		right_rotate(root);
	}
	else if (main_balance == 2)
	{
		if (balance_left == -1)
			right_rotate(&(*root)->left);
		left_rotate(root);
	}
}
int add_new_node_create_balance(tree_node_t **root, data_node_t *data, int start, int end)
{
	//printf("root->word = %s\n", (*root)->word);
	add_tree_node(root, get_data_word(data, start + (end-start)/2));
	//printf("size = %d\n", start + (end-start)/2);
	if ((end-start)/2 > 0)
	{
		add_new_node_create_balance(root, data, start, start + (end-start)/2);
		add_new_node_create_balance(root, data, start + (end-start)/2, end);
	}
	//output_tree_as_dot(*root);
	//int d;
	//scanf("%d", &d);
	return 1;
}

void make_balanced_tree_from_data(tree_node_t **root, data_node_t *data)
{
	int size = get_data_size(data);
	//printf("size = %d\n", size);
	//output_data(data);
	create_tree_node(root, get_data_word(data, size/2));
	//printf("root->word = %s\n", (*root)->word);
	add_new_node_create_balance(root, data, 0, size/2);
	add_new_node_create_balance(root, data, size/2, size);
	check_heights(root);
}
void make_by_add_balanced_tree_from_data(tree_node_t **root, data_node_t *data)
{
	//printf("size = %d\n", size);
	//output_data(data);
	//create_tree_node(root, get_data_word(data, size/2));
	//printf("root->word = %s\n", (*root)->word);
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		//printf("%s\n", cur->data);
		add_balance_node(root, cur->data);
	}
	//add_new_node_create_balance(root, data, 0, size/2);
	//add_new_node_create_balance(root, data, size/2, size);
	check_heights(root);
}
