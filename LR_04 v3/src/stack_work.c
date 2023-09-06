#include "../inc/stack_work.h"

int spec_list_pop(list_stack_node_t **head, adress_stack_node_t **h)
{
	if (*head == NULL)
	{
		return ERR_OVERFLOW;
	}
	list_stack_node_t *new_head;
	new_head = (*head)->next;
	add_adresses(h, (long int)*head);
	free(*head);
	*head = new_head;
	return OK;
}

void spec_list_free(list_stack_node_t **head, adress_stack_node_t **h)
{
	if (*head == NULL)
		return;
	list_stack_node_t *cur = (*head)->next;

	for (; cur; cur = cur->next)
	{
		add_adresses(h, (long int)*head);
		free(*head);
		*head = cur;
	}
	add_adresses(h, (long int)*head);
	free(*head);
}

int l_push(list_stack_node_t **stack)
{
	int new_element;
	printf("Введите элемент:\n");
	int rc = scanf("%d", &new_element);
	if (rc != 1)
	{
		printf("Некорректный ввод\n");
		clearInputBuf();
		return ERR_INPUT;
	}
	//list_output_stack(*stack);
	rc = list_push(stack, new_element);
	if (rc == ERR_CREATE)
		printf("Не удалось выделить память под элемент\n");
	//else if (rc == ERR_OVERFLOW)
	//	printf("Стек заполнен\n");
	return rc;
}

void list_stack_work()
{
	int rc, choise;
	list_stack_node_t *stack = NULL;
	adress_stack_node_t *adresses = NULL;

	while (1)
	{
		printf("Выберите пункт меню (Выбор не из списка - 4 пункт):\n");
		printf("\t1. Добавить элемент \n");
		printf("\t2. Удалить элемент\n");
		printf("\t3. Вывести стек\n");
		printf("\t4. Вывести очищенные ячейки памяти\n");
		printf("\t5. Очистить стек (выведуться все использованные стеком ячейки и вы выйдете в главное меню)\n");

		rc = scanf("%d", &choise);
		if (rc != 1)
		{
			printf("Некорректный ввод\n");
			clearInputBuf();
			return;
		}
		clearInputBuf();
		switch (choise)
		{
			case 1:
			{
				l_push(&stack);
				list_output_stack(stack);
				break;
			}
			case 2:
			{
				rc = spec_list_pop(&stack, &adresses);
				if (rc == ERR_OVERFLOW)
					printf("Стек пуст\n");
				break;
			}
			case 3:
			{
				list_output_stack_spec(stack);
				break;
			}
			case 4:
			{
				output_adresses(adresses);
				break;
			}
			case 5:
			{
				spec_list_free(&stack, &adresses);
				output_adresses(adresses);
				free_adresses(&adresses);
				break;
			}
			default:
			return;
		}
	}
}

int a_push(array_stack_t *stack)
{
	int new_element;
	printf("Введите элемент:\n");
	int rc = scanf("%d", &new_element);
	if (rc != 1)
	{
		printf("Некорректный ввод\n");
		clearInputBuf();
		return ERR_INPUT;
	}
	rc = array_push(stack, new_element);
	if (rc == ERR_CREATE)
		printf("Не удалось выделить память под элемент\n");
	else if (rc == ERR_OVERFLOW)
		printf("Стек заполнен\n");
	return rc;
}

void array_stack_work()
{
	int rc, choise;
	array_stack_t stack;
	rc = input_array_stack(&stack);

	while (rc == OK)
	{
		printf("Выберите пункт меню (Выбор не из списка - 4 пункт):\n");
		printf("\t1. Добавить элемент \n");
		printf("\t2. Удалить элемент\n");
		printf("\t3. Вывести стек\n");
		printf("\t4. Очистить стек (Выход в главное меню)\n");

		rc = scanf("%d", &choise);
		//printf("choise = %d\n", choise);
		if (rc != 1)
		{
			printf("Некорректный ввод\n");
			clearInputBuf();
			return;
		}
		switch (choise)
		{
			case 1:
			{
				a_push(&stack);
				break;
			}
			case 2:
			{
				rc = array_pop(&stack);
				if (rc == ERR_OVERFLOW)
					printf("Стек пуст\n");
				break;
			}
			case 3:
			{
				array_output_stack(stack);
				break;
			}
			case 4:
			{
				array_free(&stack);
			clearInputBuf();
				return;
			}
			default:
			clearInputBuf();
			return;
		}
		rc = OK;
		clearInputBuf();
	}
}

void choise_stack_work()
{
	int choise = input_type_stack();
	if (choise == ARRAY_STACK)
		array_stack_work();
	else if (choise == LIST_STACK)
		list_stack_work();
}