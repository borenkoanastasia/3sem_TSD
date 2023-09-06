#include "../inc/norm_matrix.h"

int nm_get_col_matrix(norm_matrix_t matrica, int column_num, vec_t *column)
{
    //if (matrica.columns <= column_num || 0 > column_num)
    //{
    //    return ERROR_INDEX_NOT_IN_MATRIX;
    //}
    for (int i = 0; i < matrica.rows; i++)
    {
        *(column->elements + i) = *(matrica.elements + i * matrica.columns + column_num);
    }
    return OK;
}

int nm_get_row_matrix(norm_matrix_t matrica, int row_num, vec_t *row)
{
    //if (matrica.rows <= row_num || 0 > row_num)
    //{
    //    return ERROR_INDEX_NOT_IN_MATRIX;
    //}

    for (int i = 0; i < matrica.columns; i++)
    {
        *(row->elements + i) = *(matrica.elements + row_num * matrica.columns + i);
    }
    return OK;
}

int nm_multiply_row_and_col(vec_t row, vec_t column, int *res_elem)
{
    //if (row.size != column.size)
    //{
    //    return ERROR_DIFFERENT_MATRIX;
    //}
    *res_elem = 0;
    for (int i = 0; i < row.size; i++)
    {
        *res_elem += (*(row.elements + i) * *(column.elements + i));
    }
    return OK;
}

int nm_check_matrix(norm_matrix_t m1, norm_matrix_t m2)
{
    if (m2.rows != m1.columns)
    {
        return ERROR_CALC;
    }
    return OK;
}

int norm_multiply_vec_and_matrica(norm_matrix_t m_row, norm_matrix_t matrix, norm_matrix_t *result)
{
    if (m_row.columns != matrix.rows)
    {
        return ERROR_CALC;
    }

    vec_t row, column;
    int rc = 0, cur_res = 0;

    result->rows = 1;
    result->columns = matrix.columns;

    rc = create_norm_matrix(result, 1, matrix.columns);
    if (rc != OK)
    {
        return rc;
    }

    rc = create_vector(&row, matrix.rows);
    if (rc != OK)
    {
        return rc;
    }

    nm_get_row_matrix(m_row, 0, &row);

    rc = create_vector(&column, matrix.rows);
    if (rc != OK)
    {
        return rc;
    }

    for (int j = 0; j < matrix.columns; j++)
    {
        //printf("j = %d\n", j);
        nm_get_col_matrix(matrix, j, &column);
        //output_vector(column);
        //output_vector(row);
        //printf("GOOD COLUMN\n");
        rc = nm_multiply_row_and_col(row, column, &cur_res);
        //printf("el = %d\n\n", cur_res);
        //printf("GOOD COLUMN\n");
        if (rc != OK)
        {
          	//printf("BAD\n");
            return rc;
        }
        *(result->elements + j) = cur_res;
        //printf("GOOD COLUMN\n");
    }

    free_vector(&row);
    free_vector(&column);

    return OK;
}

int norm_make_rand_matrica(norm_matrix_t *m, int procent)
{
    int row, column, elem = 0;
    int vec_cond;
    //printf("m->rows = %d\n", m->rows);
    if (m->rows == 1)
    	vec_cond = 1;
    else
    	vec_cond = 0;

    int max_digits_count = (int)((float)(m->rows * m->columns) / 100 * (float)procent);

    for (int digits_count = 0; digits_count < max_digits_count; digits_count++)
    {
        if (vec_cond)
        	row = 0;
        else
        	row = rand() % m->rows;

        column = rand() % m->columns;

        elem = *(m->elements + row * m->rows + column);

        if (elem != 0)
        {
            digits_count--;
            continue;
        }

        elem = rand() % MAX_ELEM + 1;
        //printf("elem = %d, row = %d, column = %d\n", elem, row, column);
        *(m->elements + row * m->rows + column) = elem;
    }

    return 0;
}

void nm_make_matrix_zero(norm_matrix_t *nm)
{
	for (int i = 0; i < nm->rows; i++)
	{
		for (int j = 0; j < nm->columns; j++)
		{
			nm->elements[i * nm->rows + j] = 0;
		}
	}
}