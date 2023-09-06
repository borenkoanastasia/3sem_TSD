#include "../inc/common.h"
#include "../inc/sort.h"

void make_rand_arr_stack(array_t *stack)
{
	int new_element;
	int len = 4;
	array_create_stack(stack, len);
	//printf("%ld\n", stack->aub - stack->alb);
	//array_output_stack(*stack);
	for (int i = 0; i < len; i++)
	{
		//printf("i = %d\n", i);
		new_element = rand() % 100 + 1;
		array_push(stack, new_element);
	}
}

void make_rand_list_stack(list_stack *stack)
{
	int new_element;
	int len = 4;
	//printf("%ld\n", stack->aub - stack->alb);
	//array_output_stack(*stack);
	for (int i = 0; i < len; i++)
	{
		//printf("i = %d\n", i);
		new_element = rand() % 100 + 1;
		list_push(stack, new_element);
	}
}

void test_array()
{
	srand(time(NULL));
	array_t stack1, stack2, stack3;
	//printf("good start\n");
	make_rand_arr_stack(&stack1);
	make_rand_arr_stack(&stack2);
	array_create_stack(&stack3, 20);

	//printf("good create\n");
	printf("Stack 1\n");
	array_output_stack(stack1);
	printf("\n");
	printf("Stack 2\n");
	array_output_stack(stack2);
	//printf("good end\n");

	//array_remove_min_el(&stack1, &stack2, &stack3);
	array_sort(&stack1, &stack2, &stack3);
	printf("\n");
	//printf("Stack 1\n");
	//array_output_stack(stack1);
	//printf("\n");
	//printf("Stack 2\n");
	//array_output_stack(stack2);
	//printf("\n");
	printf("Stack 3\n");
	array_output_stack(stack3);
	array_stack_free(&stack1);
	array_stack_free(&stack2);
	array_stack_free(&stack3);
}

void test_list()
{
	srand(time(NULL));
	list_stack stack1 = {NULL, NULL}, stack2 = {NULL, NULL}, stack3 = {NULL, NULL};
	//printf("good start\n");
	make_rand_list_stack(&stack1);
	make_rand_list_stack(&stack2);
	//printf("good create\n");
	printf("Stack 1\n");
	list_output_stack(stack1);
	printf("\n");
	printf("Stack 2\n");
	list_output_stack(stack2);
	//printf("good end\n");

	//array_remove_min_el(&stack1, &stack2, &stack3);
	list_sort(&stack1, &stack2, &stack3);
	printf("\n");
	//printf("Stack 1\n");
	//array_output_stack(stack1);
	//printf("\n");
	//printf("Stack 2\n");
	//array_output_stack(stack2);
	//printf("\n");
	printf("Stack 3\n");
	list_output_stack(stack3);
	list_stack_free(&stack1);
	list_stack_free(&stack2);
	//list_stack_free(&stack3);
}

int main()
{
	int rc, choise;
	while (1)
	{
		printf("Выберите пункт меню\n");
		printf("\t1. Отсортировать два стека (списка)\n");
		printf("\t2. Отсортировать два стека (массива)\n");
		printf("\t3. Показать сохраненные адреса\n");
		rc = scanf("%d", &choise); 
		if (rc != 1 || (choise != 1 && choise != 2 && choise != 3))
		{
			printf("Выход\n");
			break;
		}
		if (choise == 1)
		{
			test_list();
		}
		else if (choise == 2)
		{
			test_array();
		}
	}
	return OK;
}