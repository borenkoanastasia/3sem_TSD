#include "../inc/input.h"

int input_type()
{
	int in_type;
	printf("Выберите способ ввода:\n");
	printf("\t1\tАвтоматический\n");
	printf("\t2\tВручную\n");

	int rc = scanf("%d", &in_type);
	if (rc != 1)
	{
		printf("Некорректный выбор - выход\n");
		fflush(stdout);
		return 0;
	}
	return in_type;
}

int input_matrix_size(int *columns)
{
	/*printf("Введите кол-во строк матрицы:");

	int rc = scanf("%d", rows);
	if (rc != 1 || *rows < 1)
	{
		printf("Некорректное кол-во строк матрицы\n");	
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}*/
	printf("Введите кол-во столбцов матрицы:");

	int rc = scanf("%d", columns);
	if (rc != 1 || *columns < 1)
	{
		printf("Некорректное кол-во столбцов матрицы\n");
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_vector_size(int *columns)
{
	printf("Введите длину вектора:");

	int rc = scanf("%d", columns);
	if (rc != 1 || *columns < 1)
	{
		printf("Некорректная длина вектора\n");
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_procent(int *procent)
{
	printf("Введите процент заполнения матрицы:");

	int rc = scanf("%d", procent);
	if (rc != 1 || *procent > 100 || *procent < 1)
	{
		printf("Некорректный процент заполнения матрицы (проценты от 1 до 100)\n");	
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_el_count(int *el_count)
{
	printf("Введите кол-во ненулевых элементов:");

	int rc = scanf("%d", el_count);
	if (rc != 1 || *el_count > 100 || *el_count < 1)
	{
		printf("Некорректное кол-во ненулевых элементов\n");	
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_el_data(int * el, int *i, int *j)
{
	printf("Введите элемент и его координаты через пробел: 'el i j' - где i - номер строки, j - номер столбца: ");

	int rc = scanf("%d %d %d", el, i, j);
	if (rc != 3)
	{
		printf("Некорректный ввод\n");	
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_vec_el_data(int * el, int *i)
{
	printf("Введите элемент и его номер через пробел: 'el i' - где i - номер элемента: ");

	int rc = scanf("%d %d", el, i);
	if (rc != 2)
	{
		printf("Некорректный ввод\n");	
		if (rc != 1) 
			fflush(stdout);
		return ERROR_INPUT;
	}
	return OK;
}

int input_auto(norm_matrix_t *vector)
{
	int procent, rc;
	
	rc = input_procent(&procent);
	if (rc != OK)
		return rc;
	norm_make_rand_matrica(vector, procent);
	return OK;
}

int input_vector_manually(norm_matrix_t *vector)
{
	int el_count, el, cur_i, rc;

	rc = input_el_count(&el_count);
	if (rc != OK)
		return rc;

	for (int i = 0; i < el_count; i++)
	{
		rc = input_vec_el_data(&el, &cur_i);
		if (rc != OK)
			return rc;

		if (cur_i > vector->columns || cur_i < 1)
		{
			printf("Номер за пределами матрицы\n");
			return ERROR_INPUT;
		}
		vector->pointers[0][cur_i] = el;
	}
	return OK;
}

int input_vector(norm_matrix_t *vector, int type_input)
{
	int size, rc;

	printf("ВВЕДИТЕ ВЕКТОР\n\n");
	
	rc = input_vector_size(&size);
	if (rc != OK)
		return rc;

	create_norm_matrix(vector, 1, size); 
	//output_norm_matrix(*vector);
	
	if (type_input == AUTO)
	{
		rc = input_auto(vector);
		if (rc != OK)
			return rc;
	}
	else if (type_input == MANUALLY)
	{
		rc = input_vector_manually(vector);
		if (rc != OK)
			return rc;
	}
	return OK;
}

int input_matrix_manually(norm_matrix_t *vector)
{
	int el_count, el, cur_i, cur_j, rc;

	rc = input_el_count(&el_count);
	if (rc != OK)
		return rc;

	for (int i = 0; i < el_count; i++)
	{
		rc = input_el_data(&el, &cur_i, &cur_j);
		if (rc != OK)
			return rc;

		if (cur_i > vector->columns || cur_i < 1)
		{
			printf("Номер за пределами матрицы\n");
			return ERROR_INPUT;
		}
		if (cur_j > vector->rows || cur_j < 1)
		{
			printf("Номер за пределами матрицы\n");
			return ERROR_INPUT;
		}
		vector->pointers[cur_i][cur_j] = el;
	}
	return OK;
}

int input_two_matrixes(norm_matrix_t *vector, norm_matrix_t *matrix)
{
	int rc, type_input;
	type_input = input_type();
	if (type_input != AUTO && type_input != MANUALLY)
	{
		//printf("%d\n", type_input);
		return ERROR_INPUT;
	}

	rc = input_vector(vector, type_input);
	if (rc != OK)
		return rc;
	//output_norm_matrix(*vector);

	int column;

	printf("\nВВЕДИТЕ МАТРИЦУ\n\n");
	
	rc = input_matrix_size(&column);
	if (rc != OK)
		return rc;

	rc = create_norm_matrix(matrix, vector->columns, column);
	if (rc != OK)
		return rc;

	rc = nm_check_matrix(*vector, *matrix);
	//printf("%d\n", rc);
	if (rc != OK)
		return rc;

	if (type_input == AUTO)
	{
		rc = input_auto(matrix);
		if (rc != OK)
			return rc;
	}
	else if (type_input == MANUALLY)
	{
		rc = input_matrix_manually(matrix);
		if (rc != OK)
			return rc;
	}
	printf("\n");
	return OK;
}