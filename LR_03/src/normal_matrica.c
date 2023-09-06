#include "../inc/normal_matrica.h"

inline int norm_create_matrica(norm_matrix *new_matrica, int rows, int columns)
{
    new_matrica->rows = rows;
    new_matrica->columns = columns;

    new_matrica->elements = (int *)calloc(new_matrica->rows * new_matrica->columns, sizeof(int));
    if (!new_matrica->elements)
    {
        return ERROR_CREATE;
    }
    return OK;
}

inline void norm_free_matrica(norm_matrix *new_matrica)
{
    free((void *)new_matrica->elements);
}

inline int norm_get_element_from_matrix_by_i_j(norm_matrix matrica, int i, int j, int *elem)
{
    if (matrica.rows <= i || matrica.columns <= j)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    if (0 > i || 0 > j)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    *elem = *(matrica.elements + i * matrica.columns + j);

    return OK;
}

inline int norm_put_element_from_matrix_by_i_j(norm_matrix *matrica, int i, int j, int elem)
{
    if (matrica->rows <= i || matrica->columns <= j)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    if (0 > i || 0 > j)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    *(matrica->elements + i * matrica->columns + j) = elem;

    return OK;
}

int norm_get_column_from_matrix_by_i_j(norm_matrix matrica, int column_num, vector *column)
{
    if (matrica.columns <= column_num || 0 > column_num)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    for (int i = 0; i < matrica.rows; i++)
    {
        *(column->elements + i) = *(matrica.elements + i*matrica.columns + column_num);
    }
    return OK;
}

int norm_get_row_from_matrix_by_i_j(norm_matrix matrica, int row_num, vector *row)
{
    if (matrica.rows <= row_num || 0 > row_num)
    {
        return ERROR_INDEX_NOT_IN_MATRIX;
    }
    for (int i = 0; i < matrica.columns; i++)
    {
        *(row->elements + i) = *(matrica.elements + row_num * matrica.columns + i);
    }
    return OK;
}

int norm_multiplicate_row_and_coloumn(vector row, vector column, int *res_elem)
{
    if (row.size != column.size)
    {
        return ERROR_DIFFERENT_MATRIX;
    }
    *res_elem = 0;
    for (int i = 0; i < row.size; i++)
    {
        *res_elem += (*(row.elements + i) * *(column.elements + i));
    }
    return OK;
}

int norm_check_matrica(norm_matrix m1, norm_matrix m2)
{
    if (m2.rows != m1.columns)
    {
        return ERROR_DIFFERENT_MATRIX;
    }
    return OK;
}

int norm_multiplicate_matrica_and_matrica(norm_matrix m1, norm_matrix m2, norm_matrix *result)
{
    if (m2.rows != m1.columns)
    {
        return ERROR_DIFFERENT_MATRIX;
    }

    vector row, column;
    int rc = 0, cur_res = 0;

    result->rows = m1.rows;
    result->columns = m2.columns;

    rc = create_vector(&row, m1.columns);
    if (rc != OK)
    {
        return rc;
    }
    rc = create_vector(&column, m2.rows);
    if (rc != OK)
    {
        return rc;
    }

    for (int i = 0; i < m1.rows; i++)
    {
        for (int j = 0; j < m2.columns; j++)
        {
            norm_get_row_from_matrix_by_i_j(m1, i, &row);
            norm_get_column_from_matrix_by_i_j(m2, j, &column);
            rc = norm_multiplicate_row_and_coloumn(row, column, &cur_res);
            if (rc != OK)
            {
                return rc;
            }
            norm_put_element_from_matrix_by_i_j(result, i, j, cur_res);
        }
    }

    free_vector(&row);
    free_vector(&column);

    return OK;
}

inline void norm_output_matrica(norm_matrix m)
{
    int elem;
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            norm_get_element_from_matrix_by_i_j(m, i, j, &elem);
            printf("| %2d ", elem);
        }
        printf("|\n");
    }
    printf("\n");
}

int norm_make_rand_matrica(norm_matrix *m, int procent)
{
    int row, column, elem = 0;
    int max_digits_count = (int)((float)(m->rows * m->columns) / 100 * (float)procent);
    //printf("max_size = %d, max_digits_count = %d\n", m->rows * m->columns, max_digits_count);
    //printf("%d\n", max_digits_count);

    for (int digits_count = 0; digits_count < max_digits_count; digits_count++)
    {
        //norm_output_matrica(*m);
        //printf("m.rows = %d\n", m->rows);
        row = rand() % m->rows;
        column = rand() % m->columns;
        norm_get_element_from_matrix_by_i_j(*m, row, column, &elem);
        //printf("elem = %d\n", elem);
        if (elem != 0)
        {
            digits_count--;
            continue;
        }
        elem = rand() % MAX_ELEM + 1;
        norm_put_element_from_matrix_by_i_j(m, row, column, elem);
    }
    return 0;
}
