#ifndef HASH_WORK_H
#define HASH_WORK_H

#include "help_functions.h"

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

int hash_fuction(char *str, int m);

int make_hash_table_from_data(hash_table_t *hash_table, data_node_t *data, int m);
void output_hash_table(hash_table_t hash_table);
void free_hash_table(hash_table_t *hash_table);
int add_element_in_hash_table(hash_table_t *hash_table, char *data);
int create_hash_table(hash_table_t *hash_table, int m);
int create_hash_element_node(hash_element_node_t **res, char *data);

int add_element_hash_counter(hash_table_t *hash_table, char *data, int *i);

#endif