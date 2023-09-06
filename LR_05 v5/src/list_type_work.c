#include "../inc/list_model.h"

// Очередь 

int list_create_turn(list_turn_t **turn, int id)
{
	*turn = calloc(1, sizeof(list_turn_t));
	if (*turn == NULL)
	{
		debug_print(DEBUG, "!!!WARNING Не удалось выделить память под очередь WARNING!!!\n");
		return ERR_CREATE;
	}

	(*turn)->id = id;
	(*turn)->pin = NULL;
	(*turn)->pout = NULL;
	(*turn)->len = 0;
	(*turn)->len_av.sum = 0;
	(*turn)->len_av.count = 0;
	(*turn)->time_av.sum = 0;
	(*turn)->time_av.count = 0;
	return OK;
}

void list_delete_turn(list_turn_t **turn)
{
	if ((*turn)->pout == NULL)
	{
		return;
	}
	for (list_node_t *cur = (*turn)->pout->next; cur; cur = cur->next)
	{
		free((*turn)->pout->element);
		free((*turn)->pout);

		(*turn)->pout = cur;
	}
	free((*turn)->pout->element);
	free((*turn)->pout);
	free(*turn);
}

void list_start_fill_turn(list_turn_t **turn)
{
	request_t *r;
	list_node_t *node;
	for (int i = 0; i < REQUEST_AMOUNT; i++)
	{
		create_request(&r, i + 1, 0);
		create_node(&node, r);
		add_node(&((*turn)->pin), node);
		(*turn)->len += 1;
		if (i == 0)
		{
			(*turn)->pout = (*turn)->pin;
		}
		//debug_print(DEBUG, "i = %d, request->id = %d, node->request_id = %d, turn->node->request->id = %d\n", 
		//	i, r->id, ((request_t *)node->element)->id, ((request_t *)(*turn)->pin->element)->id);
		//output_turn(**turn);
	}
	(*turn)->len_av.sum = (*turn)->len;
	(*turn)->len_av.count = 1;
}

// Поиск очереди по id
list_node_t *list_find_turn_by_id(list_node_t *head, int turn_id)
{
	for (list_node_t *cur = head; cur; cur = cur->next)
	{
		//output_turn(*((list_turn_t *)(cur->element)));
		//debug_print(DEBUG, "%d\n", turn_id);
		
		if (((list_turn_t *)(cur->element))->id == turn_id)
		{
			return cur;
		}
	}
	debug_print(DEBUG, "!!!WARNING Пытаешься найти очередь которой нет WARNING!!!\n");
	return NULL;
}

// Анализ результатов
intermediat_result_t *get_list_intermediate(void *turn)
{
	intermediat_result_t *res = calloc(1, sizeof(intermediat_result_t));
	res->current_len = ((list_turn_t *)turn)->len;
	//printf("len = %d, sum = %lf, count = %d\n", ((list_turn_t *)turn)->len, 
	//	((list_turn_t *)turn)->time_av.sum, ((list_turn_t *)turn)->time_av.count);
	res->average_len = ((list_turn_t *)turn)->len_av.sum/((list_turn_t *)turn)->len_av.count;
	return res;
}


my_time_t list_get_average_time(void *turn)
{
	//printf("sum = %lf, count = %d\n", ((list_turn_t *)turn)->time_av.sum, ((list_turn_t *)turn)->time_av.count);
	return (((list_turn_t *)turn)->time_av.sum/((list_turn_t *)turn)->time_av.count);
}

int list_turn_push(list_turn_t **turn, request_t *element)
{
	list_node_t *node = calloc(1, sizeof(list_node_t));
	if (node == NULL)
		return ERR_CREATE;
	(node->element) = element;
	if ((*turn)->pin == NULL)
	{
		(*turn)->pout = node;
		(*turn)->pin = node;
	}
	else
	{
		(*turn)->pin->next = node;
		(*turn)->pin = node;
	}
	return OK;
}
int list_turn_pop(list_turn_t **turn, request_t *del_request, adress_stack_node_t **head)
{
	if (turn == NULL)
	{
		return ERR_OVERFLOW;
	}
	list_node_t *del_node = (*turn)->pout;
	*del_request = (*(request_t *)(del_node->element));
	add_adresses(head, (long int)(*turn)->pout);
	(*turn)->pout = del_node->next;
	free(del_node->element);
	free(del_node);
	return OK;
}

int time_list_turn_pop(list_turn_t **turn, request_t *del_request)
{
	if (turn == NULL)
	{
		return ERR_OVERFLOW;
	}
	list_node_t *del_node = (*turn)->pout;
	*del_request = (*(request_t *)(del_node->element));
	(*turn)->pout = del_node->next;
	free(del_node->element);
	free(del_node);
	return OK;
}
