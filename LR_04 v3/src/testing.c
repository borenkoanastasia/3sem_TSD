#include "../inc/testing.h"

void make_rand_list(list_stack_node_t **head, int size)
{
	int new_elem = 0;
	for (int i = 0; i < size; i++)
	{
		new_elem = rand()/MAX_RAND;
		list_push(head, new_elem);
	}
}
void make_rand_array(array_stack_t *stack, int size)
{
	int new_elem = 0;
	for (int i = 0; i < size; i++)
	{
		new_elem = rand()/MAX_RAND;
		array_push(stack, new_elem);
	}
}

int test_list_sort(int size, int procent)
{
	list_stack_node_t *stack1 = NULL, *stack2 = NULL, *stack3 = NULL;
	int start, end;
	start = clock();
	for (int i = 0; i < TESTING_REPEATS; i++)
	{
		make_rand_list(&stack1, procent);
		make_rand_list(&stack2, procent);
		list_sort(&stack1, &stack2, &stack3);
		list_free(&stack1);
		list_free(&stack2);
		list_free(&stack3);
		stack1 = NULL;
		stack2 = NULL;
		stack3 = NULL;
	}
	end = clock();
	return end - start;
}

int test_array_sort(int size, int procent)
{
	array_stack_t stack1, stack2, stack3;
	int start, end;
	
	array_create_stack(&stack1, size);
	array_create_stack(&stack2, size);
	array_create_stack(&stack3, size * 2);
	start = clock();
	for (int i = 0; i < TESTING_REPEATS; i++)
	{
		make_rand_array(&stack1, procent);
		make_rand_array(&stack2, procent);
		array_sort(&stack1, &stack2, &stack3);
	}
	end = clock();
	array_free(&stack1);
	array_free(&stack2);
	array_free(&stack3);
	return end - start;
}

void testing()
{
	int time_arr = 0, time_list = 0, count = 0;//, size_arr, size_list;
	printf("\t");
	output_line(51);
	printf("\tТаблица с результатами тестирования (кол-во повторов\n\tдля вычисления времени = %d)\n", TESTING_REPEATS);
	printf("\t");
	output_line(51);
	printf("\t| %3s | %8s | %8s | %8s | %8s |\n", "N", "type", "size", "procent", "time");
	printf("\t");
	output_line(51);

	for (int i = 1; i < 11; i++)
	{
		if (i == 4 || i == 6 || i == 8 || i == 9)
			continue;
		for (int j = 1; j < 11; j++)
		{
			if (j == 4 || j == 6 || j == 8 || j == 9)
				continue;
			if ((i == 1) && (j == 1))
			{
				for (int k = 0; k < 7; k++)
				{
					int cur_s = 1, cur_p = 4;
					time_arr = test_array_sort(cur_s*10, cur_p*10);
					time_list = test_list_sort(cur_s*10, cur_p*10);
				}
			} 
			time_arr = test_array_sort(i*10, j*10);
			time_list = test_list_sort(i*10, j*10);
			//size_arr = i * 10 * sizeof(int) + 3 * sizeof(int *);
			//size_list = i * 10 * sizeof(list_stack_node_t);
			count++;
			printf("\t| %3d | %8s | %8d | %8d | %8d |\n", count, "array", i*10, j*10, time_arr);//, size_arr);
			printf("\t| %3d | %8s | %8d | %8d | %8d |\n", count, "list", i*10, j*10, time_list);//, size_list);
			printf("\t");
			output_line(51);
		}
	}
}