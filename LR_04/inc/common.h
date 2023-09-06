#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OK 0
#define ERR_CREATE 1
#define ERR_INPUT 2
#define ERR_OVERFLOW 3
#define ERR_EMPTY 4

typedef struct array_t array_t;
typedef struct node_t node_t;
typedef struct list_stack list_stack;

struct array_t
{
	int *alb; //нижняя граница
	int *ps;  //вершина стека
	int *aub; //верхняя граница
};


struct node_t
{
	int element;
	node_t *next;
};

struct list_stack
{
	node_t *start;
	node_t *ps;
};


int array_create_stack(array_t *stack, int len);
int array_push(array_t *stack, int element);
int array_pop(array_t *stack);
void array_stack_free(array_t *stack);
void array_output_stack(array_t stack);
int list_push(list_stack *stack, int element);
int list_pop(list_stack *stack);
void list_stack_free(list_stack *stack);
void list_output_stack(list_stack stack);

#endif