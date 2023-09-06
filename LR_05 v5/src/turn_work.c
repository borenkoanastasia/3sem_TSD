#include "../inc/turn_work.h"

int tw_list_push(tw_list *turn, int element)
{
	tw_node *node = calloc(1, sizeof(tw_node));
	if (node == NULL)
		return ERR_CREATE;
	node->element = element;
	if (turn->pin == NULL)
	{
		turn->pout = node;
		turn->pin = node;
	}
	else
	{
		turn->pin->next = node;
		turn->pin = node;
	}
	return OK;
}
int tw_list_pop(tw_list *turn, adress_stack_node_t **head)
{
	if (turn == NULL)
	{
		return ERR_OVERFLOW;
	}
	tw_node *del_node = turn->pout;
	int ans = del_node->element;
	add_adresses(head, (long int)turn->pout);
	turn->pout = del_node->next;
	free(del_node);
	return ans;
}

void tw_list_free(tw_list *turn, adress_stack_node_t **head)
{
	if (turn->pout == NULL)
		return;
	for (tw_node *cur = turn->pout->next; cur; cur = cur->next)
	{
		add_adresses(head, (long int)turn->pout);
		free(turn->pout);
		turn->pout = cur;
	}
	add_adresses(head, (long int)turn->pout);
	free(turn->pout);
}
void tw_s_list_free(tw_list *turn)
{
	if (turn->pout == NULL)
		return;
	for (tw_node *cur = turn->pout->next; cur; cur = cur->next)
	{
		free(turn->pout);
		turn->pout = cur;
	}
	free(turn->pout);
}

void tw_list_output(tw_list turn)
{
	printf("Элементы очереди\n");
	for (tw_node *cur = turn.pout; cur; cur = cur->next)
	{
		printf("%d\t", cur->element);
	}
	printf("\n");
}

int tw_array_create(tw_array *turn, int size)
{
	turn->pout = calloc(size, sizeof(int));
	if (turn->pout == NULL)
	{
		turn->size = 0;
		return ERR_CREATE;
	}
	turn->pin = turn->pout;
	turn->size = size;
	return OK;
}
int tw_array_push(tw_array *turn, int element)
{
	if (turn->pin - turn->pout + 1 > turn->size)
	{
		printf("Превышен размер очереди\n");
		return ERR_OVERFLOW;
	}
	*(turn->pin) = element;
	turn->pin++;
	return OK;
}
int tw_array_pop(tw_array *turn)
{
	if (turn->pin <= turn->pout)
	{
		return ERR_OVERFLOW;
	}
	int element = *(turn->pout);
	for (int *cur = turn->pout; cur < turn->pin; cur++)
	{
		*cur = *(cur + 1);
	}
	turn->pin--;
	return element;
}

void tw_array_free(tw_array *turn)
{
	free(turn->pout);
}
void tw_array_output(tw_array turn)
{
	
	if (turn.pout == turn.pin)
		printf("Очередь пуста");
	else
		printf("Элементы очереди\n");
	for (int *cur = turn.pout; cur < turn.pin; cur++)
	{
		printf("%d\t", *cur);
	}
	printf("\n");
}

int input_type_turn()
{
	int rc, type;
	printf("Введите номер типа очереди из следущего списка:\n");
	printf("\t%d. Массив\n", ARRAY_TURN);
	printf("\t%d. Список\n", LIST_TURN);
	rc = scanf("%d", &type);
	if (rc != 1)
	{
		printf("Некорректный ввод - выход в главное меню\n");
		clearInputBuf();
		return ERR_INPUT;
	}
	return type;
}

int input_array_turn(tw_array *turn)
{
	int size, element, rc;
	turn->pout = NULL;
	turn->pin = NULL;
	printf("Введите размер очереди: \n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		//clearInputBuf();
		return ERR_INPUT;
	}
	if (size < 1)
	{
		return ERR_INPUT;
	}
	turn->pout = NULL;
	turn->pin = NULL;
	tw_array_create(turn, size);
	turn->pin = turn->pout;
	//printf("pin = %ld, pout = %ld\n", (long int)turn->pin, (long int)turn->pout);
	//tw_array_output(*turn);
	for (int i = 0; i < size; i++)
	{
		printf("Введите новый элемент очереди (некорректный ввод или заполнение стека - конец ввода)\n");
		rc = scanf("%d", &element);
	//tw_array_output(*turn);
		if (rc != 1)
		{
			//clearInputBuf();
			break;
		}
		rc = tw_array_push(turn, element);
		//printf("pin = %ld, pout = %ld, size = %d\n", (long int)turn->pin, (long int)turn->pout, turn->size);
		//tw_array_output(*turn);
		if (rc != OK)
		{
			//printf("Не удалось выделить память - выход в главное меню\n");
			tw_array_free(turn);
			return ERR_CREATE;
		}
	//printf("pin = %ld, pout = %ld\n", (long int)turn->pin, (long int)turn->pout);
	//tw_array_output(*turn);
	}
	//clearInputBuf();
	return OK;
}

