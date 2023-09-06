#include "../inc/amazing_output.h"

#define LEFT 1
#define RIGHT 0

void output_line(int i, char format_line[MAX_WORD_LEN])
{
	int j = 0;
	while (j < i) 
	{
		//printf("\nformat_line = %s\n", format_line);
		for (int k = 0; k < 4; k++)
		{
			printf(" ");
		}
		if ((format_line[j] == '1')&&(j<i-1))
			printf("|");
		else
		{
				printf(" ");
		}

		for (int k = 0; k < 4; k++)
		{
			if (j == i - 1)
			{
				if (k == 9)
					continue;
				printf("—");
			}
			else
			{
				printf(" ");
			}
		}
		j++;
	}
}

void see_right(tree_node_t **root, int i, char format_line[MAX_WORD_LEN], int side)
{
	if ((*root)->right != NULL)
	{
		if (i > 0)
		{
			if (side == RIGHT)
				format_line[i - 1] = '0';
			else 
				format_line[i - 1] = '1';
		}
		see_right(&((*root)->right), i + 1, format_line, RIGHT);
	}
	int n = strlen(format_line);
	for (int j = n; j > i + 1; j--)
	{
	//printf("\nformat_line = %s\n", format_line);
		format_line[i + j] = 0;
	}
	//printf("\nclean format_line = %s\n", format_line);

	if (i != 0)
		output_line(i, format_line);
	printf("➤ %s\n", (*root)->data);
	if ((*root)->left != NULL)
	{
		if (i > 0)
		{
			if (side == LEFT)
				format_line[i - 1] = '0';
			else 
				format_line[i - 1] = '1';
		}
		see_right(&((*root)->left), i + 1, format_line, LEFT);
	}
	for (int j = n; j > i + 1;j--)
	{
		//printf("\n clean format_line = %s\n", format_line);
		format_line[i + j] = 0;
	}
}

void output_tree(tree_node_t **root)
{
	char format_line[MAX_WORD_LEN] = { 0 };
	see_right(root, 0, format_line, RIGHT);
}



void balance_see_right(balance_tree_node_t *root, int i, char format_line[MAX_WORD_LEN], int side)
{
	if (root->right != NULL)
	{
		if (i > 0)
		{
			if (side == RIGHT)
				format_line[i - 1] = '0';
			else 
				format_line[i - 1] = '1';
		}
		balance_see_right(root->right, i + 1, format_line, RIGHT);
	}
	int n = strlen(format_line);
	for (int j = n; j > i + 1; j--)
	{
	//printf("\nformat_line = %s\n", format_line);
		format_line[i + j] = 0;
	}
	//printf("\nclean format_line = %s\n", format_line);

	if (i != 0)
		output_line(i, format_line);
	printf("➤ %s\n", root->data);
	if (root->left != NULL)
	{
		if (i > 0)
		{
			if (side == LEFT)
				format_line[i - 1] = '0';
			else 
				format_line[i - 1] = '1';
		}
		balance_see_right(root->left, i + 1, format_line, LEFT);
	}
	for (int j = n; j > i + 1;j--)
	{
		//printf("\n clean format_line = %s\n", format_line);
		format_line[i + j] = 0;
	}
}

void output_balance_tree(balance_tree_node_t *root)
{
	char format_line[MAX_WORD_LEN] = { 0 };
	balance_see_right(root, 0, format_line, RIGHT);
}
