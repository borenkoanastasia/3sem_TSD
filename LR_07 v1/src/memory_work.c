#include "../inc/memory_work.h"

list_t *create_node(void *element)
{
	list_t *node = calloc(1, sizeof(list_t));
	if (node)
	{
		node->element = element;
		node->next = NULL;
	}
	return node;
}

void *delete_node(list_t *node)
{
	void *element = node->element;
	free(node);
	return element;
}

void delete_list(list_t *head)
{
	if (!head)
		return;
	list_t *cur = head->next;
	for (; cur; cur = cur->next)
	{
		free(head->element);
		free(head);
		head = cur;
	}
	free(head->element);
	free(head);
}

void output_list(list_t *head, void (*output_element)(void *element))
{
	for (list_t *cur = head; cur; cur = cur->next)
	{
		output_element(cur->element);
	}
}

edge_t *create_edge(int p1, int p2, char dirrection)
{
	edge_t *new = calloc(1, sizeof(edge_t));
	if (new)
	{
		new->p1 = p1;
		new->p2 = p2;
	}
	return new;
}

void delete_edge(edge_t *del_edge)
{
	free(del_edge);
}

void output_edge(void *edge)
{
	edge_t *e = edge;
	printf("%s %d == %d", EDGES_SPACE, e->p1, e->p2);
}

graph_t *create_graph()
{
	graph_t *new = calloc(1, sizeof(graph_t));
	if (new)
	{
		new->len = 0;
		new->edges = NULL;
	}
	return new;
}

void delete_graph(graph_t *del_graph)
{
	delete_list(del_graph->edges);
	free(del_graph);
}

void output_graph(graph_t *graph)
{
	output_list(graph->edges, output_edge);
}

int get_list_size(list_t *head)
{
	list_t *cur = NULL;
	int len = 0;
	for (cur = head; cur; cur = cur->next)
	{
		len++;
	}
	return len;
}

stack_t *create_stack(int len)
{
	stack_t *stack = calloc(1, sizeof(stack_t));
	if (stack)
	{
	stack->start = calloc(len, sizeof(peak_name_t));
	stack->end = stack->start + len;
	}
	return stack;
}

void delete_stack(stack_t **stack)
{}

void output_stack(stack_t **stack)
{}