#include "../inc/array_model.h"

void array_output_turn(array_turn_t t1)
{
	debug_print(DEBUG, "\t Turn id = %d, ", t1.id);
	debug_print(DEBUG, "len = %d\n", t1.len);
	debug_print(DEBUG, "\t\t Turn Elements: ");

	for (request_t *i = t1.pout; i < t1.pin; i++)
	{
		debug_print(DEBUG, "%d, ", i->id);
	}
	debug_print(DEBUG, "\n");
}

void array_output_automat(automat_t a1)
{
	debug_print(DEBUG, "\tAutomat id = %d, ", a1.id);
	if (a1.current_request.id != -1)
	{
		debug_print(DEBUG, "Element id = %d, ", a1.current_request.id);
	}

	debug_print(DEBUG, "Downtime = %lf, ", a1.down_time);
	debug_print(DEBUG, "Ending work time = %lf, ", a1.work_ending_time);
	debug_print(DEBUG, "Call count = %d, ", a1.call_count);
	debug_print(DEBUG, "Next Turns\n")
	//for (list_node_t *cur = a1.next_turns; cur; cur = cur->next)
	//{
	//	output_turn(*(list_turn_t *)cur->element);
	//}
}

void array_output_all(automat_t a1, automat_t a2, array_turn_t t1, 
					  array_turn_t t2, my_time_t sys_time)
{
	debug_print(DEBUG, "\n\nSystem time = %lf\n", sys_time);
	array_output_turn(t1);
	array_output_turn(t2);
	array_output_automat(a1);
	array_output_automat(a2);
	debug_print(DEBUG, "\n\n")
}

void array_prepearing_turns(array_turn_t **t1, array_turn_t **t2)
{
	//debug_print(DEBUG, "Start prepearning turns\n");
	
	array_create_turn(t1, ID_TURN_1);
	//debug_print(DEBUG, "Creating 1 successfull\n");
	array_create_turn(t2, ID_TURN_2);
	//debug_print(DEBUG, "Creating 2 successfull\n");

	//array_output_turn(**t1);
	//array_output_turn(**t2);
	array_start_fill_turn(t1);
	(*t2)->pin = (*t2)->start;
	(*t2)->len = 0;
	//array_output_turn(**t1);
	//array_output_turn(**t2);
	//debug_print(DEBUG, "End prepearning turns\n");
}

void array_prearing_automats(automat_t *a1, automat_t *a2, array_turn_t **t1, 
							array_turn_t **t2)
{
	list_node_t *node1, *node2, *head, *last;

	//debug_print(DEBUG, "Start prepearning automat\n");
	
	//array_output_turn(**t1);
	//array_output_turn(**t2);

	create_node(&node1, *t1);
	create_node(&node2, *t2);
	head = node2;
	last = head;
	add_node(&last, node1);

	(a1)->id = ID_AUTOMAT_1;
	(a1)->current_request.id = -1;
	(a1)->next_turns = head;
	(a1)->work_ending_time = 0;
	(a1)->down_time = 0;
	(a1)->call_count = 0;
	(a1)->tmax = 6;
	(a1)->tmin = 0;
	(a1)->redirection = redirection1;


	(a2)->id = ID_AUTOMAT_2;
	(a2)->current_request.id = -1;
	(a2)->next_turns = node1;
	(a2)->work_ending_time = 0;
	(a2)->down_time = 0;
	(a2)->call_count = 0;
	(a2)->tmax = 8;
	(a2)->tmin = 1;
	(a2)->redirection = redirection2;

	//debug_print(DEBUG, "End prepearning automat\n");
}

