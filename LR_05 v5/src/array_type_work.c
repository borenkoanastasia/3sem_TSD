#include "../inc/array_model.h"

// Поиск очереди по id
list_node_t *array_find_turn_by_id(list_node_t *head, int turn_id)
{
	for (list_node_t *cur = head; cur; cur = cur->next)
	{
		//output_turn(*((list_turn_t *)(cur->element)));
		//debug_print(DEBUG, "%d\n", turn_id);
		
		if (((array_turn_t *)(cur->element))->id == turn_id)
		{
			return cur;
		}
	}
	debug_print(DEBUG, "!!!WARNING Пытаешься найти очередь которой нет WARNING!!!\n");
	return NULL;
}

int array_create_turn(array_turn_t **turn, int id)
{
	*turn = calloc(1, sizeof(array_turn_t));
	if (*turn == NULL)
	{
		debug_print(DEBUG, "!!!WARNING Не удалось выделить память под очередь WARNING!!!\n");
		return ERR_CREATE;
	}

	(*turn)->id = id;
	(*turn)->start = calloc(MAX_REQUEST_COUNT + 2, sizeof(request_t));
	(*turn)->pin = (*turn)->start;
	(*turn)->pout = (*turn)->start;
	(*turn)->max_len = MAX_REQUEST_COUNT;
	return OK;
}

void array_delete_turn(array_turn_t **turn)
{
	free((*turn)->start);
	free(*turn);
}

void array_start_fill_turn(array_turn_t **turn)
{
	(*turn)->pout = (*turn)->start;
	(*turn)->pin = (*turn)->pout;
	request_t request;
	request.time_entry = 0;
	for (int i = 0; i < REQUEST_AMOUNT; i++)
	{
		//printf("pout = %ld, pin = %ld, delta = %ld\n", (long int)(*turn)->pout, (long int)(*turn)->pin, (long int)(*turn)->pout - (long int)(*turn)->pin);
		//array_output_turn(**turn);
		request.id = i + 1;
		array_add_request(turn, request);
		//printf("i = %d ", i);
		(*turn)->len++;
	}
}

void array_add_request(array_turn_t **turn, request_t request)
{
	*((*turn)->pin) = request;
	(*turn)->pin++;
}

request_t array_remove_request(array_turn_t **turn)
{
	request_t request = *((*turn)->pout);
	//(*turn)->pout = *request;
	if ((*turn)->pout == (*turn)->pin)
		return request;
	//add_adresses(&Adress_Reester, (long int)(*turn)->pout);
	for (request_t *cur = (*turn)->pout; cur < (*turn)->pin; cur++)
		*cur = *(cur + 1);
	(*turn)->pin--;
	return request;
}

intermediat_result_t *get_array_intermediate(void *turn)
{
	intermediat_result_t *res = calloc(1, sizeof(intermediat_result_t));
	res->current_len = ((array_turn_t *)turn)->len;
	res->average_len = ((array_turn_t *)turn)->len_av.sum/((array_turn_t *)turn)->len_av.count;
	return res;
}

my_time_t array_get_average_time(void *turn)
{
	//printf("sum = %lf, count = %d\n", ((array_turn_t *)turn)->time_av.sum, ((array_turn_t *)turn)->time_av.count);
	return (((array_turn_t *)turn)->time_av.sum/((array_turn_t *)turn)->time_av.count);
}
