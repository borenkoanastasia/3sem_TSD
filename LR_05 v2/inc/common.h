#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define OK 0
#define ERR_CREATE 1
#define ERR_INPUT 2
#define ERR_WORK 3

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

#endif