// Перемещение заявки из автомата в очередь
void array_remove_from_automat_to_turn(array_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	request_t node;
	//request_t *request;
	//char d;
	//output_turn(**t1);

	// Добавление нового узла в очередь
	node = a1->current_request;
	//delete_request(a1->current_request->element);
	(*t1)->len++;
	//debug_print(DEBUG, "\n\n"); 

	// Обновление времени попадания заявки в новое место
	node.time_entry = sys_time;

	array_add_request(t1, node);
	//(*t1)->pin = (*t1)->pout + (*t1)->len;
	//scanf("%c", &d); 
	//debug_print(DEBUG, "\n\n");
	a1->current_request.id = -1;

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	//output_turn(**t1);
	//scanf("%c", &d);
}
// Перемещение заявки из очереди в автомат
void array_remove_from_turn_to_automat(array_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	request_t remove_request;
	//output_turn(**t1);
	
	// Удаление заявки из очереди

	remove_request = array_remove_request(t1);
	(*t1)->len--;
	if ((*t1)->pout == NULL)
		(*t1)->pin = NULL;

	//remove_request.time_entry = sys_time;

	// Добавление заявки в автомат
	a1->current_request = remove_request;
	//delete_node(&node);

	a1->work_ending_time = sys_time + random_time(a1->tmax, a1->tmin);
	//debug_print(DEBUG, "\n%lf, %lf, %lf\n", sys_time, random_time(a1->tmax, a1->tmin), a1->work_ending_time);
	//debug_print(DEBUG, "\n%lf, %lf\n", a1->tmax, a1->tmin);

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	// Подсчет измененного времени пребывания в очереди
	//printf("Turn id = %d, req id = %d, sys_time = %lf, request->entry_time = %lf, result = %lf\n", (*t1)->id,remove_request->id, sys_time, remove_request->time_entry, sys_time - remove_request->time_entry);
	(*t1)->time_av.sum += sys_time - remove_request.time_entry;
	(*t1)->time_av.count++;

	// Обновление времени попадания заявки в новое место
	//array_output_turn(**t1);
}

void array_beat(array_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	//debug_print(DEBUG, "\nSTART BEAT\n");
	//output_automat(*a1);
	if (a1->current_request.id != -1L)
	{
		a1->call_count++;
		int next_turn = a1->redirection();
		//debug_print(DEBUG, "1. From %d to %d\n", a1->id, next_turn);
		//output_automat(*a1);
		list_node_t *new_turn = array_find_turn_by_id(a1->next_turns, next_turn);
		array_turn_t *new_t = (array_turn_t *)new_turn->element;
		array_remove_from_automat_to_turn(&new_t, a1, sys_time);
	}
	if ((*t1)->len != 0)
	{
		//debug_print(DEBUG, "2. From %d to %d\n", (*t1)->id, a1->id);
		array_remove_from_turn_to_automat(t1, a1, sys_time);
	}
	//debug_print(DEBUG, "END BEAT\n\n");
}

my_time_t array_modeling(array_turn_t **t1, array_turn_t **t2, automat_t *a1, automat_t *a2, int condition)
{
	//array_turn_t *t1, *t2;
	//automat_t a1, a2;
	//array_prepearing_turns(&t1, &t2);
	//array_prearing_automats(&a1, &a2, &t1, &t2);

	my_time_t sys_time = 0;
	//char d;
	int i = 1;

	while (a2->call_count < STOP_AUTOMAT_CALL_COUNT)
	{
		//array_output_all(*a1, *a2, **t1, **t2, sys_time);
		//debug_print(DEBUG, "t1_len = %d, t2_len = %d\n", t1->len, t2->len);
		if (a1->current_request.id == -1 && (*t1)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 1 простаевает, автомат 2 работает\n");
			a1->down_time += a2->work_ending_time - a1->work_ending_time;
			a1->work_ending_time = sys_time;
			sys_time = a2->work_ending_time;
			array_beat(t2, a2, sys_time);
			//scanf("%c", &d);
		}
		else if (a2->current_request.id == -1 && (*t2)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 2 простаевает, автомат 1 работает\n");
			
			//output_automat(a1);
			a2->down_time += a1->work_ending_time - a2->work_ending_time;
			sys_time = a1->work_ending_time;
			a2->work_ending_time = sys_time;
			array_beat(t1, a1, sys_time);
		}
		else
		{
			if (fabs(a1->work_ending_time - a2->work_ending_time) < EPS)
			{
				//debug_print(DEBUG, "Автоматы 1 и 2 работают\n");
			
				array_beat(t1, a1, sys_time);
				array_beat(t2, a2, sys_time);
			}
			else if (a1->work_ending_time < a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 1 работает\n");
				array_beat(t1, a1, sys_time);
			}
			else if (a1->work_ending_time > a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 2 работает\n");
				array_beat(t2, a2, sys_time);
			}
			else
			{
				debug_print(DEBUG, "Невозможное случилось в if в главном while");
			}

			if (a1->work_ending_time > a2->work_ending_time)
			{
				sys_time = a2->work_ending_time;
			}
			else
				sys_time = a1->work_ending_time;
		}
		if (a2->call_count == i*100 && condition == SHOW)
		{
			output_intermediat_result(a2->call_count, *t1, t2, get_array_intermediate);
			i++;
		}
		//scanf("%c", &d);
	}
	//array_output_all(a1, a2, *t1, *t2, sys_time);
	return sys_time;
}
