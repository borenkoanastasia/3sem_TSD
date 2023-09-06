#include "../inc/menu.h"


void test1()
{
	char *filename = "func/test1.txt";
	data_node_t *data = NULL;
	read_file(filename, &data);
	printf("Success read data\n");
	output_data(data);
	tree_node_t *root;
	make_tree_from_data(&root, data);
	printf("Success make tree\n");
	//output_tree_as_dot(root);
	printf("Success convert\n");
	free_tree(&root);
	printf("Success free tree\n");
	free_data(&data);
	printf("Success free data\n");
}

void test()
{}

void main_menu()
{
	char *filename = "func/test1.txt";
	data_node_t *data = NULL, *copied_data = NULL, *sorted_data = NULL;
	read_file(filename, &data);
	//printf("Success read data\n");
	
	output_data(data);
	tree_node_t *root, *balanced_tree = NULL;
	tree_node_t *find;
	make_tree_from_data(&root, data);
	printf("Success make tree\n");
	char *new_el;

	int choise, rc;
	while (1)
	{ 
		output_line(51);
		printf("\tМЕНЮ\n");
		output_line(51);
		printf("\t1. Работа с двоичным деревом\n");
		printf("\t2. Работа со сбалансированным деревом\n");
		printf("\t3. Работа с хеш-таблицей\n");
		printf("\t4. Сравнение скорости и памяти при добавлении элементов в различные деревья\n");
		printf("\t5. Сравнение времени добавления в различные структуры данных\n");
		//printf("\t7. Сортировка исходных данных\n");

		rc = scanf("%d", &choise);
		if (rc != 1)
			break;
		if (choise == 1)
		{
			//output_tree_as_dot(root);
		}
		else if (choise == 2)
		{
			rc = input_word(&new_el);
			if (rc != OK)
				continue;
			add_data_node(&data, new_el);
			output_data(data);
			add_tree_node(&root, new_el);
			check_heights(&root);
		}
		else if (choise == 3)
		{
			rc = input_word(&new_el);
			if (rc != OK)
				continue;
			find_node_strictly(&root, new_el, &find);
			if (!find)
			{
				printf("Такого слова в дереве нет\n");
			}
			else
			{
				printf("В дереве содержится слово %s\n", find->word);
			}
		}
		else if (choise == 4)
		{
			rc = input_word(&new_el);
			if (rc != OK)
				continue;
			delete_tree_node(&root, new_el);
			check_heights(&root);
		}
		else if (choise == 6)
		{
			copy_data(data, &copied_data);
			//printf("good copy\n");
			sort_data(&copied_data, &sorted_data);
			//printf("good sort\n");
			output_data(data);
			output_data(sorted_data);
			make_balanced_tree_from_data(&balanced_tree, sorted_data);
			//printf("good make\n");
			check_heights(&root);
			//output_tree_as_dot(balanced_tree);
			//printf("good output\n");
			free_data(&copied_data);
			free_data(&sorted_data);
			copied_data = NULL;
			sorted_data = NULL;
			free_tree(&balanced_tree);
		}
		else if (choise == 7)
		{
			copy_data(data, &copied_data);
			sort_data(&copied_data, &sorted_data);
			output_data(data);
			output_data(copied_data);
			output_data(sorted_data);
			free_data(&copied_data);
			free_data(&sorted_data);
			copied_data = NULL;
			sorted_data = NULL;
		}
		else
		{
			free_tree(&root);
			free_data(&data);
			break;
		}
	}
}
