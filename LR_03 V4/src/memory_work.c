#include "../inc/memory_work.h"

int create_vector(vector *n, int size)
{
	n->elements = calloc(size, sizeof(int));
	if (n->elements == NULL)
		return ERR_CREATE;
	return OK;
}

void free_vector(vector *n)
{
	free(n->elements);
}

void output_vector(vector n)
{
	//printf("Vector %s: ", name);
	for (int i = 0; i < n.size; i++)
	{
		printf("|%4d", n.elements[i]);
	}
	printf("|\n");
}

int create_press_matrix(press_matrix_t *n, int el_count, int col_count)
{
	int rc;
	rc = create_vector(&(n->a), el_count);
	rc += create_vector(&(n->ia), el_count);
	rc += create_vector(&(n->ja), col_count + 1);

	n->a.size = el_count;
	n->ia.size = el_count;
	n->ja.size = col_count + 1;

	if (rc != OK)
		return ERR_CREATE;
	return OK;
}

void free_press_matrix(press_matrix_t *n)
{
	free_vector(&(n->a));
	free_vector(&(n->ia));
	free_vector(&(n->ja));
}

void output_press_matrix(press_matrix_t n)
{
	printf("A: ");
	output_vector(n.a);
	printf("IA: ");
	output_vector(n.ia);
	printf("JA: ");
	output_vector(n.ja);	
}

int create_norm_matrix(norm_matrix_t *n, int row_count, int col_count)
{
	n->columns = col_count;
	n->pointers = calloc(row_count, sizeof(int *));

	if (n->pointers == NULL)
		return ERR_CREATE;

	for (n->rows = 0; n->rows < row_count; n->rows++)
	{
		n->pointers[n->rows] = calloc(col_count, sizeof(int));
		if (n->pointers[n->rows] == NULL)
		{
			free_norm_matrix(n);
			return ERR_CREATE;
		}
	}
	return OK;
}

void free_norm_matrix(norm_matrix_t *n)
{
	for (int i = 0; i < n->rows; i++)
	{
		free(n->pointers[i]);
	}
	free(n->pointers);
}

void output_norm_matrix(norm_matrix_t n)
{
	for (int i = 0; i < n.rows; i++)
	{
		for (int j = 0; j < n.columns; j++)
		{
			printf("|%4d", n.pointers[i][j]);
		}
		printf("|\n");
	}
	printf("\n");
}
  
void clearInputBuf(void) 
{ 
      int garbageCollector; 
      while ((garbageCollector = getchar()) != '\n' && garbageCollector != EOF) 
      {}
}
