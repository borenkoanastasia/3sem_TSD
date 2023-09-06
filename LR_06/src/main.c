#include "../inc/file_read.h"
#include "../inc/tree_work.h"
#include "../inc/balance_work.h"
#include "../inc/amazing_output.h"
int main()
{
	char *filename = "test1.txt";
	data_array_t data;
	read_file(filename, &data);
	output_data(data);
	tree_node_t *root;
	make_tree_from_data(&root, data);
	output_tree(&root);

	balance_tree_node_t *new_root = NULL;
	make_balance_tree_from_data(&new_root, data);
	output_balance_tree(new_root);
	return OK;
}