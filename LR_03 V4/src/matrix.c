#include "../inc/matrix.h"

int norm_multiplicate_vec_and_matrix(norm_matrix_t n1, norm_matrix_t n2, norm_matrix_t *res)
{
	int rc = create_norm_matrix(res, 1, n2.columns);
	if (rc != OK)
		return rc;
	//printf("n1.rows = %d, n1.columns = %d\n", n1.rows, n1.columns);
	//printf("n2.rows = %d, n2.columns = %d\n", n2.rows, n2.columns);
	//printf("res.rows = %d, res.columns = %d\n", res->rows, res->columns);

	for (int i = 0; i < n2.columns; i++)
	{
		res->pointers[0][i] = 0;
		for (int j = 0; j < n1.columns; j++)
		{
			res->pointers[0][i] += n1.pointers[0][j] * n2.pointers[j][i];
		}
	}
	//for (int j = 0; j < n1.columns; j++)
	//{
	//	res->pointers[0][k] = 0;
	//	for (int k = 0; k < n2.columns; k++)
	//	{
	//		printf("j = %d, k = %d\n", j, k);
	//		output_norm_matrix(*res);
	//		res->pointers[0][k] += n1.pointers[0][j] * n2.pointers[j][k];
	//	}
	//}
	//printf("end");
	return OK;
}

int norm_make_rand_matrix(norm_matrix_t *m, int rows, int columns, int procent)
{
	//printf("start make rand matrix\n");
	int row, column, element, rc;// k = 0;
	rc = create_norm_matrix(m, rows, columns);
	if (rc != OK)
		return rc;
	//printf("rows = %d, columns = %d\n", rows, columns);
	//output_norm_matrix(*m);
	//printf("(int)((float)(rows * columns) / (float)procent * 100) = %d\n", (int)((float)(rows * columns) * (float)procent / 100));
	for (int i = 0; i < (int)((float)(rows * columns) * (float)procent / 100); i++)
	{
		//k++;
		//if (k == 11)
		//	scanf("%d", &k);
		row = rand() % rows;
		column = rand() % columns;
		//printf("i = %d, rows = %d, columns = %d, row = %d, column = %d, element = %d\n", i, rows, columns, row, column, m->pointers[row][column]);
		if (m->pointers[row][column] != 0)
		{
			i--;
			continue;
		}
		element = rand() % MAX_NUM + 1;
		//printf("new_elenement = %d\n", element);
		m->pointers[row][column] = element;
	}
	//printf("end make rand matrix\n");
	//output_norm_matrix(*m);
	return OK;
}

int get_elements_count(norm_matrix_t n)
{
	int count = 0;
	for (int i = 0; i < n.columns; i++)
	{
		for (int j = 0; j < n.rows; j++)
		{
			if (n.pointers[j][i] != 0)
			{
				count++;
			}
		}
	}
	return count;
}

int press_norm_matrix(norm_matrix_t n, press_matrix_t *p)
{
	int rc, el_count, k = 0;

	el_count = get_elements_count(n);
	rc = create_press_matrix(p, el_count, n.columns);
	if (rc != OK)
		return rc;

	p->ja.elements[0] = 1;
	
	for (int i = 0; i < n.columns; i++)
	{
		for (int j = 0; j < n.rows; j++)
		{
			if (n.pointers[j][i] != 0)
			{
				p->a.elements[k] = n.pointers[j][i];
				p->ia.elements[k] = j + 1;
				k++;
			}
		}
		p->ja.elements[i + 1] = k + 1;
	}
	return OK;
}

int press_multiplicate_vec_and_matrix(press_matrix_t m1, press_matrix_t m2, press_matrix_t *res)
{
	int column_el_count, elem, cur_res_el_index = 1, rc;

	rc = create_press_matrix(res, m2.a.size - 2, m2.ja.size - 1);
	if (rc != OK)
		return OK;

	for (int j = 0; j < m2.ja.size - 1; j++)     //перебираю все столбцы матрицы
	{
		column_el_count = m2.ja.elements[j + 1] - m2.ja.elements[j];
		elem = 0;
		//printf("m2.ja.elements[j + 1] = %d, m2.ja.elements[j] = %d\n", m2.ja.elements[j + 1], m2.ja.elements[j]);

		//перебираю элементы текущего столбца матрицы
		for (int k = m2.ja.elements[j] - 1; k < m2.ja.elements[j] - 1 + column_el_count; k++) 
		{
			if (m1.ja.elements[m2.ia.elements[k]] - m1.ja.elements[m2.ia.elements[k] - 1] == 0)
				continue;
			elem += m1.a.elements[m1.ja.elements[m2.ia.elements[k] - 1] - 1] * m2.a.elements[k];
			//printf("j = %d, m2.ja.elements[j] = %d, k = %d\n", j, m2.ja.elements[j], k);
			//printf("m1.a.elements[m1.ja.elements[m2.ia.elements[k]]] = %d, m2.a.elements[k] = %d, elem = %d\n",  m1.a.elements[m1.ja.elements[m2.ia.elements[k]]], m2.a.elements[k], elem);
		}
		res->ja.elements[j] = cur_res_el_index;
		if (elem == 0)
			continue;
		res->a.elements[cur_res_el_index - 1] = elem;
		res->ia.elements[cur_res_el_index - 1] = 1;
		cur_res_el_index++;
		//printf("ja\n");
		//output_vector(res->ja);
		//output_press_matrix(*res);
	}
	res->a.size = cur_res_el_index - 1;
	res->ia.size = cur_res_el_index - 1;
	res->ja.elements[m2.ja.size - 1] = cur_res_el_index + 1;
	return OK;
}