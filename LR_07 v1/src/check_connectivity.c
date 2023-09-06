#include "../inc/check_connectivity.h"

void make_black_peaks_list(graph_t *graph, int *array)
{
	int *pointer = array;
	for (int i = 1; i < graph->len; i++)
	{
		*pointer = i + 1;
		pointer++;
	}
}

int check_one_connect(int *black, int *red, int *blue)
{
	if (red)
	{}
	return 1;
}

int check_connectivity(graph_t *graph)
{
	int *black_array = calloc(graph->len - 1, sizeof(int));
	int *red_array = calloc(graph->len, sizeof(int));
	int *blue_array = calloc(graph->len, sizeof(int));

	red_array[1] = 1;

	make_black_peaks_list(graph, black_array);
	make_black_peaks_list(graph, red_array);
	make_black_peaks_list(graph, blue_array);



	//make_all_peaks_black(graph);
	//list_t *start_peak = graph->peaks;
	//((peak_t *)start_peak->element)->flag = FLAG_RED;
	return CONNECT_TRUE;
}