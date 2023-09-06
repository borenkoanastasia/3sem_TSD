#include "../inc/common.h"


int array_create_stack(array_t *stack, int len)
{
	stack->alb = (int *)calloc(len, sizeof(int));
	if (stack->alb == NULL)
	{
		return ERR_CREATE;
	}
	stack->aub = stack->alb + len;
	stack->ps = stack->alb - 1;
	return OK;
}

int array_push(array_t *stack, int element)
{
	if (stack->ps + 1 == stack->aub)
	{
		return ERR_OVERFLOW;
	}

	//printf("good compare\n");
	stack->ps++;
	//printf("good increment\n");
	*(stack->ps) = element;
	return OK;
}

int array_pop(array_t *stack)
{
	if (stack->ps == stack->alb - 1)
	{
		return ERR_OVERFLOW;
	}
	*stack->ps = 0;
	stack->ps--;
	return OK;
}

void array_stack_free(array_t *stack)
{
	free(stack->alb);
}

void array_output_stack(array_t stack)
{
	printf("| ");
	for (int *cur = stack.alb; cur < stack.aub; cur++)
	{
		if (cur == stack.ps)
		{
			printf("\x1b[41m%d\x1b[0m | ", *cur);
		}
		else
		{
			printf("%d | ", *cur);
		}
	}

	printf("\n");
}

int list_push(list_stack *stack, int element)
{
	node_t *new_node = (node_t *) calloc(1, sizeof(node_t));
	if (new_node == NULL)
	{
		return ERR_CREATE;
	}
	new_node->element = element;
	if (stack->ps == NULL)
	{
		stack->ps = new_node;
		stack->start = new_node;
	}
	else
	{
		stack->ps->next = new_node;
		stack->ps = new_node;
	}
	return OK;
}

int list_pop(list_stack *stack)
{
	if (stack->ps == stack->start)
	{
		free(stack->ps);
		stack->start = NULL;
		stack->ps = NULL;
		return OK;	
	}
	if (stack->ps == stack->start)
		return ERR_EMPTY;
	node_t *cur = stack->start;
	for (; cur->next->next; cur = cur->next);
	free(stack->ps);
	cur->next = NULL;
	stack->ps = cur;
	return OK; 
}

void list_stack_free(list_stack *stack)
{
	node_t *cur = stack->start;
	for (;stack->start; stack->start = cur)
	{
		cur = stack->start;
		free(stack->start);
	};
}

void list_output_stack(list_stack stack)
{
	for (node_t *cur = stack.start; cur; cur = cur->next)
	{
		if (cur == stack.ps)
		{
			printf("| \x1b[41m%d\x1b[0m ", cur->element);
		}
		else 
		{
			printf("| %d ", cur->element);
		}
	}
	printf("|\n");
}
