#include "../inc/experiment.h"
#include "../inc/testing.h"
#include "../inc/turn_work.h"

int main()
{
	srand(time(NULL));
	int rc, choise;
	while (1)
	{
		output_line(100);
		printf("\tМЕНЮ\n");
		output_line(100);


		printf("\t1. Работа с очередью\n");	
		printf("\t2. Работа с автоматом (массив)\n");	
		printf("\t3. Работа с автоматом (список)\n");	
		printf("\t4. Тестирование\n");

		rc = scanf("%d", &choise);
		clearInputBuf();
		//printf("rc = %d, choise = %d\n", rc, choise);
		if (rc != 1)
		{
			break;
		}
		if (choise == 1)
		{
			//clearInputBuf();
			choise_turn_work();
			//clearInputBuf();
		}
		else if (choise == 2)
		{
			array_experiment(SHOW);
		}
		else if (choise == 3)
		{
			list_experiment(SHOW);
		}
		else if (choise == 4)
		{
			testing();
		}
		else
		{
			break;
		}
	}
	return OK;
}
