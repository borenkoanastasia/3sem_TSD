#include "../inc/output_graph.h"

void add_edge(FILE *file, edge_t e)
{
	if (e.p1 == 0)
		return;
	if (e.p2 == 0)
		return;
	fprintf(file, "\t%d -- %d;\n", e.p1, e.p2);
	//printf("\t%d -- %d;\n", e.p1, e.p2);
}

void add_peaks(FILE *file, peaks_array_t peaks)
{
	for (int i = 0; i < peaks.len; i++)
	{	
		if (peaks.elements[i] == 0)
		{
			continue;
		}
		fprintf(file, "\t%d [ label = \"%d\", ];\n", peaks.elements[i], peaks.elements[i]);
	}
}

void output_graph_as_dot(graph_t g, char *filename)
{
	//printf("OUTPUT\n");
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Не удалось открыть файл для вывода\n");
		return;
	}
	fprintf(file, "graph Tree{\n");
	add_peaks(file, *g.peaks);
	for (int i = 0; i < g.edges->len; i++)
	{
		add_edge(file, g.edges->elements[i]);
	}
	//printf("good end\n");
	fprintf(file, "}");
	fclose(file);
	printf("Файл %s сохранен\n", filename);
}

int calculate_peaks_count(peaks_array_t peaks)
{
	int sum = 0;
	for (int i = 0; i < peaks.len; i++)
	{
		if (peaks.elements[i] != 0)
			sum++;
	}
	return sum;
}

int calculate_edges_count(edges_array_t edges)
{
	int sum = 0;
	for (int i = 0; i < edges.len; i++)
	{
		if (edges.elements[i].p1 != 0)
			sum++;
	}
	return sum;
}

int check_peaks_edges_counts(graph_t g)
{
	int peaks_count = calculate_peaks_count(*g.peaks);
	int edges_count = calculate_edges_count(*g.edges);
	if (peaks_count != edges_count + 1)
		return FALSE;

	return TRUE;
}

