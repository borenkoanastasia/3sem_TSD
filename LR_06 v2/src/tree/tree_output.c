#include "../../inc/tree_work.h"

void add_tree_lines(FILE *file, tree_node_t *root, int *i)
{
	if (root->left != NULL)
	{
		//printf("left\n ");
		fprintf(file, "\t%s%d -> %s%d;\n", root->word, root->height, root->left->word, root->left->height);
		add_tree_lines(file, root->left, i);
		printf("\t%s -> %s %d\n", root->word, root->left->word, root->height);
	}
	else if (root->right != NULL)
	{
		fprintf(file, "\t%d [ label = \"%d\", style = invis ];\n", *i, *i);
		fprintf(file, "\t%s%d -> %d [ style = invis ];\n", root->word, root->height, *i);
		//printf("\t%s -> %d [ style = invis ]\n", root->word, *i);
		(*i)++;
	}
	if (root->right != NULL)
	{
		//printf("right\n ");
		fprintf(file, "\t%s%d -> %s%d;\n", root->word, root->height, root->right->word, root->right->height);
		printf("\t%s -> %s %d\n", root->word, root->right->word, root->height);
		add_tree_lines(file, root->right, i);
	}
	else if (root->left != NULL)
	{
		fprintf(file, "\t%d [ label = \"%d\", style = invis ];\n", *i, *i);
		fprintf(file, "\t%s%d -> %d [ style = invis ]; \n", root->word, root->height, *i);
		//printf("\t%s -> %d [ style = invis ]\n", root->word, *i);
		(*i)++;
	}
}

void output_tree_as_dot(tree_node_t *root, char *filename)
{
	int i = 0;
	//printf("OUTPUT\n");
	FILE *file = fopen(filename, "w");
	if (!file)
	{
		printf("Не удалось открыть файл для вывода\n");
		return;
	}
	fprintf(file, "digraph Tree{\n");
	add_tree_lines(file, root, &i);
	//printf("good end\n");
	fprintf(file, "}");
	fclose(file);
	printf("Файл сохранен\n");
}

