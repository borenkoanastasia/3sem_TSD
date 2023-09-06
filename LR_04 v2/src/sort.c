#include "../inc/sort.h"

void output_tree_stacks(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3)
{
	printf("Stack 1  ");
	array_output_stack(*stack1);
	printf("Stack 2  ");
	array_output_stack(*stack2);
	printf("Stack 3  ");
	array_output_stack(*stack3);
	printf("\n\n");
}

int array_remove_min_el(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3, 
	adress_stack_node_t **h)
{
	int i = 0;
	while (stack1->ps >= stack1->alb)
	{
		i++;
		if (*(stack1->ps) < *(stack2->ps))
		{
			array_push(stack3, *(stack2->ps));
			array_pop(stack2, h);
			array_push(stack2, *(stack1->ps));
			array_pop(stack1, h);
		}
		else
		{
			array_push(stack3, *(stack1->ps));
			array_pop(stack1, h);
		}
	}
	while (i > 0)
	{
		i--;
		array_push(stack1, *(stack3->ps));
		array_pop(stack3, h);
	}
	return OK;
}

int array_sort(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3, 
	adress_stack_node_t **h)
{
	while ((stack2->ps >= stack2->alb || stack1->ps >= stack1->alb))//&& i != 1)
	{
		//output_tree_stacks(stack1, stack2, stack3);
		if (stack2->ps < stack2->alb)
		{
			array_push(stack2, *(stack1->ps));
			array_pop(stack1, h);
		}
		array_remove_min_el(stack1, stack2, stack3, h);
		if (stack1->ps < stack1->alb)
		{
			array_push(stack1, *(stack2->ps));
			array_pop(stack2, h);
		}
		array_remove_min_el(stack2, stack1, stack3, h);

		array_push(stack3, *(stack1->ps));
		array_pop(stack1, h);
	}
	return OK;
}


void output_list_tree_stacks(list_stack_node_t **stack1, list_stack_node_t **stack2, 
	list_stack_node_t **stack3)
{
	printf("Stack 1  ");
	list_output_stack(*stack1);
	printf("Stack 2  ");
	list_output_stack(*stack2);
	printf("Stack 3  ");
	list_output_stack(*stack3);
	printf("\n");
}
int list_remove_min_el(list_stack_node_t **stack1, list_stack_node_t **stack2, 
	list_stack_node_t **stack3, adress_stack_node_t **h)
{
	int i = 0;
	while (*stack1 != NULL)
	{
		i++;
		if ((*stack1)->element < (*stack2)->element)
		{
			list_push(stack3, (*stack2)->element);
			list_pop(stack2, h);
			list_push(stack2, (*stack1)->element);
			list_pop(stack1, h);
		}
		else
		{
			list_push(stack3, (*stack1)->element);
			list_pop(stack1, h);
		}
	}
	while (i > 0)
	{
		i--;
		list_push(stack1, (*stack3)->element);
		list_pop(stack3, h);
	}
	return OK;
}

int list_sort(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3,
	adress_stack_node_t **h)
{
	while ((*stack2 != NULL || *stack1 != NULL))//&& i != 1)
	{
		if (*stack2 == NULL)
		{
			list_push(stack2, (*stack1)->element);
			list_pop(stack1, h);
		}
		list_remove_min_el(stack1, stack2, stack3, h);
		if (*stack1 == NULL)
		{
			list_push(stack1, (*stack2)->element);
			list_pop(stack2, h);
		}
		list_remove_min_el(stack2, stack1, stack3, h);

		list_push(stack3, (*stack1)->element);
		list_pop(stack1, h);
		//output_list_tree_stacks(stack1, stack2, stack3);
	}
	return OK;
}
