#include "../inc/automat_func.h"

turns_list_node_t *find_turn_by_id(turns_list_node_t *next_turns, id_t find_turn_id)
{
	for (turns_list_node_t *cur = next_turns; cur; cur = cur->next)
	{
		//printf("cur = %d \n", cur->element->id);
		if (cur->element->id == find_turn_id)
		{
			return cur;
		} 
	}
	return NULL;
}

// Автомат 1 (такт)
turn_t *beat1(turns_list_node_t *next_turns)
{
	id_t find_turn_id;
	int p = rand()%10 + 1;
	if (p > 7)
	{
		find_turn_id = TURN2_ID;
	}
	else
	{
		find_turn_id = TURN1_ID;
	}
	//printf("turn id = %d\n", find_turn_id);
	turns_list_node_t *result = find_turn_by_id(next_turns, find_turn_id);
	//if (result == NULL)
	//{
	//	printf("You have a big problem\n");
	//}
	//printf("turn id = %d\n", find_turn_id);
	return result->element;
}

// Автомат 2 (такт)
turn_t *beat2(turns_list_node_t *next_turns)
{
	id_t find_turn_id = TURN1_ID;
	turns_list_node_t *result = find_turn_by_id(next_turns, find_turn_id);
	return result->element;

}

//Случайное время
sys_time_t random_time(sys_time_t tmin, sys_time_t tmax)
{
	sys_time_t result = (tmax - tmin)*((double)rand())/(RAND_MAX) + tmin;
	return result;
}

// Начальное заполнение очереди заявками

int start_fill_turn_1(turn_t *turn)
{
	requests_list_node_t *new_node;
	int id = START_REQUEST_ID;
	//output_turn(*turn, 0);
	for (int i = 0; i < START_REQUEST_TURN_OA1; i++, id++)
	{
		//printf("Iteration i = %d\n", i);
		create_request_node(&new_node, id);
		//printf("Create request success\n");
		add_request_node(&turn, &new_node);
		//printf("Add request success\n");
		if (i == 0)
		{
			turn->pout = turn->pin;
		}
		turn->len += 1;
	}
	//output_turn(*turn, 0);
	return OK;
}