#include "../inc/create.h"

int create_norm_matrix(norm_matrix_t *nm, int rows, int columns)
{
    nm->rows = rows;
    nm->columns = columns;

    nm->elements = (int *)calloc(nm->rows * nm->columns, sizeof(int));
    if (!nm->elements)
    {
        return ERROR_CREATE;
    }
	//output_norm_matrix(*nm);
    return OK;
}

void free_norm_matrix(norm_matrix_t *nm)
{
    free((void *)nm->elements);
}

void output_norm_matrix(norm_matrix_t nm)
{
    int elem;
    for (int i = 0; i < nm.rows; i++)
    {
        for (int j = 0; j < nm.columns; j++)
        {
            elem = *(nm.elements + i * nm.rows + j);
            printf("| %2d ", elem);
        }
        printf("|\n");
    }
    printf("\n");
}

int create_vector(vec_t *vec, int size)
{
    vec->size = size;
    vec->elements = calloc(vec->size, sizeof(int));
    if (!vec->elements)
    {
        return ERROR_CREATE;
    }
    return OK;
}

void free_vector(vec_t *vec)
{
    free((void *)vec->elements);
}

void output_vector(vec_t vec)
{
    for (int i = 0; i < vec.size; i++)
    {
        printf("%2d, ", *(vec.elements + i));
    }
    printf("\n");
}

int create_press_matrix(press_matrix_t *pm, int el_count, int col_count)
{
    int rc;
    rc = create_vector(&(pm->a), el_count);
    if (rc != OK)
    {
        return rc;
    }
    rc = create_vector(&(pm->ia), el_count);
    if (rc != OK)
    {
        return rc;
    }
    rc = create_vector(&(pm->ja), col_count + 1);
    if (rc != OK)
    {
        return rc;
    }

    pm->a.size = el_count;
    pm->ia.size = el_count;
    pm->ja.size = col_count + 1;

    return OK;
}

void free_press_matrix(press_matrix_t *pm)
{
    free_vector(&(pm->a));
    free_vector(&(pm->ia));
    free_vector(&(pm->ja));
}

void output_press_matrix(press_matrix_t pm)
{
    printf("%2s : ", "A");
    output_vector(pm.a);
    printf("\n");

    printf("%2s : ", "IA");
    output_vector(pm.ia);
    printf("\n");

    printf("%2s : ", "JA");
    output_vector(pm.ja);
    printf("\n");
}
