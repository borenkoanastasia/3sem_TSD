#include "../inc/list_model.h"

void list_output_turn(list_turn_t t1)
{
	debug_print(DEBUG, "\t Turn id = %d, ", t1.id);
	debug_print(DEBUG, "len = %d\n", t1.len);
	debug_print(DEBUG, "\t\t Turn Elements: ");

	for (list_node_t *cur_node = t1.pout; cur_node; cur_node = cur_node->next)
	{
		debug_print(DEBUG, "%d, ", ((request_t *)cur_node->element)->id);
	}
	debug_print(DEBUG, "\n");
}

void list_output_automat(automat_t a1)
{
	debug_print(DEBUG, "\tAutomat id = %d, ", a1.id);
	if (a1.current_request != NULL)
	{
		debug_print(DEBUG, "Element id = %d, ", ((request_t *)(a1.current_request->element))->id);
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

void list_output_all(automat_t a1, automat_t a2, list_turn_t t1, list_turn_t t2, my_time_t sys_time)
{
	debug_print(DEBUG, "\n\nSystem time = %lf\n", sys_time);
	list_output_turn(t1);
	list_output_turn(t2);
	list_output_automat(a1);
	list_output_automat(a2);
	debug_print(DEBUG, "\n\n")
}

void list_prepearing_turns(list_turn_t **t1, list_turn_t **t2)
{
	//debug_print(DEBUG, "Start prepearning turns\n");
	
	list_create_turn(t1, ID_TURN_1);
	//debug_print(DEBUG, "Creating 1 successfull\n");
	list_create_turn(t2, ID_TURN_2);
	(*t2)->len = 0;
	(*t2)->pin = NULL;
	(*t2)->pout = NULL;
	//debug_print(DEBUG, "Creating 2 successfull\n");

	//list_output_turn(**t1);
	//list_output_turn(**t2);
	list_start_fill_turn(t1);
	//list_output_turn(**t1);
	//list_output_turn(**t2);
	//debug_print(DEBUG, "End prepearning turns\n");
}

void list_prepearing_automats(automat_t *a1, automat_t *a2, list_turn_t **t1, list_turn_t **t2)
{
	list_node_t *node1, *node2, *head, *last;

	//debug_print(DEBUG, "Start prepearning automat\n");
	
	//list_output_turn(**t1);
	//list_output_turn(**t2);

	create_node(&node1, *t1);
	create_node(&node2, *t2);
	head = node2;
	last = head;
	add_node(&last, node1);

	(a1)->id = ID_AUTOMAT_1;
	(a1)->current_request = NULL;
	(a1)->next_turns = head;
	(a1)->work_ending_time = 0;
	(a1)->down_time = 0;
	(a1)->call_count = 0;
	(a1)->tmax = 6;
	(a1)->tmin = 0;
	(a1)->redirection = redirection1;


	(a2)->id = ID_AUTOMAT_2;
	(a2)->current_request = NULL;
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
void list_remove_from_automat_to_turn(list_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	list_node_t *node, *last = (*t1)->pin;
	request_t *request;
	//char d;
	//output_turn(**t1);

	// Добавление нового узла в очередь
	node = a1->current_request;
	//debug_print(DEBUG, "\n\n"); 
	add_node(&last, node);
	if ((*t1)->pout == NULL)
		(*t1)->pout = last;
	(*t1)->len++;
	(*t1)->pin = last;
	//scanf("%c", &d); 
	//debug_print(DEBUG, "\n\n");
	a1->current_request = NULL;

	//Получение самой заявки из узла очереди
	request = (request_t *)node->element;

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	// Обновление времени попадания заявки в новое место
	request->time_entry = sys_time;
	//output_turn(**t1);
	//scanf("%c", &d);
}
// Перемещение заявки из очереди в автомат
void list_remove_from_turn_to_automat(list_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	list_node_t *node;
	request_t *request;
	//output_turn(**t1);
	
	// Удаление заявки из очереди
	node = remove_node(&((*t1)->pout));
	(*t1)->len--;
	if ((*t1)->pout == NULL)
		(*t1)->pin = NULL;

	// Добавление заявки в автомат
	a1->current_request = node;

	//Получение самой заявки из узла очереди
	request = (request_t *)node->element;

	a1->work_ending_time = sys_time + random_time(a1->tmax, a1->tmin);
	//debug_print(DEBUG, "\n%lf, %lf, %lf\n", sys_time, random_time(a1->tmax, a1->tmin), a1->work_ending_time);
	//debug_print(DEBUG, "\n%lf, %lf\n", a1->tmax, a1->tmin);

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	// Подсчет измененного времени пребывания в очереди
	//printf("sys_time = %lf, request->entry_time = %lf, result = %lf\n", sys_time, request->time_entry, sys_time - request->time_entry);
	(*t1)->time_av.sum += sys_time - request->time_entry;
	(*t1)->time_av.count++;

	// Обновление времени попадания заявки в новое место
	request->time_entry = sys_time;
	//output_turn(**t1);
}

void list_beat(list_turn_t **t1, automat_t *a1, my_time_t sys_time)
{
	//debug_print(DEBUG, "\nSTART BEAT\n");
	//output_automat(*a1);
	if (a1->current_request != NULL)
	{
		a1->call_count++;
		int next_turn = a1->redirection();
		//debug_print(DEBUG, "1. From %d to %d\n", a1->id, next_turn);
		//output_automat(*a1);
		list_node_t *new_turn = list_find_turn_by_id(a1->next_turns, next_turn);
		list_turn_t *new_t = (list_turn_t *)new_turn->element;
		list_remove_from_automat_to_turn(&new_t, a1, sys_time);
	}
	if ((*t1)->len != 0)
	{
		//debug_print(DEBUG, "2. From %d to %d\n", (*t1)->id, a1->id);
		list_remove_from_turn_to_automat(t1, a1, sys_time);
	}
	//debug_print(DEBUG, "END BEAT\n\n");
}

my_time_t list_modeling(list_turn_t **t1, list_turn_t **t2, automat_t *a1, automat_t *a2, int condition)
{
	//list_turn_t *t1, *t2;
	//automat_t a1, a2;
	//list_prearing_turns(&t1, &t2);
	//list_prearing_automats(&a1, &a2, &t1, &t2);

	my_time_t sys_time = 0;
	//char d;
	int i = 1;

	while (a2->call_count < STOP_AUTOMAT_CALL_COUNT)
	{
		//list_output_all(*a1, *a2, **t1, **t2, sys_time);
		//debug_print(DEBUG, "t1_len = %d, t2_len = %d\n", (*t1)->len, (*t2)->len);
		if (a1->current_request == NULL && (*t1)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 1 простаевает, автомат 2 работает\n");
			a1->down_time += a2->work_ending_time - a1->work_ending_time;
			a1->work_ending_time = sys_time;
			sys_time = a2->work_ending_time;
			list_beat(t2, a2, sys_time);
			//scanf("%c", &d);
		}
		else if (a2->current_request == NULL && (*t2)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 2 простаевает, автомат 1 работает\n");
			
			//output_automat(a1);
			a2->down_time += a1->work_ending_time - a2->work_ending_time;
			sys_time = a1->work_ending_time;
			a2->work_ending_time = sys_time;
			list_beat(t1, a1, sys_time);
		}
		else
		{
			if (fabs(a1->work_ending_time - a2->work_ending_time) < EPS)
			{
				//debug_print(DEBUG, "Автоматы 1 и 2 работают\n");
			
				list_beat(t1, a1, sys_time);
				list_beat(t2, a2, sys_time);
			}
			else if (a1->work_ending_time < a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 1 работает\n");
				list_beat(t1, a1, sys_time);
			}
			else if (a1->work_ending_time > a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 2 работает\n");
				list_beat(t2, a2, sys_time);
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
			//printf("len = %d, sum = %lf, count = %d\n", (*t2)->len, 
			//	(*t2)->time_av.sum, (*t2)->time_av.count);
			output_intermediat_result(a2->call_count, *t1, *t2, get_list_intermediate);
			i++;
		}
		//scanf("%c", &d);
	}
	//list_output_all(a1, a2, *t1, *t2, sys_time);
	//list_delete_turn(&t1);
	//list_delete_turn(&t2);
	//delete_node(&(a1.next_turns->next));
	//delete_node(&(a1.next_turns));
	return sys_time;
}


/*
// Перемещение заявки из автомата в очередь
void adress_list_remove_from_automat_to_turn(list_turn_t **t1, automat_t *a1, my_time_t sys_time, adress_stack_node_t *adresses)
{
	list_node_t *node, *last = (*t1)->pin;
	request_t *request;
	//char d;
	//output_turn(**t1);

	// Добавление нового узла в очередь
	node = a1->current_request;
	//debug_print(DEBUG, "\n\n"); 
	add_node(&last, node);
	if ((*t1)->pout == NULL)
		(*t1)->pout = last;
	(*t1)->len++;
	(*t1)->pin = last;
	//scanf("%c", &d); 
	//debug_print(DEBUG, "\n\n");
	a1->current_request = NULL;

	//Получение самой заявки из узла очереди
	request = (request_t *)node->element;

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	// Обновление времени попадания заявки в новое место
	request->time_entry = sys_time;
	//output_turn(**t1);
	//scanf("%c", &d);
}
// Перемещение заявки из очереди в автомат
void adress_list_remove_from_turn_to_automat(list_turn_t **t1, automat_t *a1, my_time_t sys_time, adress_stack_node_t *adresses)
{
	list_node_t *node;
	request_t *request;
	//output_turn(**t1);
	
	// Удаление заявки из очереди
	node = remove_node(&((*t1)->pout));
	(*t1)->len--;
	if ((*t1)->pout == NULL)
		(*t1)->pin = NULL;

	// Добавление заявки в автомат
	a1->current_request = node;

	//Получение самой заявки из узла очереди
	request = (request_t *)node->element;

	a1->work_ending_time = sys_time + random_time(a1->tmax, a1->tmin);
	//debug_print(DEBUG, "\n%lf, %lf, %lf\n", sys_time, random_time(a1->tmax, a1->tmin), a1->work_ending_time);
	//debug_print(DEBUG, "\n%lf, %lf\n", a1->tmax, a1->tmin);

	// Подсчет измененной длины
	(*t1)->len_av.sum += (*t1)->len;
	(*t1)->len_av.count++;

	// Подсчет измененного времени пребывания в очереди
	//printf("sys_time = %lf, request->entry_time = %lf, result = %lf\n", sys_time, request->time_entry, sys_time - request->time_entry);
	(*t1)->time_av.sum += sys_time - request->time_entry;
	(*t1)->time_av.count++;

	// Обновление времени попадания заявки в новое место
	request->time_entry = sys_time;
	//output_turn(**t1);
}

void adress_list_beat(list_turn_t **t1, automat_t *a1, my_time_t sys_time, adress_stack_node_t *adresses)
{
	//debug_print(DEBUG, "\nSTART BEAT\n");
	//output_automat(*a1);
	if (a1->current_request != NULL)
	{
		a1->call_count++;
		int next_turn = a1->redirection();
		//debug_print(DEBUG, "1. From %d to %d\n", a1->id, next_turn);
		//output_automat(*a1);
		list_node_t *new_turn = list_find_turn_by_id(a1->next_turns, next_turn);
		list_turn_t *new_t = (list_turn_t *)new_turn->element;
		list_remove_from_automat_to_turn(&new_t, a1, sys_time);
	}
	if ((*t1)->len != 0)
	{
		//debug_print(DEBUG, "2. From %d to %d\n", (*t1)->id, a1->id);
		list_remove_from_turn_to_automat(t1, a1, sys_time);
	}
	//debug_print(DEBUG, "END BEAT\n\n");
}

my_time_t adress_list_modeling(list_turn_t **t1, list_turn_t **t2, automat_t *a1, automat_t *a2, int condition, adress_stack_node_t *adresses)
{
	//list_turn_t *t1, *t2;
	//automat_t a1, a2;
	//list_prearing_turns(&t1, &t2);
	//list_prearing_automats(&a1, &a2, &t1, &t2);

	my_time_t sys_time = 0;
	//char d;
	int i = 1;

	while (a2->call_count < STOP_AUTOMAT_CALL_COUNT)
	{
		//list_output_all(*a1, *a2, **t1, **t2, sys_time);
		//debug_print(DEBUG, "t1_len = %d, t2_len = %d\n", (*t1)->len, (*t2)->len);
		if (a1->current_request == NULL && (*t1)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 1 простаевает, автомат 2 работает\n");
			a1->down_time += a2->work_ending_time - a1->work_ending_time;
			a1->work_ending_time = sys_time;
			sys_time = a2->work_ending_time;
			list_beat(t2, a2, sys_time);
			//scanf("%c", &d);
		}
		else if (a2->current_request == NULL && (*t2)->len == 0)
		{
			//debug_print(DEBUG, "Автомат 2 простаевает, автомат 1 работает\n");
			
			//output_automat(a1);
			a2->down_time += a1->work_ending_time - a2->work_ending_time;
			sys_time = a1->work_ending_time;
			a2->work_ending_time = sys_time;
			list_beat(t1, a1, sys_time);
		}
		else
		{
			if (fabs(a1->work_ending_time - a2->work_ending_time) < EPS)
			{
				//debug_print(DEBUG, "Автоматы 1 и 2 работают\n");
			
				list_beat(t1, a1, sys_time);
				list_beat(t2, a2, sys_time);
			}
			else if (a1->work_ending_time < a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 1 работает\n");
				list_beat(t1, a1, sys_time);
			}
			else if (a1->work_ending_time > a2->work_ending_time)
			{
				//debug_print(DEBUG, "Автомат 2 работает\n");
				list_beat(t2, a2, sys_time);
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
			//printf("len = %d, sum = %lf, count = %d\n", (*t2)->len, 
			//	(*t2)->time_av.sum, (*t2)->time_av.count);
			output_intermediat_result(a2->call_count, *t1, *t2, get_list_intermediate);
			i++;
		}
		//scanf("%c", &d);
	}
	//list_output_all(a1, a2, *t1, *t2, sys_time);
	//list_delete_turn(&t1);
	//list_delete_turn(&t2);
	//delete_node(&(a1.next_turns->next));
	//delete_node(&(a1.next_turns));
	return sys_time;
}
*/