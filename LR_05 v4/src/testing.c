#include "../inc/testing.h"

int test_list_exp()
{
	int start, end;
	start = clock();
	for (int i = 0; i < TESTING_REPEATS; i++)
	{
		list_experiment(NOT_SHOW);
	}
	end = clock();
	return end - start;
}

int test_array_exp()
{
	int start, end;

	start = clock();
	for (int i = 0; i < TESTING_REPEATS; i++)
	{
		array_experiment(NOT_SHOW);
	}
	end = clock();
	return end - start;
}

void testing()
{
	int time_arr, time_list, size_arr, size_list;
	printf("\t");
	output_line(51);
	printf("\tТаблица с результатами тестирования (кол-во повторов\n\tдля вычисления времени = %d)\n", TESTING_REPEATS);
	printf("\t");
	output_line(51);
	printf("\t| %8s | %8s | %8s |\n", "type", "time", "memory");
	printf("\t");
	output_line(51);
	time_arr = test_array_exp();
	time_list = test_list_exp();
	size_arr = REQUEST_AMOUNT*sizeof(request_t) * 2 + sizeof(automat_t) * 3 + 2*sizeof(array_turn_t) + 3 * sizeof(list_node_t);
	size_list = REQUEST_AMOUNT*sizeof(request_t) + sizeof(automat_t) * 3 + 2*sizeof(list_turn_t) + (3+REQUEST_AMOUNT)*sizeof(list_node_t);
	printf("\t| %8s | %8d | %8d |\n", "array", time_arr, size_arr);
	printf("\t| %8s | %8d | %8d |\n", "list", time_list, size_list);
	printf("\t");
	output_line(51);
}