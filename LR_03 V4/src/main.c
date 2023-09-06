#include "../inc/common.h"
#include "../inc/choise.h"
#include "../inc/input.h"
#include "../inc/memory_work.h"
#include "../inc/matrix.h"

int main()
{
	int choise, rc;
	srand(time(NULL));

	while (1)
	{
		printf("Выберите действие:\n");
		printf("\t1. Перемножить обычные матрицы\n");
		printf("\t2. Перемножить разреженные матрицы\n");
		printf("\t3. Тестирование\n");
		printf("Некорректный выбор - выход\n");

		rc = scanf("%d", &choise); 
		if (rc != 1 || (choise != 1 && choise != 2 && choise != 3))
		{
			printf("Выход\n");
			break;
		}
		if (choise == 1)
		{
			choise_multiplicate_norm_vec_and_matrix();
		}
		else if (choise == 2)
		{
			choise_multiplicate_press_vec_and_matrix();
		}
		else if (choise == 3)
		{
			choise_big_testing();
		}
	}
	return OK;
}