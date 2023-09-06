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
void testing_trees_time(char *test_filename)
{
	//char *test_filename = "testing_data.txt";
	data_node_t *data = NULL;
	int rc = read_file(test_filename, &data);
	if (rc != OK)
	{
		printf("Провести тестирование не удалось, проверьте наличие тестового файла (%s)!\n", test_filename);
		return;
	}
	int size = get_data_size(data);
	int tree_time = 0, balance_time = 0, n = 1000;
	for (int i = 0; i < n; i++)
	{
		tree_time += testing_usual(data);
		balance_time += testing_balance(data);
	}
	int tree_memory = sizeof(tree_node_t) * size - sizeof(int)*size;
	int balance_memory = sizeof(tree_node_t)*size;

	printf("Результат теста (тест проводился на файле %s, время в мсек):\n", test_filename);
	printf("|%19s|%20s|%20s|\n", "№", "ДДП", "АВЛ");
	printf("|%17s|%17d|%17d|\n", "time", tree_time/n, balance_time/n);
	printf("|%17s|%17d|%17d|\n", "memory", tree_memory, balance_memory);
	//printf("Двоичное дерево поиска = %d\n", tree_time/n);
	//printf("Сбалансированное дерево = %d\n", balance_time/n);
}

// Добавление в хэш-таблицу
int testing_hash(data_node_t *data, int i)
{
	int start, end;
	hash_table_t table;
	hash_element_node_t *new;
	create_hash_table(&table, i);
	start = clock();
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		hash_fuction(cur->data, i);
		create_hash_element_node(&new, cur->data);
		//add_element_in_hash_table(&table, cur->data);
	}
	end = clock();
	free_hash_table(&table);
	return end - start;
}

// Добавление в файл
int testing_file(data_node_t *data, char *filename)
{
	int start, end;
	FILE *file = fopen("test_file.txt", "w");
	start = clock();
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		fprintf(file, "%s", cur->data);
	}
	end = clock();
	fclose(file);
	return end - start;
}




// Добавление в дерево двоичного поиска
int testing_usual_counter(data_node_t *data)
{
	int counter = 0;
	tree_node_t *root = NULL;
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		add_tree_node_counter(&root, cur->data, &counter);
	}
	free_tree(&root);
	return counter;
}

// Добавление в сбалансированное дерево
int testing_balance_counter(data_node_t *data)
{
	tree_node_t *root = NULL;
	int counter = 0;
	
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		add_balance_node_counter(&root, cur->data, &counter);
	}
	free_tree(&root);
	return counter;
}

// Добавление в хэш-таблицу
int testing_hash_counter(data_node_t *data, int i)
{
	int counter = 0;
	hash_table_t table;
	create_hash_table(&table, i);
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		//hash_fuction(cur->data, i);
		//create_hash_element_node(&new, cur->data);
		add_element_hash_counter(&table, cur->data, &counter);
		//printf("counter = %d\n", counter);
	}
	free_hash_table(&table);
	return counter;
}

void testing_all(int rang, char *test_filename)
{
	data_node_t *data = NULL;
	//char *test_filename = "testing_data.txt";
	int rc = read_file(test_filename, &data);
	if (rc != OK)
	{
		printf("Провести тестирование не удалось, проверьте наличие тестового файла %s!\n", test_filename);
		return;
	}
	int size = get_data_size(data);//, rang = size;
	//if (size > 255)
	//	rang = 255;
	int tree_time = 0, balance_time = 0, hash_time = 0, file_time = 0, n = 1000;
	int tree_counter = 0, balance_counter = 0, hash_counter = 0;
	for (int i = 0; i < n; i++)
	{
		tree_time += testing_usual(data);
		balance_time += testing_balance(data);
		//printf("good trees\n");
		hash_time += testing_hash(data, rang);
		//printf("good hash\n");
		file_time += testing_file(data, "file.txt");
		//printf("good file\n");
	}
	tree_counter += testing_usual_counter(data);
	balance_counter += testing_balance_counter(data);
		//printf("good trees\n");
	hash_counter += testing_hash_counter(data, rang);
	int tree_memory = sizeof(tree_node_t)*size - sizeof(int)*size;
	int balance_memory = sizeof(tree_node_t)*size;
	int hash_memory = sizeof(hash_table_t)*size;
		//printf("good hash\n");
	free_data(&data);
	//output_line(LINE_LEN);
	printf("Результат теста (тест проводился на файле %s, время в мсек):\n", test_filename);
	printf("|%12s|%10s|%10s|%10s|%11s|\n", "№", "ДДП", "АВЛ", "Хеш", "Файл");
	printf("|%10s|%7d|%7d|%7d|%7d|\n", "time", tree_time/n, balance_time/n, hash_time/n, file_time/n);
	printf("|%10s|%7d|%7d|%7d|%7s|\n", "memory", tree_memory, balance_memory, hash_memory, "---");
	printf("|%10s|%.5f|%.5f|%.5f|%7s|\n", "comparing", (double)tree_counter/size, (double)balance_counter/size, (double)hash_counter/size, "---");
	//printf("Время:");
	//printf("Двоичное дерево поиска = %d\n", tree_time/n);
	//printf("Сбалансированное дерево = %d\n", balance_time/n);
	//printf("Хеш-таблица = %d\n", hash_time/n);
	//printf("Файл = %d\n", file_time/n);
	//printf("Двоичное дерево поиска = %d\n", tree_counter/size);
	//printf("Сбалансированное дерево = %d\n", balance_counter/size);
	//printf("Хеш-таблица = %d\n", hash_counter/size);
	printf("Добавлено %d слов(а).\n", size);
}