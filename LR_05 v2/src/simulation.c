#include "../inc/simulation.h"

int preparing_simulation(automat_t **a1, automat_t **a2, turn_t **t1, turn_t **t2)
{
	turns_list_node_t *t_node1, *t_node2, *head, *node;
	int rc;
	//printf("Start prepearing\n");

	rc = create_turn_node(&t_node1, TURN1_ID);
	if (rc != OK)
		return rc;
	//printf("Create turn 1 complete\n");
	start_fill_turn_1((t_node1->element));
	//printf("Fill turn 1 complete\n");

	rc = create_turn_node(&t_node2, TURN2_ID);
	if (rc != OK)
	{
		delete_turn_node(&t_node1);
		return rc;
	}
	//printf("Create turn 2 complete\n");

	add_turn_node(&node, &t_node2);
	head = node;
	add_turn_node(&node, &t_node1);
	//printf("Make turn list complete\n");
	//for (turns_list_node_t *cur = head; cur; cur = cur->next)
	//{
	//	printf("id turn = %d\n", cur->element->id);
	//}
	
	rc = create_automat(a1, AUTOMAT1_ID, AUTOMAT1_MIN_TIME, AUTOMAT1_MAX_TIME, head, beat1);
	//printf("Create automat 1 complete\n");
	if (rc != OK)
	{
		delete_turn_node(&t_node1);
		delete_turn_node(&t_node2);
		return rc;
	}

	rc = create_automat(a2, AUTOMAT2_ID, AUTOMAT2_MIN_TIME, AUTOMAT2_MAX_TIME, t_node2, beat2);
	//printf("Create automat 2 complete\n");
	if (rc != OK)
	{
		delete_turn_node(&t_node1);
		delete_turn_node(&t_node2);
		delete_automat(a1);
		return rc;
	}
	*t1 = t_node1->element;
	*t2 = t_node2->element;
	//printf("Prepearing complete!!!\n");
	return OK;
}

void write_event(requests_list_node_t **request, id_t worker, int work, sys_time_t cur_sys_time)
{
	events_list_node_t *event;
	int rc = create_event_node(&event, worker, work, cur_sys_time);
	if (rc != OK)
	{
		printf("Не удалось создать event\n");
	}
	add_event_node(&((*request)->element), &event);
	//(*request)->element;
}

void beat_for_automat(automat_t **a, turn_t **t, sys_time_t system_time)
{
	(*a)->call_count += 1;

	requests_list_node_t *new_r;
	turn_t *new_t;

	if ((*a)->element != NULL)
	{
		//printf("Из автомата в очередь\n");
		new_t = (*a)->beat((*a)->next_turns);  // нахожу новую очередь
		//printf("From %d to %d\n",(*a)->id, (new_t)->id);
		new_r = ((*a)->element);
		add_request_node(&(new_t), &new_r);
		(*a)->element = NULL;
		write_event(&(new_r), (*a)->id, EVENT_GO_OUT, system_time);
		write_event(&(new_r), (new_t)->id, EVENT_GO_IN, system_time);
		//printf("WRITE EVENT\n");
		//printf("Element id : %d\n", new_r->element->id);
		//output_events((new_r)->element->events);
		(new_t)->len += 1;
	}

	if ((*t)->len != 0)
	{
		//printf("Из очереди в автомат\n");
		(*a)->time_end_work = system_time + random_time((*a)->t_min, (*a)->t_max);
		//printf("From %d to %d\n",(*t)->id, (*a)->id);
		new_r = remove_request_node(t);
		(*t)->len -= 1;

		((*a)->element) = new_r;
		write_event(&(new_r), (*t)->id, EVENT_GO_OUT, system_time);
		write_event(&(new_r), (*a)->id, EVENT_GO_IN, system_time);
		//printf("WRITE EVENT\n");
		//printf("Element id : %d\n", new_r->element->id);
		//output_events((new_r)->element->events);
		//sleep(2);
	}
}

int simulation()
{
	automat_t *a1, *a2;
	turn_t *t1, *t2;

	sys_time_t system_time = 0;// cur_time1, cur_time2;
	int rc;
	rc = preparing_simulation(&a1, &a2, &t1, &t2);
	if (rc != OK)
		return rc;

	//output_all(*a1, *a2, *t1, *t2, system_time);
	while (a2->call_count < MAX_CALL_OA2_COUNT)
	{
		//output_all(*a1, *a2, *t1, *t2, system_time);
		if (a1->element == NULL && t1->len == 0)
		{
			//printf("Автомат 1 простаивает, ходит автомат 2\n");
			beat_for_automat(&a2, &t2, system_time);
			a1->downtime += a2->time_end_work - a1->time_end_work;
			a1->time_end_work = a2->time_end_work;

			system_time = a2->time_end_work;
		}
		else if (a2->element == NULL && t2->len == 0)
		{
			//printf("Автомат 2 простаивает, ходит автомат 1\n");
			beat_for_automat(&a1, &t1, system_time);
			a2->downtime += a1->time_end_work - a2->time_end_work;
			a2->time_end_work = a1->time_end_work;

			system_time = a1->time_end_work;

		}
		else 
		{
			//printf("a1->time_end_work = %lf, a2->time_end_work = %lf, a1->time_end_work - a2->time_end_work = %lf, EPS = %lf\n", a1->time_end_work, a2->time_end_work, a1->time_end_work - a2->time_end_work, EPS);
			if (fabs(a1->time_end_work - a2->time_end_work) < EPS)
			{
				//printf("Автоматы 1 и 2 ходят одновременно\n");
				beat_for_automat(&a1, &t1, system_time);
				beat_for_automat(&a2, &t2, system_time);
			}
			else if (a1->time_end_work < a2->time_end_work)
			{
				//printf("Автомат 1 ходит\n");
				beat_for_automat(&a1, &t1, system_time);
			}
			else if (a1->time_end_work > a2->time_end_work)
			{
				//printf("Автомат 2 ходит\n");
				beat_for_automat(&a2, &t2, system_time);
			}
			else
			{
				//printf("!!!!!!!!!YOU HAVE A VERY BIG PROBLEM IN MAIN WHILE!!!!!!!!!");
				break;
			}
			if (a1->time_end_work > a2->time_end_work)
			{
				system_time = a2->time_end_work;
			}
			else
			{
				system_time = a1->time_end_work;
			}
		}
	}

	output_all(*a1, *a2, *t1, *t2, system_time);
	return OK;
}