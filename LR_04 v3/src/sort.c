#include "../inc/sort.h"
#include "../inc/stack_work.h"
// Работа со стеком - списком

int list_remove_min_el(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3)
{
	int i = 0;
	while (*stack1 != NULL)
	{
		i++;
		if ((*stack1)->element < (*stack2)->element)
		{
			list_push(stack3, (*stack2)->element);
			list_pop(stack2);
			list_push(stack2, (*stack1)->element);
			list_pop(stack1);
		}
		else
		{
			list_push(stack3, (*stack1)->element);
			list_pop(stack1);
		}
	}
	while (i > 0)
	{
		i--;
		list_push(stack1, (*stack3)->element);
		list_pop(stack3);
	}
	return OK;
}

int list_sort(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3)
{
	while ((*stack2 != NULL || *stack1 != NULL))//&& i != 1)
	{
		if (*stack2 == NULL)
		{
			list_push(stack2, (*stack1)->element);
			list_pop(stack1);
		}
		list_remove_min_el(stack1, stack2, stack3);
		if (*stack1 == NULL)
		{
			list_push(stack1, (*stack2)->element);
			list_pop(stack2);
		}
		list_remove_min_el(stack2, stack1, stack3);

		list_push(stack3, (*stack1)->element);
		list_pop(stack1);
		//output_list_tree_stacks(stack1, stack2, stack3);
	}
	return OK;
}

// Работа со стеком - массивом

int array_remove_min_el(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3)
{
	int i = 0;
	while (stack1->ps >= stack1->alb)
	{
		i++;
		if (*(stack1->ps) < *(stack2->ps))
		{
			array_push(stack3, *(stack2->ps));
			array_pop(stack2);
			array_push(stack2, *(stack1->ps));
			array_pop(stack1);
		}
		else
		{
			array_push(stack3, *(stack1->ps));
			array_pop(stack1);
		}
	}
	while (i > 0)
	{
		i--;
		array_push(stack1, *(stack3->ps));
		array_pop(stack3);
	}
	return OK;
}

int array_sort(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3)
{
	while ((stack2->ps >= stack2->alb || stack1->ps >= stack1->alb))//&& i != 1)
	{
		//output_tree_stacks(stack1, stack2, stack3);
		if (stack2->ps < stack2->alb)
		{
			array_push(stack2, *(stack1->ps));
			array_pop(stack1);
		}
		array_remove_min_el(stack1, stack2, stack3);
		if (stack1->ps < stack1->alb)
		{
			array_push(stack1, *(stack2->ps));
			array_pop(stack2);
		}
		array_remove_min_el(stack2, stack1, stack3);

		array_push(stack3, *(stack1->ps));
		array_pop(stack1);
	}
	return OK;
}

int input_choise_output(int *choise)
{
	printf("Выберите из списка:\n");
	printf("\t1. Вывести адреса\n");
	printf("\t2. Не выводить адреса\n");
	int rc;
	rc = scanf("%d", choise);
	clearInputBuf();
	if (rc == OK)
		return ERR_CREATE;
	return OK;
}

void choise_sort()
{
	int choise = input_type_stack();
	if (choise == ARRAY_STACK)
	{
		array_stack_t stack1, stack2, stack3;
		int rc;
		rc = input_array_stack(&stack1);
		if (rc != OK)
			return;
		rc = input_array_stack(&stack2);
		if (rc != OK)
			return;
		array_create_stack(&stack3, (stack1.aub - stack1.alb) + (stack2.aub - stack2.alb));

		printf("Стек 1: ");
		array_output_stack(stack1);
		printf("Стек 2: ");
		array_output_stack(stack2);
	
		array_sort(&stack1, &stack2, &stack3);
	
		printf("Результаты \n");
		printf("Стек 1: ");
		array_output_stack(stack1);
		printf("Стек 2: ");
		array_output_stack(stack2);
		printf("Стек 3: ");
		array_output_stack(stack3);

		array_free(&stack1);
		array_free(&stack2);
		array_free(&stack3);
	}
	else if (choise == LIST_STACK)
	{
		list_stack_node_t *head1 = NULL, *head2 = NULL, *head3 = NULL;
		int rc;
		//printf("Good start\n");
		rc = input_list_stack(&head1);
		if (rc != OK)
			return;
		rc = input_list_stack(&head2);
		if (rc != OK)
			return;

		printf("Стек 1: ");
		list_output_stack(head1);
		printf("Стек 2: ");
		list_output_stack(head2);
	
		list_sort(&head1, &head2, &head3);
	
		printf("Результаты \n");
		printf("Стек 1: ");
		list_output_stack(head1);
		printf("Стек 2: ");
		list_output_stack(head2);
		printf("Стек 3: ");
		list_output_stack(head3);


		list_free(&head1);
		list_free(&head2);
		list_free(&head3);
	}
}