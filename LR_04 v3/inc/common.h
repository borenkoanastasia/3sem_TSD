#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> 

#define OK 0
#define ERR_CREATE -1
#define ERR_INPUT -2
#define ERR_OVERFLOW -3
#define ERR_EMPTY -4

#define LIST_STACK 2
#define ARRAY_STACK 1

#define MAX_RAND 1000

#define TESTING_REPEATS 100

typedef struct array_stack_t array_stack_t;
typedef struct adress_stack_node_t adress_stack_node_t;
typedef struct list_stack_node_t list_stack_node_t;

struct array_stack_t
{
	int *alb; //нижняя граница
	int *ps;  //вершина стека
	int *aub; //верхняя граница
};

struct list_stack_node_t
{
	int element;
	list_stack_node_t *next;
};

struct adress_stack_node_t
{
	long int element;
	adress_stack_node_t *next;
};


#endif