#include "../inc/help_functions.h"
#include "../inc/list_model.h"
#include "../inc/array_model.h"

// Случайное время в заданном интервале
my_time_t random_time(my_time_t tmax, my_time_t tmin)
{
	my_time_t res = (tmax - tmin) * (((double)rand())/RAND_MAX) + tmin;
	return res;
}

// ЗАЯВКА

// Создание
int create_request(request_t **new_request, int id, int time_entry)
{
	*new_request = calloc(1, sizeof(request_t));
	if (*new_request == NULL)
	{
		debug_print(DEBUG, "!!!WARNING Не удалось выделить память под заявку WARNING!!!\n");
		return ERR_CREATE;
	}

	(*new_request)->id = id;
	(*new_request)->time_entry = time_entry;

	return OK;
}

// Удаление
void delete_request(request_t **del_request)
{
	free(*del_request);
}


// ПЕРЕНАПРАВЛЕНИЕ ЗАЯВОК АВТОМАТАМИ

// Перенаправление автомата 1
int redirection1()
{
	int p, turn_id;

	p = rand() % 10 + 1;
	
	if (p <= 7)
		turn_id = ID_TURN_1;
	else
		turn_id = ID_TURN_2;

	return turn_id;
}

// Перенаправление автомата 2
int redirection2()
{
	return ID_TURN_1;
}

// ОДНОСВЯЗНЫЙ СПИСОК

// Создание узла
int create_node(list_node_t **new_node, void *element)
{
	*new_node = calloc(1, sizeof(list_node_t));

	if (*new_node == NULL)
	{
		debug_print(DEBUG, "!!!WARNING Не удалось выделить память под узел списка WARNING!!!\n");
		return ERR_CREATE;
	}

	(*new_node)->element = element;
	(*new_node)->next = NULL;
	return OK;
}

// Удаление узла
void delete_node(list_node_t **new_node)
{
	free(*new_node);
	*new_node = NULL;
}

// Добавление узла
void add_node(list_node_t **last, list_node_t *new_node)
{
	if ((*last) != NULL)
		(*last)->next = new_node;
	(*last) = new_node;
}

// Перемещение узла
list_node_t *remove_node(list_node_t **head)
{
	if (*head == NULL)
		return NULL;
	list_node_t *result = *head;
	*head = result->next;
	result->next = NULL;
	return result;
}

// Анализ и вывод результатов моделирования автоматов и очередей

void output_intermediat_result(int a2_calling, void *turn1, void *turn2, intermediat_result_t *(*get_intermediate)(void *turn))
{
	intermediat_result_t *res1 = get_intermediate(turn1);
	intermediat_result_t *res2 = get_intermediate(turn2);
	printf("Автомат А2 вызван %d раз\n", a2_calling);
	printf("\tТекущая длина очереди к А1: %lf\n", res1->current_len);
	printf("\tСредняя длина очереди к А1: %lf\n", res1->average_len);
	printf("\tТекущая длина очереди к А2: %lf\n", res2->current_len);
	printf("\tСредняя длина очереди к А2: %lf\n", res2->average_len);
	free(res1);
	free(res2);
}

final_result_t *get_final(void *turn1, void *turn2, automat_t a1, automat_t a2, my_time_t sys_time, 
	my_time_t (*get_av_time)(void *turn))
{
	final_result_t *res = calloc(1, sizeof(final_result_t));

	res->average_request_time1 = get_av_time(turn1);
	res->average_request_time2 += get_av_time(turn2);
	res->result_system_time = sys_time;
	res->a1_calling = a1.call_count;
	res->a2_down_time = a2.down_time;
	return res;
}

void output_final_result(void *turn1, void *turn2, automat_t a1, automat_t a2, my_time_t sys_time, 
	my_time_t (*get_av_time)(void *turn))
{
	final_result_t *res = get_final(turn1, turn2, a1, a2, sys_time, get_av_time);
	printf("Результаты моделирования\n");
	printf("\tВремя работы системы: %lf\n", res->result_system_time);
	printf("\tСреднее время нахождения заявки в очереди 1 = %lf\n", res->average_request_time1);
	printf("\tСреднее время нахождения заявки в очереди 2 = %lf\n", res->average_request_time2);
	printf("\tАвтомат 1 вызван %d раз\n", res->a1_calling);
	printf("\tАвтомат 2 простаивал %lf\n", res->a2_down_time);
	free(res);
}

// Очищение stdin

void clearInputBuf(void) 
{ 
      int garbageCollector; 
      while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF) 
      {}
}

// Напечатать линию

void output_line(int size)
{
	for(int i = 0; i <size; i++)
		printf("-");
	printf("\n");
}
