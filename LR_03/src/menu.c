#include "../inc/menu.h"

void print_header(char *header)
{
	for (int i = 0; i < 50; i++)
		printf("-");

	printf("%s", header);

	for (int i = 0; i < 50; i++)
		printf("-");

	printf("\n");
}

void output_menu(choise choises_arr[MAX_CHOISE_NAME], int len)
{
	print_header("МЕНЮ");
	printf("\n");

	for (int i = 0; i < len; i++)
	{
		printf("%d.    %s\n", i + 1, choises_arr[i].name);
	}
	printf("\n - Выбор не из списка - выход\n\n");
}

int make_choise(choise choises_arr[MAX_CHOISE_NAME], int len)
{
	int input_choice, rc;
	rc = scanf("%d", &input_choice);
	if (1 != rc || input_choice > len || input_choice < 1)
	{
		printf("Некорректный выбор - выход\n");
		return CHOISE_EXIT;
	}
	choises_arr[input_choice - 1].action();
	return CHOISE_NOT_EXIT;
}

void menu(choise choises_arr[MAX_CHOISE_NAME], int len)
{
	int rc;
	while (1)
	{
		output_menu(choises_arr, len);
		rc = make_choise(choises_arr, len);
		if (rc == CHOISE_EXIT)
			break;
	}
}

// Описание основного меню 

void multiplicate_press_vector_and_matrix()
{
	press_matrix_t pm1, pm2, pm3;
	norm_matrix_t nm1, nm2;
	int rc;

	rc = input_two_matrixes(&nm1, &nm2);
	if (rc != OK)
		return;


	pm_press_nm_to_pm(nm1, &pm1);
	pm_press_nm_to_pm(nm2, &pm2);


	print_header("INPUT");
	printf("\nМатрица А:\n");
	output_press_matrix(pm1);
	printf("\nМатрица B:\n");
	output_press_matrix(pm2);

	print_header("RESULT");
	rc = pm_miltiply_row_and_matrix(pm1, pm2, &pm3);
	if (rc != OK)
	{
		output_error_message(rc);
		return;
	}
	printf("\nМатрица АxB:\n");
	output_press_matrix(pm3);
}

void multiplicate_normal_matrix()
{
	norm_matrix_t m1, m2, m3;
	int rc;
	rc = input_two_matrixes(&m1, &m2);
	if (rc != OK)
		return;

	print_header("INPUT");
	if (m1.rows > 10 || m1.columns > 10 || m2.columns > 10 || m2.rows > 10)
	{
		press_matrix_t pm1, pm2;
		pm_press_nm_to_pm(m1, &pm1);
		pm_press_nm_to_pm(m2, &pm2);
		printf("\nМатрица А:\n");
		output_press_matrix(pm1);
		printf("\nМатрица B:\n");
		output_press_matrix(pm2);
	}
	else
	{
		printf("\nМатрица А:\n");
		output_norm_matrix(m1);
		printf("\nМатрица B:\n");
		output_norm_matrix(m2);
	}


	print_header("RESULT");

	rc = create_norm_matrix(&m3, m1.columns, m2.columns);
	if (rc != OK)
	{
		output_error_message(rc);
		return;
	}
	

	rc = norm_multiply_vec_and_matrica(m1, m2, &m3);
	if (rc != OK)
	{
		output_error_message(rc);
		return;
	}

	printf("\nМатрица АxB:\n");

	if (m1.rows > 10 || m1.columns > 10 || m2.columns > 10 || m2.rows > 10)
	{
		press_matrix_t pm3;
		pm_press_nm_to_pm(m3, &pm3);
		output_press_matrix(pm3);
	}
	else
	{
		output_norm_matrix(m3);
	}
}

void compare_multiplication_press_and_usual()
{
	big_testing();
}

int make_main_choises(choise choises_arr[MAX_CHOISE_NAME])
{
	strcpy(choises_arr[0].name, "Перемножить разреженный вектор и разреженную матрицу");
	strcpy(choises_arr[1].name, "Перемножить обычные матрицы А и В");
	strcpy(choises_arr[2].name, "Сравнить перемножение разреженных матриц и вектора и обычных матриц по времени и памяти");

	choises_arr[0].action = multiplicate_press_vector_and_matrix;
	choises_arr[1].action = multiplicate_normal_matrix;
	choises_arr[2].action = compare_multiplication_press_and_usual;

	return 3;
}

// Описание меню для выбора вручную или автоматического ввода
/*
void input_manually()
{
}

void input_auto()
		press_norm_matrica_to_press(m1, &pm1);
		press_norm_matrica_to_press(m1, &pm1);
		press_norm_matrica_to_press(m1, &pm1);
{
}

make_type_of_input_choises(choise choises_arr[MAX_CHOISE_NAME])
{
	choises_arr[0]->name = "Ввод вручную";
	choises_arr[1]->name = "Ввод автоматически";

	choises_arr[0]->action = input_manually;
	choises_arr[1]->action = input_auto;
}*/
