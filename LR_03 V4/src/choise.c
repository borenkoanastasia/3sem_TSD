#include "../inc/choise.h"

void output_title(char *message)
{
	int dash_len = (100 - strlen(message)) / 2;

	for (int i = 0; i < dash_len; i++)
	{
		printf("-");
	}
	printf("%s", message);
	for (int i = 0; i < dash_len; i++)
	{
		printf("-");
	}
	printf("\n");
}

void choise_multiplicate_norm_vec_and_matrix()
{
	norm_matrix_t n1, n2, res;
	int rc;

	rc = input_vec_and_matrix(&n1, &n2);
	if (rc != OK)
		return;

	if (n1.rows > 10 || n2.rows > 10 || n1.columns > 10 || n2.columns > 10)
	{
		press_matrix_t p1, p2, p3;
		press_norm_matrix(n1, &p1);
		press_norm_matrix(n2, &p2);
		output_title("INPUT");
		printf("Vector A\n");
		output_press_matrix(p1);
		printf("Matrix B\n");
		output_press_matrix(p2);
		output_title("RESULT");
		rc = norm_multiplicate_vec_and_matrix(n1, n2, &res);
		//printf("rows = %d, columns = %d\n", res.rows, res.columns);
		if (rc == ERR_CREATE)
		{
			printf("Не удалось выделить память под матрицу");
			return;
		}
		press_norm_matrix(res, &p3);
		output_press_matrix(p3);

	}
	else
	{
		output_title("INPUT");
		printf("Vector A\n");
		output_norm_matrix(n1);
		printf("Matrix B\n");
		output_norm_matrix(n2);
		output_title("RESULT");
		rc = norm_multiplicate_vec_and_matrix(n1, n2, &res);
		//printf("rows = %d, columns = %d\n", res.rows, res.columns);
		if (rc == ERR_CREATE)
		{
			printf("Не удалось выделить память под матрицу");
			return;
		}
		output_norm_matrix(res);
	}
}

void choise_multiplicate_press_vec_and_matrix()
{
	norm_matrix_t n1, n2;
	press_matrix_t p1, p2, res;
	int rc;

	rc = input_vec_and_matrix(&n1, &n2);
	if (rc != OK)
		return;

	//output_norm_matrix(n1);
	//<	output_norm_matrix(n2);

	rc = press_norm_matrix(n1, &p1);
	if (rc == ERR_CREATE)
	{
		printf("Не удалось выделить память под матрицу");
		return;
	}
	rc = press_norm_matrix(n2, &p2);
	if (rc == ERR_CREATE)
	{
		printf("Не удалось выделить память под матрицу");
		return;
	}


	output_title("INPUT");
	printf("Vector A\n");
	//output_norm_matrix(n1);
	output_press_matrix(p1);
	printf("Matrix B\n");
	//output_norm_matrix(n2);
	output_press_matrix(p2);
	output_title("RESULT");
	rc = press_multiplicate_vec_and_matrix(p1, p2, &res);
	if (rc == ERR_CREATE)
	{
		printf("Не удалось выделить память под матрицу");
		return;
	}
	output_press_matrix(res);
}

int test_norm(norm_matrix_t n1, norm_matrix_t n2)
{
	norm_matrix_t res;
	int start, end; //rc;

	//rc = create_norm_matrix(&res, n1.rows, n2.columns);
	//if (rc != OK)
	//	return -1;

	start = clock();
	for (int i = 0; i < 100; i++)
	{
		norm_multiplicate_vec_and_matrix(n1, n2, &res);
	}
	end = clock();
	free_norm_matrix(&res);

	return end - start;
}

int test_press(press_matrix_t p1, press_matrix_t p2)
{
	press_matrix_t res;
	int start, end; // rc;

	//rc = create_press_matrix(&res, p2.ja.size - 1, p2.ja.size);
	//if (rc != OK)
	//	return -1;

	start = clock();
	for (int i = 0; i < 100; i++)
	{
		press_multiplicate_vec_and_matrix(p1, p2, &res);
	}
	end = clock();
	free_press_matrix(&res);

	return end - start;}


void output_table_line()
{
	for (int i = 0; i < 5 + 3 + 12 + 10 + 10 + 10 + 10 + 2; i++)
	{
		printf("-");
	}
	printf("\n");
}

void output_shapka()
{
	printf("Таблица с результатами тестирования (время указано за 100 повторений)\n");
	printf("|%3s|%12s|%10s|%10s|%10s|%10s|\n", "No", "matrix type", "procent", "size", "time", "memory");
	output_table_line();
}

void choise_big_testing()
{
	norm_matrix_t n1, n2;
	press_matrix_t p1, p2;
	int norm_size, norm_time, press_time, press_size, k = 0, size;

	output_shapka();
	for (int i = 0; i < 11; i++)
	{
		size = i*10;
		if (i == 0)
		{
			size = 5;
		}
		if (i != 0 && i != 1 && i != 2 && i != 3 && i != 5 && i != 7 && i != 10)
		{
			continue;
		}
		for (int j = 1; j < 11; j++)
		{
			if (j != 1 && j != 2 && j != 3 && j != 5 && j != 7 && j != 10)
			{
				continue;
			}
			k++;
			norm_make_rand_matrix(&n1, size, size, j*10);
			norm_make_rand_matrix(&n2, size, size, j*10);
			press_norm_matrix(n1, &p1);
			press_norm_matrix(n2, &p2);

			norm_size = sizeof(norm_matrix_t) * 3 + size * size * sizeof(int) * 3;
			press_size = sizeof(press_matrix_t) * 3 + p1.a.size * 2 * sizeof(int) + p1.ja.size * sizeof(int) +
				p2.a.size * 2 * sizeof(int) + p2.ja.size * sizeof(int);

			norm_time = test_norm(n1, n2);
			press_time = test_press(p1, p2);

			printf("|%3d|%12s|%10d|%10d|%10d|%10d|\n", k, "press", j*10, size, press_time, press_size);
			printf("|%3d|%12s|%10d|%10d|%10d|%10d|\n", k, "norm", j*10, size, norm_time, norm_size);
			output_table_line();
		}

	}
}