int input_list_turn(tw_list *turn)
{
	int element, rc;
	rc = 1;
	turn->pout = NULL;
	turn->pin = NULL;
	printf("Введите элементы стека: \n");
	while (rc == 1)
	{
		printf("Введите новый элемент очереди (некорректный ввод - конец ввода)\n");
		rc = scanf("%d", &element);
		if (rc != 1)
		{
			clearInputBuf();
			break;
		}
		rc = tw_list_push(turn, element);
		if (rc != OK)
		{
			printf("Не удалось выделить память - выход в главное меню\n");
			tw_s_list_free(turn);
			return ERR_CREATE;
		}
		rc = 1;
	}
	return OK;
}


int l_push(tw_list *turn)
{
	int new_element;
	printf("Введите элемент:\n");
	int rc = scanf("%d", &new_element);
	if (rc != 1)
	{
		printf("Некорректный ввод\n");
		//clearInputBuf();
		return ERR_INPUT;
	}
	//list_output_stack(*stack);
	rc = tw_list_push(turn, new_element);
	if (rc == ERR_CREATE)
		printf("Не удалось выделить память под элемент\n");
	//else if (rc == ERR_OVERFLOW)
	//	printf("Стек заполнен\n");
	return rc;
}


void list_turn_work()
{
	tw_list turn;
	int choise, rc = input_list_turn(&turn);
	adress_stack_node_t *adresses = NULL;
	while (rc == OK)
	{
		printf("Выберите пункт меню (Выбор не из списка - 4 пункт):\n");
		printf("\t1. Добавить элемент \n");
		printf("\t2. Удалить элемент\n");
		printf("\t3. Вывести очередь\n");
		printf("\t4. Вывести очищенные ячейки памяти\n");
		printf("\t5. Очистить очередь (выведутся все использованные стеком ячейки и вы выйдете в главное меню)\n");

		rc = scanf("%d", &choise);
		if (rc != 1)
		{
			printf("Некорректный ввод\n");
			clearInputBuf();
			return;
		}
		rc = OK;
		//printf("choise = %d\n", choise);
		switch (choise)
		{
			case 1:
			{
				l_push(&turn);
				break;
			}
			case 2:
			{
				rc = tw_list_pop(&turn, &adresses);
				if (rc == ERR_OVERFLOW)
					printf("Очередь пуста\n");
				//printf("pop\n");
				//printf("rc = %d\n", rc);
				break;
			}
			case 3:
			{
				tw_list_output(turn);
				break;
			}
			case 4:
			{
				output_adresses(adresses);
				break;
			}
			case 5:
			{
				tw_list_free(&turn, &adresses);
				output_adresses(adresses);
				free_adresses(&adresses);
				return;
			}
			default:
			{
				tw_list_free(&turn, &adresses);
				return;
			}
		}
		rc = OK;
	}
}


int a_push(tw_array *turn)
{
	int new_element;
	printf("Введите элемент:\n");
	int rc = scanf("%d", &new_element);
	if (rc != 1)
	{
		printf("Некорректный ввод\n");
		//clearInputBuf();
		return ERR_INPUT;
	}
	//list_output_stack(*stack);
	rc = tw_array_push(turn, new_element);
	//if (rc == ERR_CREATE)
	//	printf("Не удалось выделить память под элемент\n");
	//else if (rc == ERR_OVERFLOW)
	//	printf("Стек заполнен\n");
	return rc;
}


void array_turn_work()
{
	tw_array turn;
	int choise, rc = input_array_turn(&turn);
	
	clearInputBuf();
	//adress_stack_node_t *adresses = NULL;
	while (rc == OK)
	{
		printf("Выберите пункт меню (Выбор не из списка - 4 пункт):\n");
		printf("\t1. Добавить элемент \n");
		printf("\t2. Удалить элемент\n");
		printf("\t3. Вывести очередь\n");
		//printf("\t4. Вывести очищенные ячейки памяти\n");
		printf("\t4. Очистить очередь (Выход в главное меню)\n");

		rc = scanf("%d", &choise);
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
				a_push(&turn);
				break;
			}
			case 2:
			{
				rc = tw_array_pop(&turn);//, &adresses);
				if (rc == ERR_OVERFLOW)
					printf("Очередь пуста\n");
				break;
			}
			case 3:
			{
				tw_array_output(turn);
				break;
			}
			//case 4:
			//{
			//	output_adresses(adresses);
			//	break;
			//}
			default:
			{
				tw_array_free(&turn);
			//	output_adresses(adresses);
			//	free_adresses(&adresses);
				clearInputBuf();
				return;
			}
		}
		rc = OK;
		clearInputBuf();
	}
}

void choise_turn_work()
{
	int choise = input_type_turn();
	if (choise == ARRAY_TURN)
		array_turn_work();
	else if (choise == LIST_TURN)
		list_turn_work();
}
