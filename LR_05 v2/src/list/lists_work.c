#include "../inc/lists_work.h"

// Работа со списками/очередями (создать узел, удалить узел, добавить узел, отсоеденить узел, 
//                               очищение списка)


// Создание узла

int create_event_node(events_list_node_t **new, id_t worker, int work, sys_time_t cur_sys_time)
{
	*new = calloc(1, sizeof(events_list_node_t));
	if (*new == NULL)
		return ERR_CREATE;

	event_t *new_event;
	int rc = create_event(&new_event, worker, work, cur_sys_time);
	if (rc != OK)
	{
		free(*new);
		return rc;
	}

	(*new)->element = new_event;
	(*new)->next = NULL;

	return OK;
}

int create_request_node(requests_list_node_t **new, id_t id)
{
	*new = calloc(1, sizeof(requests_list_node_t));
	if (*new == NULL)
		return ERR_CREATE;

	request_t *new_request;
	int rc = create_request(&new_request, id);
	if (rc != OK)
	{
		free(*new);
		return rc;
	}

	(*new)->element = new_request;
	(*new)->adress = (long int)*new;
	(*new)->next = NULL;

	return OK;
}

int create_turn_node(turns_list_node_t **new, id_t id)
{
	*new = calloc(1, sizeof(turns_list_node_t));
	if (*new == NULL)
		return ERR_CREATE;

	turn_t *new_turn;
	int rc = create_turn(&new_turn, id);
	if (rc != OK)
	{
		free(*new);
		return rc;
	}

	(*new)->element = new_turn;
	(*new)->next = NULL;

	return OK;
}

// Удаление узла

void delete_event_node(events_list_node_t **new)
{
	delete_event(&((*new)->element));
	free(*new);
}

void delete_request_node(requests_list_node_t **new)
{
	delete_request(&((*new)->element));
	free(*new);
}

void delete_turn_node(turns_list_node_t **new)
{
	delete_turn(&((*new)->element));
	free(*new);
}


// Добавление узла

void add_event_node(request_t **request, events_list_node_t **new)
{
	if ((*request)->last_event != NULL)
	{
		((*request)->last_event)->next = *new;
	}
	else
	{
		(*request)->events = *new;
	}
	((*request)->last_event) = *new;
}

void add_request_node(turn_t **turn, requests_list_node_t **new)
{
	if ((*turn)->pin != NULL)
	{
		(*turn)->pin->next = *new;
	}
	else
	{
		(*turn)->pout = *new;
	}
	(*turn)->pin = *new;
}

void add_turn_node(turns_list_node_t **last_turn, turns_list_node_t **new)
{
	if (*last_turn != NULL)
	{
		(*last_turn)->next = *new;
	}
	(*last_turn) = *new;
}

// Отсоединение узла

requests_list_node_t *remove_request_node(turn_t **turn)
{
	requests_list_node_t *excess = ((*turn)->pout);
	((*turn)->pout) = excess->next;
	excess->next = NULL;

	if ((*turn)->pout == NULL)
	{
		(*turn)->pin = NULL;
		//(*turn)->len = 0;
	}

	return excess;
}

// Очищение списка

void clear_event_list(events_list_node_t **head)
{
	for (events_list_node_t *cur = (*head)->next; head; cur = cur->next)
	{
		delete_event_node(head);
		*head = cur;
	}
}

void clear_request_list(requests_list_node_t **head)
{
	for (requests_list_node_t *cur = (*head)->next; head; cur = cur->next)
	{
		delete_request_node(head);
		*head = cur;
	}
}

void clear_turn_list(turns_list_node_t **head)
{
	for (turns_list_node_t *cur = (*head)->next; head; cur = cur->next)
	{
		delete_turn_node(head);
		*head = cur;
	}
}
