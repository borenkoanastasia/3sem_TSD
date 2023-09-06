#include "../../inc/balance_work.h"

int add_new_node_create_balance(tree_node_t **root, data_node_t *data, int start, int end)
{
	//printf("root->word = %s\n", (*root)->word);
	add_tree_node(root, get_data_word(data, start + (end-start)/2));
	//printf("size = %d\n", start + (end-start)/2);
	if ((end-start)/2 > 0)
	{
		add_new_node_create_balance(root, data, start, start + (end-start)/2);
		add_new_node_create_balance(root, data, start + (end-start)/2, end);
	}
	//output_tree_as_dot(*root);
	//int d;
	//scanf("%d", &d);
	return 1;
}

void make_balanced_tree_from_data(tree_node_t **root, data_node_t *data)
{
	int size = get_data_size(data);
	//printf("size = %d\n", size);
	//output_data(data);
	create_tree_node(root, get_data_word(data, size/2));
	//printf("root->word = %s\n", (*root)->word);
	add_new_node_create_balance(root, data, 0, size/2);
	add_new_node_create_balance(root, data, size/2, size);
	check_heights(root);
}
void make_by_add_balanced_tree_from_data(tree_node_t **root, data_node_t *data)
{
	//printf("size = %d\n", size);
	//output_data(data);
	//create_tree_node(root, get_data_word(data, size/2));
	//printf("root->word = %s\n", (*root)->word);
	for (data_node_t *cur = data; cur; cur = cur->next)
	{
		printf("%s\n", cur->data);
		add_balance_node(root, cur->data);
	}
	//add_new_node_create_balance(root, data, 0, size/2);
	//add_new_node_create_balance(root, data, size/2, size);
	check_heights(root);
}
