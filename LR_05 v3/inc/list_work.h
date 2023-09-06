#ifndef LIST_WORK_H
#define LIST_WORK_H

#include "common.h"

#define MAX_CALL_OA2_COUNT 1000
#define START_REQUEST_TURN_OA1 100

#define EPS 0.000001

#define EVENT_GO_IN 1
#define EVENT_GO_OUT 2

#define NULL_ID 0

#define START_REQUEST_ID 1

#define TURN1_ID 1001
#define TURN2_ID 1002

#define AUTOMAT1_ID 2001
#define AUTOMAT2_ID 2002

#define AUTOMAT1_MIN_TIME 0
#define AUTOMAT1_MAX_TIME 6
#define AUTOMAT2_MIN_TIME 1
#define AUTOMAT2_MAX_TIME 8

typedef int id_t;
typedef double sys_time_t;

typedef struct average_t average_t;
typedef struct adress_node_t adress_node_t;

typedef struct event_t event_t;
typedef struct events_list_node_t events_list_node_t;

typedef struct request_t request_t;
typedef struct requests_list_node_t requests_list_node_t;

typedef struct turn_t turn_t;
typedef struct turns_list_node_t turns_list_node_t;

typedef struct automat_t automat_t;

// Типы данных

// Вспомогательый тип для поиска среднего арифметического
struct average_t
{
	int sum;
	int count;
};

// Событие (произошедшее с заявкой)
struct event_t
{
	id_t worker;        
	int work_num;       
	sys_time_t event_time;  
};

// Заявка
struct request_t
{
	id_t id;
	events_list_node_t *events;
	events_list_node_t *last_event;
};

// Очередь
struct turn_t
{
	id_t id;
	requests_list_node_t *pout;
	requests_list_node_t *pin;

	int len;
	average_t average;
};

// Автомат
struct automat_t
{
	id_t id;
	requests_list_node_t *element;

	sys_time_t t_max;
	sys_time_t t_min;

	sys_time_t time_end_work;
	sys_time_t downtime;

	int call_count;

	turns_list_node_t *next_turns;

	turn_t *(*beat)(turns_list_node_t *next_turns);
};


// Узлы списков

// Вспомогательный узел для списков адресов
//struct adress_node_t
//{
//	long int *element;
//	adress_node_t *next;
//};

// Узел списка событий
struct events_list_node_t
{
	event_t *element;
	events_list_node_t *next;
};

// Узел списка заявок
struct requests_list_node_t
{
	request_t *element;
	requests_list_node_t * next;
	long int adress;
};

// Узел списка очередей
struct turns_list_node_t
{
	turn_t *element;
	turns_list_node_t *next;
};

int create_event(event_t **new, id_t worker, int work, sys_time_t cur_sys_time);
int create_request(request_t **new, id_t id);
int create_turn(turn_t **new, id_t id);
int create_automat(automat_t **new, id_t id, sys_time_t tmin, sys_time_t tmax, turns_list_node_t *next_turns, 
	turn_t *(*beat)(turns_list_node_t *next_turns));

void delete_event(event_t **event);
void delete_request(request_t **request);
void delete_turn(turn_t **turn);
void delete_automat(automat_t **automat);

void output_events(events_list_node_t *head);
void output_turn(turn_t t, int buf);
void output_automat(automat_t a1);
void output_all(automat_t a1, automat_t a2, turn_t t1, turn_t t2, sys_time_t system_time);


int create_event_node(events_list_node_t **new, id_t worker, int work, sys_time_t cur_sys_time);
int create_request_node(requests_list_node_t **new, id_t id);
int create_turn_node(turns_list_node_t **new, id_t id);

void delete_event_node(events_list_node_t **new);
void delete_request_node(requests_list_node_t **new);
void delete_turn_node(turns_list_node_t **new);

void add_event_node(request_t **request, events_list_node_t **new);
void add_request_node(turn_t **turn, requests_list_node_t **new);
void add_turn_node(turns_list_node_t **last_turn, turns_list_node_t **new);

requests_list_node_t *remove_request_node(turn_t **turn);

void clear_event_list(events_list_node_t **head);
void clear_request_list(requests_list_node_t **head);
void clear_turn_list(turns_list_node_t **head);

#endif