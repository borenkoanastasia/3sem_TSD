#ifndef ARRAY_WORK_H
#define ARRAY_WORK_H

#include "common.h"

edge_t *tw_create_edge(int p1, int p2);
void tw_delete_edge(edge_t *e);
void tw_output_edge(edge_t e);

edges_array_t *tw_create_edges_array(int len);
void tw_delete_edges_array(edges_array_t *arr);
void tw_output_edges_array(edges_array_t arr);

peaks_array_t *tw_create_peaks_array(int len);
void tw_delete_peaks_array(peaks_array_t *arr);
void tw_output_peaks_array(peaks_array_t arr);

graph_t *tw_create_graph(int peaks_count, int edges_count);
void tw_delete_graph(graph_t *g);
void tw_output_graph(graph_t g);


#endif