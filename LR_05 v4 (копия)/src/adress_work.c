#include "../inc/adress_work.h"

// Работа со стеком освобожденных адрессов

int add_adresses(adress_stack_node_t **head, long int adress)
{
	adress_stack_node_t *new_node;
	new_node = (adress_stack_node_t *)calloc(1, sizeof(adress_stack_node_t));
	if (new_node == NULL)
		return ERR_CREATE;
	new_node->element = adress;
	new_node->next = *head;
	*head = new_node;
	return OK;
}

void output_adresses(adress_stack_node_t *head)
{
	for (adress_stack_node_t *cur = head; cur; cur = cur->next)
	{
		printf("%ld\n", cur->element);
	}
}

void free_adresses(adress_stack_node_t **head)
{
	for (adress_stack_node_t *cur = (*head)->next; cur; cur = cur->next)
	{
		free(*head);
		*head = cur;
	}
}

//adress_stack_node_t *Adress_Reester=NULL;