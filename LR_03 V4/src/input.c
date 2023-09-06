#include "../inc/input.h"

int input_manually_vec_and_matrix(norm_matrix_t *vec, norm_matrix_t *m)
{
	int rc, check, size, el_count, el, el_index, row, column;

	printf("Введите размер вектора:\n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (size < 1)
	{
		printf("Размер должен быть натуральным числом\n");
		return ERR_INPUT;
	}

	printf("Введите кол-во ненулевых элементов:\n");
	rc = scanf("%d", &el_count);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (el_count > size)
	{
		printf("Слишком много элементов!\n");
		return ERR_INPUT;
	}


	rc = create_norm_matrix(vec, 1, size);
	if (rc != OK)
		return ERR_CREATE;

	printf("Введите элементы:\n");
	rc = OK;
	for (int i = 0; i < el_count && rc == OK; i++)
	{
		printf("Элемент %d:", i + 1);
		check = scanf("%d", &el);
		if (check != 1)
		{
			rc = ERR_INPUT;
			continue;
		}

		printf("Номер %d-ого элемента:", i + 1);
		check = scanf("%d", &el_index);
		if (check != 1)
		{
			rc = ERR_INPUT;
			continue;
		}
		if (el_index < 1 || el_index > vec->columns)
		{
			rc = ERR_INPUT;
			printf("Номер за пределами массива\n");
			continue;
		}
		vec->pointers[0][el_index - 1] = el;

		printf("\n");
	}

	if (rc != OK)
	{
		printf("Некорректный ввод\n");
		clearInputBuf();
		free_norm_matrix(vec);
		return rc;
	}
	
	// Ввод матрицы

	printf("Введите кол-во столбцов матрицы:\n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (size < 1)
	{
		printf("Кол-во столбцов должно быть натуральным числом\n");
		return ERR_INPUT;
	}


	printf("Введите кол-во ненулевых элементов:\n");
	rc = scanf("%d", &el_count);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (el_count > vec->columns * size)
	{
		printf("Слишком много элементов!\n");
		return ERR_INPUT;
	}

	rc = create_norm_matrix(m, vec->columns, size);
	if (rc != OK)
		return ERR_CREATE;

	printf("Введите элементы:\n");
	rc = OK;
	for (int i = 0; i < el_count && rc == OK; i++)
	{
		printf("Элемент %d:", i + 1);
		check = scanf("%d", &el);
		if (check != 1)
		{
			rc = ERR_INPUT;
			continue;
		}

		printf("Номер строки %d-ого элемента:", i + 1);
		check = scanf("%d", &row);
		if (check != 1)
		{
			rc = ERR_INPUT;
			continue;
		}
		printf("Номер столбца %d-ого элемента:", i + 1);
		check = scanf("%d", &column);
		if (check != 1)
		{
			rc = ERR_INPUT;
			continue;
		}
		//printf("row = %d column = %d\n", row, column);
		//printf("rows = %d columns = %d\n", m->rows, m->columns);

		if (row < 1 || row > m->rows || column < 1 || column > m->columns)
		{
			rc = ERR_INPUT;
			continue;
		}
		if (m->pointers[row - 1][column - 1] != 0)
		{
			printf("Элемент уже задан! Введите следущий!\n");
			i--;
			continue;
		}

		m->pointers[row - 1][column - 1] = el;
		printf("\n");
	}

	if (rc != OK)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		free_norm_matrix(vec);
		free_norm_matrix(m);
		return rc;
	}
	return OK;
}

int input_auto_vec_and_matrix(norm_matrix_t *vec, norm_matrix_t *m)
{
	int rc, size, procent;

	printf("Введите размер вектора:\n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (size < 1)
	{
		printf("Размер должен быть натуральным числом\n");
		return ERR_INPUT;
	}

	printf("Введите процент заполнения вектора:\n");
	rc = scanf("%d", &procent);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (procent < 0 || procent > 100)
	{
		printf("Процент не может быть больше 100 и меньше 0\n");
		return ERR_INPUT;
	}

	rc = norm_make_rand_matrix(vec, 1, size, procent);
	if (rc != OK)
	{
		printf("Не удалось создать вектор\n");
		return ERR_CREATE;
	}


	printf("Введите кол-во столбцов матрицы:\n");
	rc = scanf("%d", &size);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (size < 1)
	{
		printf("Кол-во столбцов должно быть натуральным числом\n");
		return ERR_INPUT;
	}

	printf("Введите процент заполнения матрицы:\n");
	rc = scanf("%d", &procent);
	if (rc != 1)
	{
		clearInputBuf();
		printf("Некорректный ввод\n");
		return ERR_INPUT;
	}
	if (procent < 0 || procent > 100)
	{
		printf("Процент не может быть больше 100 и меньше 0\n");
		return ERR_INPUT;
	}

	rc = norm_make_rand_matrix(m, vec->columns, size, procent);
	if (rc != OK)
	{
		printf("Не удалось создать матрицу\n");
		free_norm_matrix(vec);
		return ERR_INPUT;
	}
	return OK;
}

int input_manually_or_auto()
{
	int rc, ans;
	printf("Выберете способ ввода\n");
	printf("\t1. Автоматический\n");
	printf("\t2. Вручную\n");
	printf("Введите цифру выбранного варианта. Некорректный ввод - выход в главное меню\n");

	rc = scanf("%d", &ans);
	if (rc != 1 || (ans != 1 && ans != 2))
	{
		if (rc != 1)
		{
			clearInputBuf();
		}
		printf("Некорректный ввод - выход в главное меню\n");
		return ERR_INPUT;
	}
	if (ans == 2)
		return MANUALLY;
	return AUTO;
}

int input_vec_and_matrix(norm_matrix_t *vec, norm_matrix_t *m)
{
	int rc;
	rc = input_manually_or_auto();
	if (rc == ERR_INPUT)
		return rc;
	if (rc == AUTO)
	{
		rc = input_auto_vec_and_matrix(vec, m);
	}
	else
	{
		rc = input_manually_vec_and_matrix(vec, m);
	}
	return rc;
}