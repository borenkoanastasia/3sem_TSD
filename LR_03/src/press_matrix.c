#include "../inc/common.h"
#include "../inc/norm_matrix.h"
/*
void pm_get_el(press_matrix_t pm, int in_i, int in_j, int *elem)
{
	int column_size = pm.ja.elements[in_i + 1] - pm.ja.elements[in_i];
	for (int i = 0; i < column_size; i++)
	{
		pm.ja.elements[i + in_i];
		if (pm.a[i]);
		*elem = pm.a[i]; 
	}
}
*/
void pm_get_column(press_matrix_t pm, press_matrix_t *column, int in_c)
{
	int size;
	size = (pm.ja.elements[in_c + 1] - pm.ja.elements[in_c]);
	for (int j = 0; j < size; j++)
	{
		/*if (pm.a.size < pm.ja.elements[in_c] + j)
		{
			size = j;
			break;
		}*/
		column->a.elements[j] = pm.a.elements[pm.ja.elements[in_c] + j - 1];
		column->ia.elements[j] = pm.ia.elements[pm.ja.elements[in_c] + j - 1];
	}
	column->ja.elements[0] = 0;
	column->ja.elements[1] = size;
	column->a.size = size;
	column->ia.size = size;
}

int pm_multiply_row_and_column(press_matrix_t row, press_matrix_t column)
{
	int k = 0, result = 0, cur_el;

	for (int i = 0; i < row.ja.size - 1; i++)
	{
		//printf("i = %d\n", i);
		if (row.ja.elements[i + 1] - row.ja.elements[i] == 0)
			continue;

		cur_el = row.a.elements[row.ja.elements[i] - 1];
		//printf("cur_el = %d\n", cur_el);

		while (column.ia.elements[k] < i)
		{
			//printf("k = %d\n", k);
			k++;
			if (k >= column.ia.size)
				break;
		} 
		if (column.ia.elements[k] == i)
		{		
			result += column.a.elements[k] * cur_el;
			k++; 
		}	
	}
	//printf("good end pm\n");
	return result;
}

int get_row_count(press_matrix_t pm)
{
	int max_el = -1;
	for (int i = 0; i < pm.ia.size; i++)
	{
		if (max_el < pm.ia.elements[i])
		{
			max_el = pm.ia.elements[i];
		}
	}
	return max_el;
}
void clean_column(press_matrix_t *column)
{
	for (int i = 0; i < column->a.size; i++)
	{
		column->a.elements[i] = 0;
		column->ia.elements[i] = 0;
	}
	column->ja.elements[0] = 0;
	column->ja.elements[1] = 0;
}

int pm_miltiply_row_and_matrix(press_matrix_t row, press_matrix_t matrix, press_matrix_t *result)
{
	int rc, cur_res, row_count; //res_index;
	press_matrix_t column;

	row_count = get_row_count(matrix);

	if (row_count > row.ja.size)
		return ERROR_CALC;

	rc = create_press_matrix(result, matrix.a.size, matrix.ja.size - 1);
	if (rc != OK)
		return rc;
 
	rc = create_press_matrix(&column, row_count, 1);
	if (rc != OK)
		return rc;

	int res_index = 0;
	//printf("pm_start\n");

	for (int i = 0; i < matrix.ja.size - 1; i++)
	{
		pm_get_column(matrix, &column, i);
		//printf("not multiply\n");
		cur_res = pm_multiply_row_and_column(row, column);
		//printf("pm_multiply\n");
		//printf("cur_res = %d\n\n", cur_res);
		if (cur_res != 0)
		{
			result->a.elements[res_index] = cur_res;
			result->ia.elements[res_index] = 0;
			res_index++;
		}
		//printf("pm_res\n");
		result->ja.elements[i] = res_index;
		clean_column(&column);
	}
	result->a.size = res_index;
	result->ia.size = res_index;
	result->ja.elements[result->ja.size - 1] = result->a.size + 1;
	free_press_matrix(&column);
	return OK;
}

int get_nm_el_count(norm_matrix_t nm)
{
	int el_count = 0;

	for (int i = 0; i < nm.rows; i++)
	{
		for (int j = 0; j < nm.columns; j++)
		{
			//printf("i = %d, j = %d el_count = %d, nm.elements[i * nm.rows + j] = %d\n", i, j, el_count, nm.elements[i * nm.rows + j]);
			if (nm.elements[i * nm.rows + j] != 0)
				el_count++;
		}
	}
	return el_count;
}

int pm_press_nm_to_pm(norm_matrix_t nm, press_matrix_t *pm)
{
	int el_count = get_nm_el_count(nm), pm_ind = 0, elem, rc;

	rc = create_press_matrix(pm, el_count, nm.columns);
	if (rc != OK)
		return rc;

	for (int i = 0; i < nm.columns; i++)
	{
		pm->ja.elements[i] = pm_ind + 1;
		for (int j = 0; j < nm.rows; j++)
		{
			elem = *(nm.elements + j * nm.rows + i);
			//printf("elem = %d\n", elem);
			if (elem != 0)
			{
				pm->a.elements[pm_ind] = elem;
				pm->ia.elements[pm_ind] = j;
				pm_ind++;
			}
		}
	}

	pm->ja.elements[pm->ja.size - 1] = el_count + 1;
	return OK;
}