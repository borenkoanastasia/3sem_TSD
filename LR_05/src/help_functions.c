#include "common.h"

// Добавляет элемент в очередь
int add_element(turn_t *oa, int element)
{
	turn_node_t *new_node = calloc(1, sizeof(turn_node_t));
	if (new_node == NULL)
		return ERR_CREATE;
	new_node->element = element
	oa->pin->next = new_node;
	oa->pin = new_node;
	oa->len += 1;
	return OK;
}

// Удаляет элемент из очереди
void del_element(turn_t *oa, int element)
{
	turn_node_t *del_el = oa->pout;
	oa->pout = oa->pout->next; 
	free(del_el);
	oa->len -= 1;
}

// Заполнение очереди стартовым кол-вом элементов
int fill_turn(turn_t *oa)
{
	int rc;
	for (int i = 0; i < START_OA1_TASKS; i++)
	{
		rc = add_element(oa, i);
		if (rc != OK)
			return rc;
		oa->len += 1;
	}
	return OK;
}

// Определяет время работы автомата 1 случайным образом
float random_time_1()
{
	float time1 = rand()%7;
	return time1;
}

// Определяет время работы автомата 2 случайным образом
float random_time_2()
{
	float time2 = rand()%8 + 1;
	return time2;
}

// Определяет следущую очередь для айвки прошедшей первый автомат
int random_p()
{
	int next = rand()%10 + 1;
	if (next > 7)
	{
		return NEXT_OA2;
	}
	return NEXT_OA1;
}

// Такт автомата ОА1
int beat_oa1(turn_t *oa1, turn_t *oa2)
{
	int next_turn = random_p();
	if (next_turn == NEXT_OA1)
	{
		add_element(oa2, oa1->pout->element);
	}
	else
	{
		add_element(oa1, oa1->pout->element);	
	}
	del_element(oa1);
	return random_time_1();
}

// Такт автомата ОА2
int beat_oa2(turn_t *oa1, turn_t *oa2)
{
	add_element(oa1, oa2->pout->element);
	del_element(oa2);
	return random_time_2();
}
