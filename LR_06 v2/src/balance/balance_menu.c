#include "../../inc/balance_work.h"


void balanced_menu()
{
	char *filename = "func/test1.txt";
	data_node_t *start_data = NULL;//, *sorted_data = NULL;
	read_file(filename, &start_data);
	printf("Success read data\n");
	output_data(start_data);
	//sort_data(&start_data, &sorted_data);
	//copy_data(sorted_data, &start_data);
	tree_node_t *balanced_root = NULL;
	tree_node_t *find;
	make_by_add_balanced_tree_from_data(&balanced_root, start_data);
	printf("Success make tree\n");
	char *new_el;

	int choise, rc;
	while (1)
	{ 
		output_line(51);
		printf("\tМЕНЮ\n");
		output_line(51);
		printf("\t1. Вывести дерево\n");
		printf("\t2. Добавить узел\n");
		printf("\t3. Найти слово\n");
		printf("\t4. Удалить узел\n");
		printf("\t5. Удалить дерево\n");

		rc = scanf("%d", &choise);
		if (rc != 1)
			break;
		if (choise == 1)
		{
			output_tree_as_dot(balanced_root);
		}
		else if (choise == 2)
		{
			rc = input_word(&new_el);
			if (rc != OK)
				continue;
			add_data_node(&start_data, new_el);
			output_data(start_data);
			add_balance_node(&balanced_root, new_el);
			balance(&balanced_root);
			check_heights(&balanced_root);
		}
		else if (choise == 3)
		{
			rc = input_word(&new_el);
			if (rc != OK)
				continue;
			find_node_strictly(&balanced_root, new_el, &find);
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
			rc = delete_tree_node(&balanced_root, new_el);
			if (rc == ERR_WORK)
				printf("Этого слова нет в дереве\n");
			check_heights(&balanced_root);
		}
		else
		{
			free_tree(&balanced_root);
			free_data(&start_data);
			break;
		}
	}
}