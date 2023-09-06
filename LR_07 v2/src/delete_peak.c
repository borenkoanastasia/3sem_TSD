#include "../inc/delete_peak.h"

void delete_edge(edges_array_t *edges, int i)
{
	edges->elements[i].p1 = 0;
	edges->elements[i].p2 = 0;
}

void delete_loops(edges_array_t *edges)
{
	for (int i = 0; i < edges->len; i++)
	{
		if (edges->elements[i].p1 == edges->elements[i].p2 && edges->elements[i].p1 != 0)
			delete_edge(edges, i);
	}
}

void delete_peak(graph_t *g, int peak_num)
{
	//printf("Start delete peak\n");
	g->peaks->elements[peak_num - 1] = 0;
	for (int i = 0; i < g->edges->len; i++)
	{
		if (g->edges->elements[i].p1 == peak_num || g->edges->elements[i].p2 == peak_num)
			delete_edge(g->edges, i);
	}
}

int copy_graphs(graph_t src, graph_t **dst)
{
	*dst = tw_create_graph(src.peaks->len, src.edges->len);
	if (!*dst)
		return ERR_CREATE;
	for (int i = 0; i < src.peaks->len; i++)
	{	
		(*dst)->peaks->elements[i] = src.peaks->elements[i];
	}
	for (int i = 0; i < src.edges->len; i++)
	{
		(*dst)->edges->elements[i].p1 = src.edges->elements[i].p1;
		(*dst)->edges->elements[i].p2 = src.edges->elements[i].p2;
	}
	return OK;
}

int calculate_edges(edges_array_t edges)
{
	int sum = 0;
	for (int i = 0; i < edges.len; i++)
	{
		if (edges.elements[i].p1 == 0)
			continue;
		sum++;
	}
	return sum;
}

int calculate_peaks(peaks_array_t peaks)
{
	int sum = 0;
	for (int i = 0; i < peaks.len; i++)
	{
		if (peaks.elements[i] == 0)
			continue;
		sum++;
	}
	return sum;
}

int check_calculation(graph_t g)
{
	if (calculate_peaks(*g.peaks) == calculate_edges(*g.edges) + 1)
		return TRUE;
	return FALSE;
}