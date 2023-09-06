#include "../inc/common.h"
#include "../inc/create.h"
#include "../inc/input.h"
#include "../inc/norm_matrix.h"
#include "../inc/press_matrix.h"
#include "../inc/testing.h"
#include "../inc/menu.h"

void test_1()
{
	//vec_t t;
	//create_vector(&t, 10);
	//free_vector(&t);
	
	norm_matrix_t nm1, nm2, nm3;
	press_matrix_t pm1, pm2, pm3;
	
	input_two_matrixes(&nm1, &nm2);

	printf("GOOD INPUT \n");

	pm_press_nm_to_pm(nm1, &pm1);
	pm_press_nm_to_pm(nm2, &pm2);

	printf("M1\n");
	output_norm_matrix(nm1);
	output_press_matrix(pm1);
	printf("M2\n");
	output_norm_matrix(nm2);
	output_press_matrix(pm2);

	norm_multiply_vec_and_matrica(nm1, nm2, &nm3);
	printf("M3\n");
	output_norm_matrix(nm3);

	pm_miltiply_row_and_matrix(pm1, pm2, &pm3);
	output_press_matrix(pm3);
	free_press_matrix(&pm3);

	pm_press_nm_to_pm(nm3, &pm3);
	output_press_matrix(pm3);

	free_press_matrix(&pm1);
	free_press_matrix(&pm2);
	free_press_matrix(&pm3);

	free_norm_matrix(&nm1);
	free_norm_matrix(&nm2);
	free_norm_matrix(&nm3);
}
void test()
{
	srand(time(NULL));
	choise choises_arr[MAX_CHOISE_NAME];
	int len;
	len = make_main_choises(choises_arr);
	menu(choises_arr, len);
}

int main()
{
	test();
	return OK;
}