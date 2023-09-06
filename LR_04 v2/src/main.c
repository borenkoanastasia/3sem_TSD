#include "../inc/choises.h"

int main()
{
	int rc, choise;
	adress_stack_node_t *head = NULL;
	while (1)
	{
		for (int i = 0; i < 50; i++)
			printf("-");
		printf("МЕНЮ");
		for (int i = 0; i < 50; i++)
			printf("-");
		printf("\n");


		printf("\t1. Сортировать 2 стека (тип хранения - список)\n");	
		printf("\t2. Сортировать 2 стека (тип хранения - массив)\n");	
		printf("\t3. Вывести освобожденные ячейки памяти\n");

		rc = scanf("%d", &choise);
		//printf("rc = %d, choise = %d\n", rc, choise);
		if (rc != 1)
		{
			clearInputBuf();
			break;
		}
		if (choise == 1)
		{
			choise_list_stacks_sort(&head);
		}
		else if (choise == 2)
		{
			choise_array_stacks_sort(&head);
		}
		else if (choise == 3)
		{
			choise_output_adress_stack(&head);
		}
		else
		{
			break;
		}
	}
	if (head != NULL)
	{
		free_free_adresses(&head);
	}	
	return OK;
}
