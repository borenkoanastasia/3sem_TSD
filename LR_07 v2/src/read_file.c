#include "../inc/read_file.h"

int find_edge(edges_array_t edges, int p1, int p2, int cur_len)
{
	for (int i = 0; i < cur_len; i++)
	{
		if (edges.elements[i].p1 == p1 && edges.elements[i].p2 == p2)
		{
			return ERR_WORK;
		}
		if (edges.elements[i].p2 == p1 && edges.elements[i].p1 == p2)
		{
			return ERR_WORK;
		}

	}
	return OK;
}

int read_graph_size(FILE *file, int *peaks_count, int *edges_count)
{
	int rc;

	rc = fscanf(file, "%d %d", peaks_count, edges_count);
	if (rc != 2)
		return ERR_INPUT;

	if (*peaks_count < 1 || *edges_count < 0)
	{
		return ERR_INPUT;
	}
	return OK;
}

int read_edge(FILE *file, edges_array_t *e, int i, int max_peak_name)
{
	int rc, p1, p2;

	rc = fscanf(file, "%d %d", &p1, &p2);
	if (rc != 2)
		return ERR_INPUT;

	if (p1 < 1 || p1 > max_peak_name)
	{
		return ERR_INPUT;
	}
	if (p2 < 1 || p2 > max_peak_name)
	{
		return ERR_INPUT;
	}
	//printf("p1 = %d, p2 = %d\n", p1, p2);

	rc = find_edge(*e, p1, p2, i);
	if (rc != OK)
	{
		return ERR_WORK;
	}

	e->elements[i].p1 = p1;
	e->elements[i].p2 = p2;
	//printf("e->p1 = %d, e->p2 = %d\n", e->elements[i].p1, e->elements[i].p2);

	return OK;
}

int read_edges(FILE *file, edges_array_t *edges, int max_peak_name)
{
	int rc;
	for (int i = 0; i < edges->len; i++)
	{
		rc = read_edge(file, edges, i, max_peak_name);
		if (rc == ERR_WORK)
			continue;
		if (rc != OK)
			return rc;
	}
	return OK;
}

void fill_peaks_array(peaks_array_t *peaks)
{
	for (int i = 0; i < peaks->len; i++)
	{
		peaks->elements[i] = i + 1;
	}
}

int read_file(char *filename, graph_t **g)
{
	int rc, peaks_count, edges_count;

	FILE *file = fopen(filename, "r");
	if (!file)
	{
		return ERR_OPEN_FILE;
	}

	rc = read_graph_size(file, &peaks_count, &edges_count);
	if (rc != OK)
	{
		fclose(file);
		return rc;
	}

	*g = tw_create_graph(peaks_count, edges_count);

	fill_peaks_array((*g)->peaks);
	//printf("(*g)->peaks->len = %d\n", (*g)->peaks->len);

	rc = read_edges(file, (*g)->edges, peaks_count);
	if (rc != OK)
		tw_delete_graph(*g);

	fclose(file);
	return rc;
}