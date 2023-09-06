#include "../../inc/balance_work.h"

void right_rotate(tree_node_t **root)
{
	if (!(*root)->right)
		return;
	tree_node_t *new_root = (*root)->right;
	(*root)->right = new_root->left;
	new_root->left = *root;
	*root = new_root;
	fix_height(&(*root)->left);
	fix_height(root);
}

void left_rotate(tree_node_t **root)
{
	if (!(*root)->left)
		return;
	tree_node_t *new_root = (*root)->left;
	(*root)->left = new_root->right;
	new_root->right = *root;
	*root = new_root;
	fix_height(&(*root)->right);
	fix_height(root);
}

void balance(tree_node_t **root)
{
	int main_balance = get_balance_factor(*root);
	int balance_right = 0, balance_left = 0;
	if ((*root)->right)
		balance_right = get_balance_factor((*root)->right);
	if ((*root)->left)
		balance_left = get_balance_factor((*root)->left);
	//printf("root = %s, main_balance = %d, left_balance = %d, right_balance =%d\n",
	//	(*root)->word, main_balance, balance_left, balance_right);

	if (main_balance == -2)
	{
		//printf("BALANCE\n");
		if (balance_right == 1)
		{
			//printf("right\n");
			left_rotate(&(*root)->right);
			//fix_height(root);
		}
		right_rotate(root);
		//printf("not right\n");
	}
	else if (main_balance == 2)
	{
		//printf("BALANCE\n");
		if (balance_left == -1)
		{
			//printf("left\n");
			right_rotate(&(*root)->left);
			//fix_height(root);
		}
		left_rotate(root);
		//printf("not left\n");
	}
}
