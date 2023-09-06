#include "../inc/connectivity.h"

// Работа с массивом

array_t *create_array(int size)
{
	array_t *s = calloc(1, sizeof(array_t));
	if (s)
	{
		s->elements = calloc(size, sizeof(int *));
		if (s->elements)
		{
			s->len = size;
		}
		else
		{
			free(s);
			s = NULL;
		}
	}
	return s;
}

void delete_array(array_t *s)
{
	free(s->elements);
	free(s);
}

void output_array(array_t s)
{
	for (int i = 0; i < s.len; i++)
	{
		if (s.elements[i] == 0)
			continue;
		printf("%d ", s.elements[i]);
	}
	printf("\n");
}

void array_pop(array_t *array, int element)
{	
	for (int i = 0; i < array->len; i++)
	{
		if (array->elements[i] == element)
		{
			array->elements[i] = 0;
			break;
		}
	}
}

int check_empty_array(array_t arr)
{
	for (int i = 0; i < arr.len; i++)
	{
		if (arr.elements[i] != 0)
			return FALSE;
	}
	return TRUE;
}

int find_element_in_array(array_t array, int element)
{
	for (int i = 0; i < array.len; i++)
	{
		if (array.elements[i] == element)
			return i;
	}
	return -1;
}

//Работа со стеком

stack_t *create_stack(int size)
{
	stack_t *s = calloc(1, sizeof(stack_t));
	if (s)
	{
		s->start = calloc(size, sizeof(int));
		if (s->start)
		{
			s->end = s->start + size;
			s->ps = s->start;
		}
		else
		{
			free(s);
			s = NULL;
		}
	}
	return s;
}

void delete_stack(stack_t *s)
{
	free(s->start);
	free(s);
}

void output_stack(stack_t s)
{
	for (int *i = s.start; i < s.ps; i++)
	{
		printf("%d ", *i);
	}
	printf("\t\t");
}

void push_stack(stack_t *stack, int element)
{
	*stack->ps = element;
	stack->ps++;
}

int pop_stack(stack_t *stack)
{
	stack->ps--;
	int element = *stack->ps;
	return element;
}

void prepear_array_and_stack(peaks_array_t peaks, array_t *not_work, stack_t *in_work)
{
	int flag = 0, k = 0;
	for (int i = 0; i < peaks.len; i++)
	{
		if (peaks.elements[i] != 0 && flag == 0)
		{
			flag = 1;
			push_stack(in_work, peaks.elements[i]);
		}
		else if (peaks.elements[i] != 0)
		{
			not_work->elements[k] = peaks.elements[i];
			k++;
		}
	}
}

void work(array_t *not_work, stack_t *in_work, stack_t *worked, edges_array_t edges)
{
	if (in_work->ps == in_work->start)
		return;
	int work_element = pop_stack(in_work);
	int element, index;
	//printf("START\n");
	//printf("worked_element = %d\n", work_element);

	for (int i = 0; i < edges.len; i++)
	{
		//tw_output_edge(edges.elements[i]);
		if (edges.elements[i].p1 == work_element)
		{
			element = edges.elements[i].p2;
			index = find_element_in_array(*not_work, element);
			//printf("element = %d\n", element);
			if (index == -1)
				continue;
			array_pop(not_work, element);
			push_stack(in_work, element);
		}

		if (edges.elements[i].p2 == work_element)
		{
			element = edges.elements[i].p1;
			index = find_element_in_array(*not_work, element);
			//printf("element = %d\n", element);
			if (index == -1)
				continue;
			array_pop(not_work, element);
			push_stack(in_work, element);
		}
	}
	push_stack(worked, work_element);
	//output_array(*not_work);
	//output_stack(*in_work);
	//output_stack(*worked);
	//printf("\n");
	//printf("END\n");
	work(not_work, in_work, worked, edges);
}

int check_graph_connectivity(graph_t g)
{
	array_t *not_work;
	stack_t *in_work, *worked;
	int answer = 0;
	not_work = create_array(g.peaks->len);
	in_work = create_stack(g.peaks->len);
	worked = create_stack(g.peaks->len);

	//printf("GOOD INIT\n");


	prepear_array_and_stack(*g.peaks, not_work, in_work);
	//output_array(*not_work);
	//output_stack(*in_work);
	//output_stack(*worked);
	//printf("\n");

	work(not_work, in_work, worked, *g.edges);

	answer = check_empty_array(*not_work);
	delete_array(not_work);
	delete_stack(in_work);
	delete_stack(worked);
	return answer;
}