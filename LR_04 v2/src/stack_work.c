#include "../inc/stack_work.h"


// Работа со стеком освобожденных адрессов

int add_free_adress(adress_stack_node_t **head, long int adress)
{
	adress_stack_node_t *new_node;
	new_node = (adress_stack_node_t *)calloc(1, sizeof(adress_stack_node_t));
	if (new_node == NULL)
		return ERR_CREATE;
	new_node->element = adress;
	new_node->next = *head;
	*head = new_node;
	return OK;
}

void output_free_adresses(adress_stack_node_t *head)
{
	for (adress_stack_node_t *cur = head; cur; cur = cur->next)
	{
		printf("%ld\n", cur->element);
	}
}

void free_free_adresses(adress_stack_node_t **head)
{
	for (adress_stack_node_t *cur = (*head)->next; cur; cur = cur->next)
	{
		free(*head);
		*head = cur;
	}
}

// Работа со стеком - списком

int list_push(list_stack_node_t **head, int new_el)
{
	list_stack_node_t *new_node;
	new_node = (list_stack_node_t *)calloc(1, sizeof(list_stack_node_t));
	if (new_node == NULL)
		return ERR_CREATE;
	new_node->element = new_el;
	new_node->next = *head;
	*head = new_node;
	return OK;
}

void list_pop(list_stack_node_t **head, adress_stack_node_t **adress_head)
{
	list_stack_node_t *new_head;
	new_head = (*head)->next;
	free(*head);
	add_free_adress(adress_head, (long int)head);
	*head = new_head;
}

void list_free(list_stack_node_t **head)
{
	for (list_stack_node_t *cur = (*head)->next; cur; cur = cur->next)
	{
		free(*head);
		*head = cur;
	}
}

void list_output_stack(list_stack_node_t *stack)
{
	int i = 0;
	for (list_stack_node_t *cur = stack; cur; cur = cur->next, i++)
	{
		if (i == 0)
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


// Работа со стеком - массивом

int array_create_stack(array_stack_t *stack, int len)
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

int array_push(array_stack_t *stack, int element)
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

int array_pop(array_stack_t *stack, adress_stack_node_t **h)
{
	if (stack->ps == stack->alb - 1)
	{
		return ERR_OVERFLOW;
	}
	*stack->ps = 0;
	stack->ps--;
	return OK;
}

void array_stack_free(array_stack_t *stack)
{
	free(stack->alb);
}

void array_output_stack(array_stack_t stack)
{
	printf("| ");
	for (int *cur = stack.aub - 1; cur > stack.alb - 1; cur--)
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
