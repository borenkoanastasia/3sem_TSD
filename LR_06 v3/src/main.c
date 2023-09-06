#include "../inc/common.h"
#include "../inc/tree_work.h"
#include "../inc/balance_work.h"
#include "../inc/testing_trees.h"
#include "../inc/hash_work.h"

int main()
{
	//testing_all(40, "test_trees_time.txt");
	//output_line(LINE_LEN);
	//testing_all(40, "testing_data.txt");
	
	int rc = 0;
	char filename[21], tree_file[] = "tree.dot", balance_file[] = "balance.dot";
	data_node_t *data = NULL, *hash_data = NULL, *balance_data = NULL;
	tree_node_t *tree = NULL, *balanced_tree = NULL;
	int hash_table_exist = 0;
	hash_table_t hash;
	int choise, hash_rang = 0;
	char *element, *all_test_file;

	printf("Введите файл для работы:\n");
	rc = scanf("%20s", filename);
	if (rc != 1)
	{
		printf("Некорректный ввод\n");
		free_data(&data);
		return ERR_WORK;
	}

	rc = read_file(filename, &data);

	if (rc != OK)
	{
		printf("Файл не существует или в файле ошибка\n");
		return rc;
	}

	copy_data(data, &hash_data);
	sort_data(&hash_data, &balance_data);
	copy_data(data, &hash_data);


	make_tree_from_data(&tree, data);
	make_by_add_balanced_tree_from_data(&balanced_tree, balance_data);
	//make_hash_table_from_data(&hash, data);
	//printf("data\n");
	//output_data(data);
	//printf("sorted data\n");
	//output_data(balance_data);
	//printf("copied data\n");
	//output_data(hash_data);

	//output_data(data);
	//output_data(sorted_data);

	//output_tree_as_dot(tree, tree_file);
	//output_tree_as_dot(balanced_tree, balance_file);

	while (1)
	{
		output_line(LINE_LEN);
		printf("\tМЕНЮ\n");
		output_line(LINE_LEN);
		printf("Выберите пункт меню (некорректный выбор - выход):\n");
		printf("\t1. Вывести дерево\n");
		printf("\t2. Вывести сбалансированное дерево\n");
		printf("\t3. Добавить элементы в деревья\n");
		printf("\t4. Сравнить эффективность добавления в разные деревья.\n");
		if (hash_table_exist)
		{
			printf("\t5. Вывести хеш-таблицу\n");
			printf("\t6. Реструктурировать хеш-таблицу\n");
			printf("\t7. Добавить элементы в хеш-таблицу\n");
			printf("\t8. Сравнить эффективность добавления в деревья, хеш-таблицу и файл.\n");
		}
		else
		{
			printf("\t5. Создать хеш-таблицу\n");
			printf("\t6. Сравнить эффективность добавления в деревья, хеш-таблицу и файл.\n");
		}
		output_line(LINE_LEN);
		rc = scanf("%d", &choise);
		output_line(LINE_LEN);
		if (rc != 1 || choise < 0 || choise > 8)
		{
			printf("Выход\n");
			break;
		}
		if (choise > 6 && !hash_table_exist)
		{
			printf("Выход\n");
			break;
		}
		clearInputBuf();
		switch (choise)
		{
			case 1:
				output_tree_as_dot(tree, tree_file);
				break;
			case 2:
				output_tree_as_dot(balanced_tree, balance_file);
				break;
			case 3:
				printf("Введите новое слово:\n");
				rc = input_word(&element);
				if (rc != OK)
				{
					clearInputBuf();
					printf("Нельзя вводить числа и русские буквы\n");
					continue;
				}
				add_data_node(&data, element);
				rc = add_tree_node(&tree, element);
				if (rc == ERR_WORK)
					printf("Файл уже в дереве\n");
				rc = add_balance_node(&balanced_tree, element);
				if (rc == ERR_WORK)
					printf("Файл уже в дереве\n");
				break;
			case 4:
				printf("Введите тестовый файл:\n");
				all_test_file = read_word(stdin);
				testing_trees_time(all_test_file);
				break;
			case 5:
				if (hash_table_exist)
					output_hash_table(hash);
				else
				{
					printf("Введите ранг хеш-таблицы:\n");
					rc = scanf("%d", &hash_rang);
					if (rc != 1 || hash_rang > 255 || hash_rang < 0)
					{
						printf("Некорректный ввод\n");
						clearInputBuf();
						return ERR_INPUT;
					}
					hash_table_exist = 1;
					rc = make_hash_table_from_data(&hash, hash_data, hash_rang);
					if (rc != OK)
						return rc;
				}
				break;
			case 6:
				if (hash_table_exist)
				{
					int hash_rang = get_data_size(hash_data);
					printf("Новый ранг:%d\n", hash_rang);
					free_hash_table(&hash);
					make_hash_table_from_data(&hash, hash_data, hash_rang);
				}
				else
				{
					printf("Введите тестовый файл:\n");
					all_test_file = read_word(stdin);
					printf("Введите ранг хеш-таблицы:\n");
					rc = scanf("%d", &hash_rang);
					if (rc != 1 || hash_rang > 255 || hash_rang < 1)
					{
						printf("Некорректный ввод\n");
						clearInputBuf();
						return ERR_INPUT;
					}
					testing_all(hash_rang, all_test_file);
				}
				break;
			case 7:
				if (hash_table_exist)
				{
					printf("Введите новое слово:\n");
					element = read_word(stdin);
					add_data_node(&hash_data, element);
					add_element_in_hash_table(&hash, element);
				}
				break;
			case 8:
				if (hash_table_exist)
				{
					printf("Введите тестовый файл:\n");
					all_test_file = read_word(stdin);
					if (!all_test_file)
					{
						clearInputBuf();
					}
					printf("Введите ранг хеш-таблицы:\n");
					rc = scanf("%d", &hash_rang);
					if (rc != 1 || hash_rang > 255 || hash_rang < 1)
					{
						clearInputBuf();
						printf("Некорректный ввод\n");
						return ERR_INPUT;
					}
					testing_all(hash_rang, all_test_file);
				}
				break;
		}
	}
	output_line(LINE_LEN);
	//free_tree(&tree);
	//free_tree(&balanced_tree);
	//free_data(&data);
	//free_hash_table(&hash);
	
	return OK;
}

