#ifndef MEMORY_WORK_H
#define MEMORY_WORK_H

#include "common.h"

list_t *create_node(void *element);
void *delete_node(list_t *node);
void delete_list(list_t *head);
void output_list(list_t *head, void (*output_element)(void *element));
edge_t *create_edge(int p1, int p2, char dirrection);
void delete_edge(edge_t *del_edge);
void output_edge(void *edge);
graph_t *create_graph();
void delete_graph(graph_t *del_graph);
void output_graph(graph_t *graph);
int get_list_size(list_t *head);

#endif