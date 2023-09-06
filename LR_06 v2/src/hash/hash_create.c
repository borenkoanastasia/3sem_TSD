#include "../../inc/hash_work.h"

int hash_fuction(char *str, int m)
{
	int p = 'z' + 1 - 'a';
	int p_pow = 1;
	long long hash = 0;
	for (int i=0; i < strlen(str); ++i)
	{
		hash += (str[i] - 'a' + 1) * p_pow % m;
		//printf("str[i] = %c\n", str[i]);
		//printf("hash = %lld\n", hash);
		p_pow *= p;
	}
	return hash % m;
}

int create_hash_element_node(hash_element_node_t **res, char *data)
{
	*res = calloc(1, sizeof(hash_element_node_t));
	if (!(*res))
	{
		printf("Не удалось выделить память под элемент хеш-таблицы\n");
		return ERR_CREATE;
	}
	(*res)->data = data;
	(*res)->next = NULL;
	return OK;
}

int add_element_in_hash_table(hash_table_t *hash_table, char *data)
{
	hash_element_node_t *new_node;
	int rc = create_hash_element_node(&new_node, data);
	if (rc != OK)
		return rc;
	int key = hash_fuction(data, hash_table->len);
	//printf("key = %d\n", key);
	if (hash_table->array[key])
	{
		hash_element_node_t *cur = hash_table->array[key];
		for (; cur->next; cur = cur->next)
		{
			if (!strcmp(cur->data, data))
			{
				printf("Элемент уже в таблице\n");
				return ERR_WORK;
			}
		}
		if (!strcmp(cur->data, data))
		{
			printf("Элемент уже в таблице\n");
			return ERR_WORK;
		}
		cur->next = new_node;
	}
	else
		hash_table->array[key] = new_node;
	return OK;
}

int check_table_conflicts(hash_table_t *hash_table)
{
	int j;
	for (int i = 0; i < hash_table->len; i++)
	{
		j = 0;
		hash_element_node_t *cur = hash_table->array[i];
		for (; cur; cur = cur->next, j++);
		if (j > 3)
			return ERR_MANY_CONFLICTS;
	}
	return OK;
}

void output_hash_elements(hash_element_node_t *head)
{
	for (hash_element_node_t *cur = head; cur; cur = cur->next)
	{
		printf("%s\t", cur->data);
	}
}

void output_hash_table(hash_table_t hash_table)
{
	printf("|%5s|%20s\n", "key", "values");
	for (int i = 0; i < hash_table.len; i++)
	{
		printf("|%5d|", i);
		output_hash_elements(hash_table.array[i]);
		printf("\n");
	}
}

int create_hash_table(hash_table_t *hash_table, int m)
{
	hash_table->array = calloc(m, sizeof(hash_element_node_t));
	if (!hash_table->array)
	{
		printf("Не удалось выделить память под хеш-таблицу\n");
		return ERR_CREATE;
	}
	hash_table->len = m;
	for (int i = 0; i < m; i++)
	{
		hash_table->array[i] = NULL;
	}
	return OK;
}

int make_hash_table_from_data(hash_table_t *hash_table, data_node_t *data, int m)
{
	int rc = create_hash_table(hash_table, m);
	if (rc != OK)
		return rc;

	//printf("good create table\n");
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		//printf("add %s\n", cur->data);
		add_element_in_hash_table(hash_table, cur->data);
		//printf("good add %s\n", cur->data);
	}
	return OK;
}

void free_hash_elements(hash_element_node_t **head)
{
	if (!(*head))
		return;
	for (hash_element_node_t *cur = (*head)->next;cur; cur = cur->next)
	{
		free(*head);
		*head = cur;
	}
	free(*head);
}

void free_hash_table(hash_table_t *hash_table)
{
	for (int i = 0; i < hash_table->len; i++)
	{
		free_hash_elements(&(hash_table->array[i]));
	}
	free(hash_table->array);
}