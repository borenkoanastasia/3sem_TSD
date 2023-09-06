#include "../inc/tree_work.h"

// Добавить лист
int add_tree_node(tree_node_t **root, char *element)
{
	tree_node_t *new_node = NULL, *found_node = NULL;
	int rc;

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

	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}

	// Заполняем параметры узла
	if (strcmp(found_node->word, element) < 0)
		found_node->right = new_node;
	else
		found_node->left = new_node;

	//new_node->parent = found_node;

	return OK;
}


// Найти ближайший узел к заданному
void find_near_node_counter(tree_node_t **root, char *element, tree_node_t **return_node, int *i)
{
	if (*root == NULL)
		return;
	//printf("%s\n", (*root)->word);
	(*i)++;
	if (strcmp((*root)->word, element) < 0)
	{
		if ((*root)->right == NULL)
		{
			*return_node = (*root);
		}
		else
		{
			find_near_node_counter(&(*root)->right, element, return_node, i);
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
			find_near_node_counter(&(*root)->left, element, return_node, i);
		}
	}
	else
	{
		*return_node = (*root);
	}
}
int add_tree_node_counter(tree_node_t **root, char *element, int *i)
{
	tree_node_t *new_node = NULL, *found_node = NULL;
	int rc;

	// Если корень существует ищем ближайший в дереве узел для нового слова
	if (*root)
	{
		find_near_node_counter(root, element, &found_node, i);
		if (!strcmp(found_node->word, element))
			return ERR_WORK;
	}

	// Создаем узел
	rc = create_tree_node(&new_node, element);
	if (rc != OK)
		return rc;

	// Если корня нет - создаем корень
	if (!*root)
	{
		*root = new_node;
		return OK;
	}

	// Заполняем параметры узла

	(*i)++;
	if (strcmp(found_node->word, element) < 0)
		found_node->right = new_node;
	else
		found_node->left = new_node;

	//new_node->parent = found_node;

	return OK;
}
// Создание листа
int create_tree_node(tree_node_t **new_node, char *word)
{
	*new_node = calloc(1, sizeof(tree_node_t));
	if (!*new_node)
	{
		printf("Не удалось выделить память под узел дерева\n");
		return ERR_CREATE;
	}
	//(*new_node)->parent = NULL;
	(*new_node)->right = NULL;
	(*new_node)->left = NULL;
	(*new_node)->height = 1;
	(*new_node)->word = word;
	return OK;
}

// Удаление листа
void free_tree_node(tree_node_t **root)
{
	free(*root);
}

// Удаление дерева
void free_tree(tree_node_t **root)
{
	if ((*root)->right)
		free_tree(&(*root)->right);
	if ((*root)->left)
		free_tree(&(*root)->left);
	free_tree_node(root);
}

// Исправить высоту листа (при условии, что высота поддеревьев правильная) 
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

// Получить баланс фактор
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

// Получить дерево из данных
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

// Поправить высоту во всем дела
void check_heights(tree_node_t **root)
{
	if ((*root)->left)
		check_heights(&(*root)->left);
	if ((*root)->right)
		check_heights(&(*root)->right);
	fix_height(root);
}

// Просмотр дерева слева
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

// Найти ближайший узел к заданному
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

// Строго найти узел
void find_node_strictly(tree_node_t **root, char *element, tree_node_t **return_node)
{
	find_near_node(root, element, return_node);
	if (strcmp((*return_node)->word, element))
		*return_node = NULL;
}

// Добавить связи в файл дот
void add_tree_lines(FILE *file, tree_node_t *root, int *i)
{
	if (root->left != NULL)
	{
		//printf("left\n ");
		fprintf(file, "\t%s -> %s;\n", root->word, root->left->word);
		//fprintf(file, "\t%s%d -> %s%d;\n", root->word, root->height, root->left->word, root->left->height);
		add_tree_lines(file, root->left, i);
		//printf("\t%s -> %s %d\n", root->word, root->left->word, root->height);
	}
	else if (root->right != NULL)
	{
		fprintf(file, "\t%d [ label = \"%d\", style = invis ];\n", *i, *i);
		fprintf(file, "\t%s -> %d [ style = invis ];\n", root->word, *i);
		//fprintf(file, "\t%s%d -> %d [ style = invis ];\n", root->word, root->height, *i);
		//printf("\t%s -> %d [ style = invis ]\n", root->word, *i);
		(*i)++;
	}
	if (root->right != NULL)
	{
		//printf("right\n ");
		fprintf(file, "\t%s -> %s;\n", root->word, root->right->word);
		//fprintf(file, "\t%s%d -> %s%d;\n", root->word, root->height, root->right->word, root->right->height);
		//printf("\t%s -> %s %d\n", root->word, root->right->word, root->height);
		add_tree_lines(file, root->right, i);
	}
	else if (root->left != NULL)
	{
		fprintf(file, "\t%d [ label = \"%d\", style = invis ];\n", *i, *i);
		fprintf(file, "\t%s -> %d [ style = invis ]; \n", root->word, *i);
		//fprintf(file, "\t%s%d -> %d [ style = invis ]; \n", root->word, root->height, *i);
		//printf("\t%s -> %d [ style = invis ]\n", root->word, *i);
		(*i)++;
	}
}

// Записать дерево в дот
void output_tree_as_dot(tree_node_t *root, char *filename)
{
	int i = 0;
	//printf("OUTPUT\n");
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Не удалось открыть файл для вывода\n");
		return;
	}
	fprintf(file, "digraph Tree{\n");
	add_tree_lines(file, root, &i);
	//printf("good end\n");
	fprintf(file, "}");
	fclose(file);
	printf("Файл сохранен\n");
}
/*
// Удалить узел из дерева
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
		//printf("new_left = %s, new_left->parent = %s\n", new_left->word, new_left->parent->word);
		new_left->parent = parent;
		new_left->left = del_node->left;
		new_left->right = del_node->right;
		//printf("new_left = %s, new_left->parent = %s\n", new_left->word, new_left->parent->word);
		//printf("del_left = %s, del_left->parent = %s\n", del_node->word, del_node->parent->word);
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
*/