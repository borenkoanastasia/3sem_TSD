#include "../inc/types_work.h"
#include "../inc/lists_work.h"
// Работа с обычными типами (создать, удалить)

// Создание
int create_event(event_t **new, id_t worker, int work, sys_time_t cur_sys_time)
{
	*new = calloc(1, sizeof(event_t));
	if (*new == NULL)
	{
		return ERR_CREATE;
	}
	(*new)->worker = worker;
	(*new)->work_num = work;
	(*new)->event_time = cur_sys_time;

	return OK;
}

int create_request(request_t **new, id_t id)
{
	*new = calloc(1, sizeof(request_t));
	if (*new == NULL)
	{
		return ERR_CREATE;
	}

	(*new)->id = id;
	(*new)->events = NULL;
	(*new)->last_event = NULL;
	
	return OK;
}

int create_turn(turn_t **new, id_t id)
{
	*new = calloc(1, sizeof(turn_t));
	if (*new == NULL)
	{
		return ERR_CREATE;
	}
	
	(*new)->id = id;
	(*new)->pin = NULL;
	(*new)->pout = NULL;
	(*new)->average.sum = 0;
	(*new)->average.count = 0;
	
	return OK;
}

int create_automat(automat_t **new, id_t id, sys_time_t tmin, sys_time_t tmax, turns_list_node_t *next_turns, 
	turn_t *(*beat)(turns_list_node_t *next_turns))
{
	*new = calloc(1, sizeof(automat_t));
	if (*new == NULL)
	{
		return ERR_CREATE;
	}
	
	(*new)->id = id;
	(*new)->element = NULL;

	(*new)->t_min = tmin;
	(*new)->t_max = tmax;

	(*new)->time_end_work = 0;
	(*new)->downtime = 0;
	(*new)->call_count = 0;

	(*new)->next_turns = next_turns;

	(*new)->beat = beat;
	
	return OK;
}

// Удаление

void delete_event(event_t **event)
{
	free(*event);
}

void delete_request(request_t **request)
{
	free(*request);
};

void delete_turn(turn_t **turn)
{
	free(*turn);
};

void delete_automat(automat_t **automat)
{
	//clear_turn_list(&((*automat)->next_turns));
	free(*automat);
};

// Вывод всего
void output_events(events_list_node_t *head)
{
	printf("Events log\n");
	for (events_list_node_t *cur = head; cur; cur = cur->next)
	{
		printf("%15s| %d ", "Worker id", cur->element->worker);
		if (cur->element->work_num == EVENT_GO_OUT)
		{
			printf("|%15s| go out |", "Work");
		}
		else
		{
			printf("|%15s| go in |", "Work");
		}
		printf("%15s| %lf\n", "System time", cur->element->event_time);
	}
	printf("\n");
}

void output_turn(turn_t t, int buf)
{
	printf("\tTurn id = %d, len = %d\n", t.id, t.len);
	printf("\t\tRequests ides\n");
	for (requests_list_node_t *cur = t.pout; cur; cur = cur->next)
	{
		printf("%d, \t", cur->element->id);
		if (buf == 0)
		{
			output_events(cur->element->events);
		}
	}
	printf("\n");
}

void output_automat(automat_t a1)
{
	printf("\tAutomat id = %d, \t", a1.id);
	if (a1.element != NULL)
		printf("Element in work: id = %d, ", a1.element->element->id);
	printf("Work ending in: time = %lf, ", a1.time_end_work);
	printf("Called %d times, ", a1.call_count);
	printf("Downtime = %lf ", a1.downtime);
	printf("\n");
}

void output_all(automat_t a1, automat_t a2, turn_t t1, turn_t t2, sys_time_t system_time)
{
	int buf = 1;
	printf("\n\nSystem_time = %lf\n", system_time);
	printf("\tTurn 1\n");
	output_turn(t1, buf);
	printf("\tTurn 2\n");
	output_turn(t2, buf);	
	output_automat(a1);	
	output_automat(a2);
}