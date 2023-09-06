#ifndef HELP_FUNCTIONS_H
#define HELP_FUNCTIONS_H

#include "common.h"
//#include "adress_work.h"

#define ID_TURN_1 1001
#define ID_TURN_2 1002
#define ID_AUTOMAT_1 2001
#define ID_AUTOMAT_2 2002

#define REQUEST_AMOUNT 100

#define STOP_AUTOMAT_CALL_COUNT 1000

typedef double my_time_t;

typedef struct list_node_t list_node_t;
typedef struct request_t request_t;
typedef struct automat_t automat_t;

// Внутренние структуры моделирования

// Узел связного списка
struct list_node_t
{
	void *element;
	list_node_t *next;
};

// Заявка
struct request_t
{
	int id;
	my_time_t time_entry;
};

// Автомат
struct automat_t
{
	int id;

	my_time_t work_ending_time;
	my_time_t down_time;

	my_time_t tmax;
	my_time_t tmin;
	
	int call_count;

	list_node_t *current_request;
	
	list_node_t *next_turns;

	int (*redirection)();
};

// Случайное время в заданном интервале
my_time_t random_time(my_time_t tmax, my_time_t tmin);

// ЗАЯВКА

// Создание
int create_request(request_t **new_request, int id, int time_entry);
// Удаление
void delete_request(request_t **del_request);

// ПЕРЕНАПРАВЛЕНИЕ ЗАЯВОК АВТОМАТАМИ

// Перенаправление автомата 1
int redirection1();

// Перенаправление автомата 2
int redirection2();

// ОДНОСВЯЗНЫЙ СПИСОК

// Создание узла
int create_node(list_node_t **new_node, void *element);

// Удаление узла
void delete_node(list_node_t **new_node);

// Добавление узла
void add_node(list_node_t **last, list_node_t *new_node);

// Перемещение узла
list_node_t *remove_node(list_node_t **head);


// Структуры вывода

typedef struct intermediat_result_t intermediat_result_t;
typedef struct final_result_t final_result_t;

struct intermediat_result_t
{
	double current_len;
	double average_len;
};

struct final_result_t
{
	my_time_t result_system_time;
	my_time_t average_request_time1;
	my_time_t average_request_time2;
	int a1_calling;
	my_time_t a2_down_time;
};

void output_intermediat_result(int a2_calling, void *turn1, void *turn2, intermediat_result_t *(*get_intermediate)(void *turn));
final_result_t *get_final(void *turn1, void *turn2, automat_t a1, automat_t a2, my_time_t sys_time, 
	my_time_t (*get_av_time)(void *turn));

void output_final_result(void *turn1, void *turn2, automat_t a1, automat_t a2, my_time_t sys_time, 
	my_time_t (*get_av_time)(void *turn));

void clearInputBuf(void);
void output_line(int size);

#endif