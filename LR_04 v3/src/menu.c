#include "../inc/menu.h"

void menu()
{
	srand(time(NULL));
	int rc, choise;
	while (1)
	{
		output_line(100);
		printf("\tМЕНЮ\n");
		output_line(100);


		printf("\t1. Работа со стеком\n");	
		printf("\t2. Сортировка\n");	
		printf("\t3. Тестирование\n");

		rc = scanf("%d", &choise);
		clearInputBuf();
		//printf("rc = %d, choise = %d\n", rc, choise);
		if (rc != 1)
		{
			break;
		}
		if (choise == 1)
		{
			choise_stack_work();
		}
		else if (choise == 2)
		{
			choise_sort();
		}
		else if (choise == 3)
		{
			testing();
		}
		else
		{
			break;
		}
	}
}