#include "../inc/testing_trees.h"

// Добавление в дерево двоичного поиска
int testing_usual(data_node_t *data)
{
	int start, end;
	tree_node_t *root = NULL;
	start = clock();
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		add_tree_node(&root, cur->data);
	}
	end = clock();
	free_tree(&root);
	return end - start;
}

// Добавление в сбалансированное дерево
int testing_balance(data_node_t *data)
{
	tree_node_t *root = NULL;
	int start, end;
	start = clock();
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		add_balance_node(&root, cur->data);
	}
	end = clock();
	free_tree(&
		root);
	return end - start;
}

// Сравнение времени добавления в обычное и сбалансированное двоичные деревья
void testing_trees_time()
{
	char *test_filename = "testing_data.txt";
	data_node_t *data = NULL;
	int rc = read_file(test_filename, &data);
	if (rc != OK)
	{
		printf("Провести тестирование не удалось, проверьте наличие тестового файла (test_trees_time.txt)!\n");
		return;
	}
	int tree_time = 0, balance_time = 0, n= 1000;
	for (int i = 0; i < n; i++)
	{
		tree_time += testing_usual(data);
		balance_time += testing_balance(data);
	}
	output_line(51);
	printf("Результат теста:\n");
	printf("tree_time = %d\n", tree_time/n);
	printf("balance_time = %d\n", balance_time/n);
	output_line(51);
}