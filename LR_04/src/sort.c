#include "../inc/sort.h"

void output_tree_stacks(array_t *stack1, array_t *stack2, array_t *stack3)
{
	printf("Stack 1  ");
	array_output_stack(*stack1);
	printf("Stack 2  ");
	array_output_stack(*stack2);
	printf("Stack 3  ");
	array_output_stack(*stack3);
	printf("\n\n");
}

void output_list_tree_stacks(list_stack *stack1, list_stack *stack2, list_stack *stack3)
{
	printf("Stack 1  ");
	list_output_stack(*stack1);
	printf("Stack 2  ");
	list_output_stack(*stack2);
	printf("Stack 3  ");
	list_output_stack(*stack3);
	printf("\n");
}

int array_remove_min_el(array_t *stack1, array_t *stack2, array_t *stack3)
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

int array_sort(array_t *stack1, array_t *stack2, array_t *stack3)
{
	while ((stack2->ps >= stack2->alb || stack1->ps >= stack1->alb))//&& i != 1)
	{
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

int list_remove_min_el(list_stack *stack1, list_stack *stack2, list_stack *stack3)
{
	int i = 0;
	while (stack1->start != NULL)
	{
		i++;
		if (stack1->ps->element < stack2->ps->element)
		{
			list_push(stack3, stack2->ps->element);
			list_pop(stack2);
			list_push(stack2, stack1->ps->element);
			list_pop(stack1);
		}
		else
		{
			list_push(stack3, stack1->ps->element);
			list_pop(stack1);
		}
	}
	while (i > 0)
	{
		i--;
		list_push(stack1, stack3->ps->element);
		list_pop(stack3);
	}
	return OK;
}

int list_sort(list_stack *stack1, list_stack *stack2, list_stack *stack3)
{
	while ((stack2->ps != NULL || stack1->ps != NULL))//&& i != 1)
	{
		if (stack2->ps == NULL)
		{
			list_push(stack2, stack1->ps->element);
			list_pop(stack1);
		}
		list_remove_min_el(stack1, stack2, stack3);
		if (stack1->ps == NULL)
		{
			list_push(stack1, stack2->ps->element);
			list_pop(stack2);
		}
		list_remove_min_el(stack2, stack1, stack3);

		list_push(stack3, stack1->ps->element);
		list_pop(stack1);
	}
	return OK;
}
