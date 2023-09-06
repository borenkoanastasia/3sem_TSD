#ifndef HASH_WORK_H
#define HASH_WORK_H

#include "help_functions.h"

int hash_fuction(char *str, int m);

typedef struct hash_element_node_t hash_element_node_t;
typedef struct hash_table_t hash_table_t;

struct hash_element_node_t
{
	char *data;
	hash_element_node_t *next;
};

struct hash_table_t
{
	hash_element_node_t **array;
	int len;
};

int make_hash_table_from_data(hash_table_t *hash_table, data_node_t *data, int m);
void output_hash_table(hash_table_t hash_table);
void free_hash_table(hash_table_t *hash_table);

#endif