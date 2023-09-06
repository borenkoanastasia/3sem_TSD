#include "../inc/help.h"

// Список

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

void list_pop(list_stack_node_t **head)
{
	list_stack_node_t *new_head;
	new_head = (*head)->next;
	free(*head);
	*head = new_head;
}

void list_free(list_stack_node_t **head)
{
	if (*head == NULL)
		return;
	list_stack_node_t *cur = (*head)->next;

	for (; cur; cur = cur->next)
	{
		free(*head);
		*head = cur;
	}
	free(*head);
}

// Переворот списка

void reverse_list(list_stack_node_t **head)
{
    list_stack_node_t *new_head = 0;
    list_stack_node_t *save_next;
    for(list_stack_node_t *pos = *head; pos;)
    {
        save_next = pos->next;
        pos->next = new_head;
        new_head = pos;
        pos = save_next;
    }
    *head = new_head;
}

void list_output_stack(list_stack_node_t *stack)
{
	if (stack == NULL)
	{
		printf("Стек пуст\n");
		return;
	}
	reverse_list(&stack);
	for (list_stack_node_t *cur = stack; cur; cur = cur->next)
	{
		if (!cur->next)
		{
			printf("| \x1b[41m%d\x1b[0m ", cur->element);
		}
		else 
		{
			printf("| %d ", cur->element);
		}
	}
	printf("|\n");
	reverse_list(&stack);
}

void list_output_stack_spec(list_stack_node_t *stack)
{
	list_stack_node_t *buf = NULL;
	for (list_stack_node_t *cur = stack; cur;)
	{
		list_push(&buf, cur->element);
		list_pop(&cur);
	}
	for (list_stack_node_t *cur = buf; cur;)
	{
		list_push(&stack, cur->element);
		printf("| %d ", stack->element);
		list_pop(&cur);
	}
	printf("|\n");
}

void list_output_tree_stacks(list_stack_node_t **stack1, list_stack_node_t **stack2, list_stack_node_t **stack3)
{
	printf("Stack 1  ");
	list_output_stack(*stack1);
	printf("Stack 2  ");
	list_output_stack(*stack2);
	printf("Stack 3  ");
	list_output_stack(*stack3);
	printf("\n");
}
// Массив

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

int array_pop(array_stack_t *stack)
{
	if (stack->ps == stack->alb - 1)
	{
		return ERR_OVERFLOW;
	}
	//*stack->ps = 0;
	stack->ps--;
	return OK;
}

void array_free(array_stack_t *stack)
{
	free(stack->alb);
}

void array_output_stack(array_stack_t stack)
{
	if (stack.alb == stack.ps + 1)
	{
		printf("Стек пуст\n");
	}
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
/*
void array_output_stack_spec(array_stack_t stack)
{
	array_stack_t buf;
	array_create_stack(&buf, stack.aub - stack.alb);
	for (;stack.ps < stack.aub; stack.ps++)
	{
		array_push(&buf, *(stack.ps));
		array_pop(&stack);
	}
	for (; buf.ps < buf.aub; buf.ps++)
	{
		array_push(&stack, *(buf.ps));
		printf("| %d ", *(stack.ps));
		array_pop(&buf);
	}
	array_free(&buf);
	printf("|\n");
}
*/
void array_output_tree_stacks(array_stack_t *stack1, array_stack_t *stack2, array_stack_t *stack3)
{
	printf("Stack 1  ");
	array_output_stack(*stack1);
	printf("Stack 2  ");
	array_output_stack(*stack2);
	printf("Stack 3  ");
	array_output_stack(*stack3);
	printf("\n\n");
}

// Очищение stdin

void clearInputBuf(void) 
{ 
      int garbageCollector; 
      while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF) 
      {}
}

// Напечатать линию

void output_line(int size)
{
	for(int i = 0; i <size; i++)
		printf("-");
	printf("\n");
}
