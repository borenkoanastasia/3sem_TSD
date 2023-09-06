#ifndef DELETE_PEAK_H
#define DELETE_PEAK_H

#include "../inc/types_work.h"

void delete_edge(edges_array_t *edges, int i);
void delete_loops(edges_array_t *edges);
int copy_graphs(graph_t src, graph_t **dst);
void delete_peak(graph_t *g, int peak_num);
int check_calculation(graph_t g);

#endif