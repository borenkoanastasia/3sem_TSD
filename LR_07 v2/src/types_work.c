#include "../inc/types_work.h"

edge_t *tw_create_edge(int p1, int p2)
{
	edge_t *e = calloc(1, sizeof(edge_t));
	if (e)
	{
		e->p1 = p1;
		e->p2 = p2;
	}
	return e;
}

void tw_delete_edge(edge_t *e)
{
	free(e);
}

void tw_output_edge(edge_t e)
{
	printf("%d --- %d\n", e.p1, e.p2);
}

edges_array_t *tw_create_edges_array(int len)
{
	edges_array_t *arr = calloc(1, sizeof(edges_array_t));
	if (arr)
	{
		arr->len = len;
		arr->elements = calloc(len, sizeof(edge_t));
		if (!arr->elements)
		{
			free(arr);
			arr = NULL;
		}
	}
	return arr;
}

void tw_delete_edges_array(edges_array_t *arr)
{
	free(arr->elements);
	free(arr);
}

void tw_output_edges_array(edges_array_t arr)
{
	for (int i = 0; i < arr.len; i++)
	{
		tw_output_edge(arr.elements[i]);
	}
}

peaks_array_t *tw_create_peaks_array(int len)
{
	peaks_array_t *arr = calloc(1, sizeof(peaks_array_t));
	if (arr)
	{
		arr->len = len;
		arr->elements = calloc(len, sizeof(int));
		if (!arr->elements)
		{
			free(arr);
			arr = NULL;
		}
	}
	return arr;
}

void tw_delete_peaks_array(peaks_array_t *arr)
{
	free(arr->elements);
	free(arr);
}

void tw_output_peaks_array(peaks_array_t arr)
{
	for (int i = 0; i < arr.len; i++)
	{
		printf("%d, ", arr.elements[i]);
	}
	printf("\n");
}

graph_t *tw_create_graph(int peaks_count, int edges_count)
{
	graph_t *g = calloc(1, sizeof(graph_t));
	if (g)
	{
		g->peaks = tw_create_peaks_array(peaks_count);
		g->edges = tw_create_edges_array(edges_count);
		if (!g->edges)
		{
			free(g);
			g = NULL;
		}
	}
	return g;
}

void tw_delete_graph(graph_t *g)
{
	tw_delete_edges_array(g->edges);
	tw_delete_peaks_array(g->peaks);
	free(g);
}

void tw_output_graph(graph_t g)
{
	printf("Graph peaks\n");
	tw_output_peaks_array(*(g.peaks));
	printf("Graph edges\n");
	tw_output_edges_array(*(g.edges));
	printf("\n");
}
