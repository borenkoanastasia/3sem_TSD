#include "../inc/input.h"

int input_type_stack()
{
	int rc, type;
	printf("Введите номер типа стека из следущего списка:\n");
	printf("\t%d. Массив\n", ARRAY_STACK);
	printf("\t%d. Список\n", LIST_STACK);
	rc = scanf("%d", &type);
	if (rc != 1)
	{
		printf("Некорректный ввод - выход в главное меню\n");
		clearInputBuf();
		return ERR_INPUT;
	}
	return type;
}

int input_array_stack(array_stack_t *stack)
{
	int size, element, rc;
	printf("Введите размер стека: \n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		clearInputBuf();
		return ERR_INPUT;
	}
	if (size < 1)
	{
		clearInputBuf();
		return ERR_INPUT;
	}
	array_create_stack(stack, size);
	for (int i = 0; i < size; i++)
	{
		printf("Введите новый элемент стека (некорректный ввод или заполнение стека - конец ввода)\n");
		rc = scanf("%d", &element);
		if (rc != 1)
		{
			break;
		}
		rc = array_push(stack, element);
		//printf("rc = %d \n", rc);
		if (rc != OK)
		{
			printf("Не удалось выделить память - выход в главное меню\n");
			array_free(stack);
			return ERR_CREATE;
		}
	}
	clearInputBuf();
	return OK;
}

int input_list_stack(list_stack_node_t **head)
{
	int element, rc;
	rc = 1;
	*head = NULL;
	printf("Введите элементы стека: \n");
	while (rc == 1)
	{
		printf("Введите новый элемент стека (некорректный ввод - конец ввода)\n");
		rc = scanf("%d", &element);
		clearInputBuf();
		if (rc != 1)
		{
			break;
		}
		rc = list_push(head, element);
		if (rc != OK)
		{
			printf("Не удалось выделить память - выход в главное меню\n");
			list_free(head);
			return ERR_CREATE;
		}
		rc = 1;
	}
	return OK;
}
